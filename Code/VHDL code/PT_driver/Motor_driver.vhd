--------------------------------------------------------------------------------
--
-- MODULENAME	: Motor_driver.vhd
-- PROJECT		: P&T system
-- DESCRIPTION	: Driver for the motor, see documentation
--
-- CHANGE LOG:
--------------------------------------------------------------------------------
-- DATE		ID		CHANGE
-- DDMMYY
------------------------
-- 310316	MG		Module created.
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
entity Motor_driver is
	port( CLK: 					in std_logic;
			ENABLE: 				in std_logic;
			MOTOR_DIR: 			in std_logic;
			DUTY_CYCLE:			in std_logic_vector(7 downto 0);
			
			ENABLE_OUT: out std_logic;
			MOTOR_CONTROL_1: 	out std_logic;
			MOTOR_CONTROL_2: 	out std_logic);
end Motor_driver;


--Architecture of entity
--------------------------------------------------------------------------------
architecture Behavioral of Motor_driver is
	signal PWM_wire: std_logic;
	
-- Init PWM module --
	component PWM
	port( DUTY_CYCLE:			in	std_logic_vector(7 downto 0);
			ENABLE:				in	std_logic;
			CLK:					in std_logic;
			PWM_OUT:				out std_logic);
	end component;
	
begin
-- Output --
	MOTOR_CONTROL_1 <= PWM_wire when MOTOR_DIR = '1' else '0';
	MOTOR_CONTROL_2 <= PWM_wire when MOTOR_DIR = '0' else '0';
	ENABLE_OUT <= ENABLE;
	
-- PWM component setup --
	PWM_GENERATOR: PWM port map(DUTY_CYCLE, ENABLE, CLK, PWM_OUT => PWM_wire);
	
end Behavioral;

