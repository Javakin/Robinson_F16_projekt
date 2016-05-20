--------------------------------------------------------------------------------
--
-- MODULENAME	: PWM.vhd
-- PROJECT		: P&T system
-- DESCRIPTION	: Generates PWM signal, see documentation
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
entity PWM is
	generic( pwm_period: integer := 2560);
				
	port( DUTY_CYCLE:	in	std_logic_vector(7 downto 0);
			ENABLE:		in	std_logic;
			CLK:			in std_logic;
			PWM_OUT:		out std_logic);
end PWM;


--Architecture of entity
--------------------------------------------------------------------------------
architecture Behavioral of PWM is
	signal counter: integer range 0 to (pwm_period + 200) := 0;
begin

-- Output --
	PWM_OUT <= '1' when counter <= conv_integer(DUTY_CYCLE)*(pwm_period / 256) and ENABLE = '1' else '0';

-- Counting process --
counting_pro:
	process(CLK)
	begin
		if rising_edge(CLK) then
			if counter = pwm_period then
				counter <= 0;
			else
				counter <= counter + 1;
			end if;
		end if;
	end process;
end Behavioral;