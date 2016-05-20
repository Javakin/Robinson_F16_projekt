--------------------------------------------------------------------------------
--
-- MODULENAME	: SPI_slave.vhd
-- PROJECT		: P&T system
-- DESCRIPTION	: SPI slave module for the FPGA, see documentation
--
-- CHANGE LOG:
--------------------------------------------------------------------------------
-- DATE		ID		CHANGE
-- DDMMYY
------------------------
-- 070416	MG		Module created.
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
entity SPI_slave is
	generic( data_width: integer := 11;
				address_width: integer := 3);
				
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
			MOTOR_ENABLE_TILT: out std_logic := '0'; -- Motor control
			MOTOR_ENABLE_PAN: out std_logic := '0';
			
			DILLER_REG: out std_logic_vector(13 downto 0);
			EV: out std_logic_vector(1 downto 0);
			COUNTER: out std_logic_vector(3 downto 0);
			
			CLK: in std_logic);
end SPI_slave;

--Architecture of entity
--------------------------------------------------------------------------------
architecture Behavioral of SPI_slave is
	signal input_shift_register: std_logic_vector(13 downto 0) := (others => '0');
	signal output_buffer: std_logic_vector(13 downto 0) := (others => '0');
	
	signal TARGET_POS_TILT_temp: std_logic_vector(10 downto 0) := "00000000000";
	signal TARGET_POS_PAN_temp: std_logic_vector(10 downto 0) := "01000011100";
	signal MAX_SPEED_TILT_temp: std_logic_vector(7 downto 0) := (others => '0');
	signal MAX_SPEED_PAN_temp: std_logic_vector(7 downto 0) := (others => '0');
	signal MIN_SPEED_TILT_temp: std_logic_vector(7 downto 0) := (others => '0');
	signal MIN_SPEED_PAN_temp: std_logic_vector(7 downto 0) := (others => '0');
	signal MOTOR_ENABLE_TILT_temp: std_logic := '0';
	signal MOTOR_ENABLE_PAN_temp: std_logic := '0';

	signal S_CLK_counter: integer range -1 to 13 := 13;
	
	signal S_CLK_event: std_logic_vector(1 downto 0) := "00"; -- Shift register to catch rising and falling edge on S_CLK
	signal SS_event: std_logic_vector(1 downto 0) := "00"; -- Shift register to catch rising and falling edge on SS
begin

	TARGET_POS_TILT <= TARGET_POS_TILT_temp;
	TARGET_POS_PAN <= TARGET_POS_PAN_temp;
	MAX_SPEED_TILT <= MAX_SPEED_TILT_temp;
	MAX_SPEED_PAN <= MAX_SPEED_PAN_temp;
	MIN_SPEED_TILT <= MIN_SPEED_TILT_temp;
	MIN_SPEED_PAN <= MIN_SPEED_PAN_temp;
	MOTOR_ENABLE_TILT <= MOTOR_ENABLE_TILT_temp;
	MOTOR_ENABLE_PAN <= MOTOR_ENABLE_PAN_temp;
	
	MISO <= output_buffer(S_CLK_counter + 1) when S_CLK_counter < 10 else MOSI; -- Set output
	
	DILLER_REG <= input_shift_register;
	EV <= SS_event;
	COUNTER <= conv_std_logic_vector(S_CLK_counter, 4);

sampling_pro:
	process(CLK)
	begin
		if rising_edge(CLK) then -- Look for events on rising edge
			S_CLK_event <= S_CLK_event(0) & S_CLK;
			SS_event <= SS_event(0) & SS;
		end if;
	end process;
	
communication_pro:
	process(CLK)
		variable motor_tilt_enable: std_logic := '0';
		variable motor_pan_enable: std_logic := '0';
	begin
		
		if falling_edge(CLK) then -- SPI coding here
			if SS_event = "01" then -- SS rising edge
				S_CLK_counter <= 13;
				
				case input_shift_register(13 downto 11) is
					when "000" => 
						TARGET_POS_TILT_temp <= input_shift_register(10 downto 0);
						
					when "001" =>
						TARGET_POS_PAN_temp <= input_shift_register(10 downto 0);
						
					when "010" =>
						MAX_SPEED_TILT_temp <= input_shift_register(7 downto 0);
						
					when "011" =>
						MAX_SPEED_PAN_temp <= input_shift_register(7 downto 0);
						
					when "100" => 
						MIN_SPEED_TILT_temp <= input_shift_register(7 downto 0);
						
					when "101" =>
						MIN_SPEED_PAN_temp <= input_shift_register(7 downto 0);
						
					when "110" =>
						MOTOR_ENABLE_TILT_temp <= input_shift_register(0);
						
					when "111" =>
						MOTOR_ENABLE_PAN_temp <= input_shift_register(0);
					
					when others => S_CLK_counter <= 13;
				
				end case;
			end if;
			
			if S_CLK_event = "01" then -- S_CLK rising edge
				
				if S_CLK_counter = 10 then
					case input_shift_register(13 downto 11) is
						when "000" => 
							output_buffer <= "000" & CURRENT_POS_TILT;
							
						when "001" =>
							output_buffer <= "000" & CURRENT_POS_PAN;
							
						when others =>
							output_buffer <= (others => '0');
					end case;
				end if;
				
				input_shift_register(S_CLK_counter) <= MOSI; -- Put data in shift register
				
				if S_CLK_counter /= -1 then -- If last entry, move to input buffer
					S_CLK_counter <= S_CLK_counter - 1; --S_CLK_counter - 1; -- Decrement counter
				end if;
				
				
			end if;
		end if;
	end process;
	
end Behavioral;

