--------------------------------------------------------------------------------
--
-- MODULENAME	: PT_driver.vhd
-- PROJECT		: P&T system
-- DESCRIPTION	: See documentation
--
-- CHANGE LOG:
--------------------------------------------------------------------------------
-- DATE		ID		CHANGE
-- DDMMYY
------------------------
-- 190516	MG		Module created.
--
--------------------------------------------------------------------------------

--Library declarations
--------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


--Entity declaration
--------------------------------------------------------------------------------
entity PT_driver is
	generic( Kp_tilt: integer := 6;
				Ki_tilt: integer := 2;
				
				Kp_pan: integer := 2;
				Ki_pan: integer := 2);
	
	port( S_CLK: in std_logic;
			MOSI:	in std_logic;
			MISO: out std_logic;
			SS: in std_logic;
	
			ENABLE_PAN: out std_logic;
			MOTOR_CONTROL_PAN_1: out std_logic;
			MOTOR_CONTROL_PAN_2: out std_logic;
			HALL_SENSOR_PAN_1: in std_logic;
			HALL_SENSOR_PAN_2: in std_logic;
			
			ENABLE_TILT: out std_logic;
			MOTOR_CONTROL_TILT_1: out std_logic;
			MOTOR_CONTROL_TILT_2: out std_logic;
			HALL_SENSOR_TILT_1: in std_logic;
			HALL_SENSOR_TILT_2: in std_logic;
			
			SEGMENTS: out std_logic_vector(1 to 8);
			AN: out std_logic_vector(3 downto 0);
			
			CLK: in std_logic);
end PT_driver;


--Architecture of entity
--------------------------------------------------------------------------------
architecture Behavioral of PT_driver is
-- Generel wires --
	signal CLOCK_1K_wire: std_logic;
	
-- Tilt wires --
	signal MOTOR_ENABLE_TILT_wire: std_logic;
	signal MOTOR_DIR_TILT_wire: std_logic;
	signal DUTY_CYCLE_TILT_wire: std_logic_vector(7 downto 0);
	signal POSITION_TILT_wire: std_logic_vector(10 downto 0);
	signal ERROR_TILT_wire: std_logic_vector(10 downto 0);
	signal TARGET_TILT_wire: std_logic_vector(10 downto 0);
	signal MAX_SPEED_TILT_wire: std_logic_vector(7 downto 0);
	signal MIN_SPEED_TILT_wire: std_logic_vector(7 downto 0);
	
-- Pan wires --
	signal MOTOR_ENABLE_PAN_wire: std_logic;
	signal MOTOR_DIR_PAN_wire: std_logic;
	signal DUTY_CYCLE_PAN_wire: std_logic_vector(7 downto 0);
	signal POSITION_PAN_wire: std_logic_vector(10 downto 0);
	signal ERROR_PAN_wire: std_logic_vector(10 downto 0);
	signal TARGET_PAN_wire: std_logic_vector(10 downto 0);
	signal MAX_SPEED_PAN_wire: std_logic_vector(7 downto 0);
	signal MIN_SPEED_PAN_wire: std_logic_vector(7 downto 0);
	
	component Motor_driver
			port( CLK: in std_logic;
					ENABLE: in std_logic;
					MOTOR_DIR: in std_logic;
					DUTY_CYCLE: in std_logic_vector(7 downto 0);
					ENABLE_OUT: out std_logic;
					MOTOR_CONTROL_1: out std_logic;
					MOTOR_CONTROL_2: out std_logic);
	end component;
	
	component Hall_Counter
		Port ( HALL1: in std_logic;
				 HALL2: in std_logic;
				 POSITION: out std_logic_vector(10 downto 0);
				 CLK: in std_logic);
	end component;
	
	component Mux_Display
		port( clk_50MHz: 	in		std_logic;
				bcd:			in		std_logic_vector(15 downto 0);
				segm:			out	std_logic_vector(1 to 8);
				an:			out 	std_logic_vector(3 downto 0);
				clk_1kHz:	out	std_logic);
	end component;
	
	component PID_controller
		port( ERROR: in std_logic_vector(10 downto 0);
				OUTPUT: out std_logic_vector(7 downto 0);
				CLK: in std_logic;
				K_P: in std_logic_vector(5 downto 0);
				K_I: in std_logic_vector(5 downto 0);
				MAX_SPEED: in std_logic_vector(7 downto 0);
				MIN_SPEED: in std_logic_vector(7 downto 0));
	end component;
	
	component Simple_comparator
		port( INPUT: in std_logic_vector(10 downto 0);
				FEEDBACK: in std_logic_vector(10 downto 0);
				OUTPUT: out std_logic_vector(10 downto 0);
				DIR: out std_logic;
				CONSTRAINER: in std_logic);
	end component;
	
	component SPI_slave
		port( S_CLK: in std_logic;
				MOSI:	in std_logic;
				MISO: out std_logic;
				SS: in std_logic;
				
				CURRENT_POS_TILT: in std_logic_vector(10 downto 0); -- Current pos
				CURRENT_POS_PAN: in std_logic_vector(10 downto 0);
				TARGET_POS_TILT: out std_logic_vector(10 downto 0); -- Target pos
				TARGET_POS_PAN: out std_logic_vector(10 downto 0);
				MAX_SPEED_TILT: out std_logic_vector(7 downto 0); -- Max speed
				MAX_SPEED_PAN: out std_logic_vector(7 downto 0);
				MIN_SPEED_TILT: out std_logic_vector(7 downto 0); -- Min speed
				MIN_SPEED_PAN: out std_logic_vector(7 downto 0);
				MOTOR_ENABLE_TILT: out std_logic; -- Motor control
				MOTOR_ENABLE_PAN: out std_logic;
				
				CLK: in std_logic);
	end component;
	
begin

-- SPI --
	SPI_UI: SPI_slave
		port map( S_CLK => S_CLK,
					 MOSI => MOSI,
					 MISO => MISO,
					 SS => SS,
					 CURRENT_POS_TILT => POSITION_TILT_wire,
					 CURRENT_POS_PAN => POSITION_PAN_wire,
					 TARGET_POS_TILT => TARGET_TILT_wire,
					 TARGET_POS_PAN => TARGET_PAN_wire,
					 MAX_SPEED_TILT => MAX_SPEED_TILT_wire,
					 MAX_SPEED_PAN => MAX_SPEED_PAN_wire,
					 MIN_SPEED_TILT => MIN_SPEED_TILT_wire,
					 MIN_SPEED_PAN => MIN_SPEED_PAN_wire,
					 MOTOR_ENABLE_TILT => MOTOR_ENABLE_TILT_wire,
					 MOTOR_ENABLE_PAN => MOTOR_ENABLE_PAN_wire,
					 CLK => CLK);


-- TILT --
	MOTOR_DRIVER_TILT: Motor_driver
		port map( CLK => CLK,
					 ENABLE => MOTOR_ENABLE_TILT_wire,
					 MOTOR_DIR => MOTOR_DIR_TILT_wire,
					 DUTY_CYCLE => DUTY_CYCLE_TILT_wire,
					 ENABLE_OUT => ENABLE_TILT,
					 MOTOR_CONTROL_1 => MOTOR_CONTROL_TILT_1,
					 MOTOR_CONTROL_2 => MOTOR_CONTROL_TILT_2);
					 
	HALLCOUNTER_TILT: Hall_Counter
		port map( HALL1 => HALL_SENSOR_TILT_1,
					 HALL2 => HALL_SENSOR_TILT_2,
					 POSITION => POSITION_TILT_wire,
					 CLK => CLK);
					 
	PID_CONTROLLER_TILT: PID_controller
		port map( ERROR => ERROR_TILT_wire,
					 OUTPUT => DUTY_CYCLE_TILT_wire,
					 CLK => CLK,
					 K_P => conv_std_logic_vector(Kp_tilt, 6),
					 K_I => conv_std_logic_vector(Ki_tilt, 6),
					 MAX_SPEED => MAX_SPEED_TILT_wire,
					 MIN_SPEED => MIN_SPEED_TILT_wire);
					 
	SIMPLE_COMPARATOR_TILT: Simple_comparator
		port map( INPUT => TARGET_TILT_wire,
					 FEEDBACK => POSITION_TILT_wire,
					 OUTPUT => ERROR_TILT_wire,
					 DIR => MOTOR_DIR_TILT_wire,
					 CONSTRAINER => '0');
					
					
-- PAN --
	MOTOR_DRIVER_PAN: Motor_driver
		port map( CLK => CLK,
					 ENABLE => MOTOR_ENABLE_PAN_wire,
					 MOTOR_DIR => MOTOR_DIR_PAN_wire,
					 DUTY_CYCLE => DUTY_CYCLE_PAN_wire,
					 ENABLE_OUT => ENABLE_PAN,
					 MOTOR_CONTROL_1 => MOTOR_CONTROL_PAN_1,
					 MOTOR_CONTROL_2 => MOTOR_CONTROL_PAN_2);
					 
	HALLCOUNTER_PAN: Hall_Counter
		port map( HALL1 => HALL_SENSOR_PAN_1,
					 HALL2 => HALL_SENSOR_PAN_2,
					 POSITION => POSITION_PAN_wire,
					 CLK => CLK);
					 
	PID_CONTROLLER_PAN: PID_controller
		port map( ERROR => ERROR_PAN_wire,
					 OUTPUT => DUTY_CYCLE_PAN_wire,
					 CLK => CLK,
					 K_P => conv_std_logic_vector(Kp_pan, 6),
					 K_I => conv_std_logic_vector(Ki_pan, 6),
					 MAX_SPEED => MAX_SPEED_PAN_wire,
					 MIN_SPEED => MIN_SPEED_PAN_wire);
					 
	SIMPLE_COMPARATOR_PAN: Simple_comparator
		port map( INPUT => TARGET_PAN_wire,
					 FEEDBACK => POSITION_PAN_wire,
					 OUTPUT => ERROR_PAN_wire,
					 DIR => MOTOR_DIR_PAN_wire,
					 CONSTRAINER => '1');
					 

-- EXTRA --					 
	MUX_DISPLAY_1: Mux_Display
		port map( clk_50MHz => CLK,
					 bcd(15 downto 11) => "00000",
					 bcd(10 downto 0) => POSITION_TILT_wire,
					 segm => SEGMENTS,
					 an => AN,
					 clk_1kHz => CLOCK_1K_wire);

end Behavioral;