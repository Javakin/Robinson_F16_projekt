--------------------------------------------------------------------------------
--
-- MODULENAME	: PID_controller.vhd
-- PROJECT		: P&T system
-- DESCRIPTION	: See documentation
--
-- CHANGE LOG:
--------------------------------------------------------------------------------
-- DATE		ID		CHANGE
-- DDMMYY
------------------------
-- 110516	MG		Module created.
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
entity PID_controller is
	generic( dead_band: integer := 0);
				
	port( ERROR: in std_logic_vector(10 downto 0);
			OUTPUT: out std_logic_vector(7 downto 0);
			CLK: in std_logic;
			
			K_P: in std_logic_vector(5 downto 0);
			K_I: in std_logic_vector(5 downto 0);
			
			MAX_SPEED: in std_logic_vector(7 downto 0);
			MIN_SPEED: in std_logic_vector(7 downto 0));
end PID_controller;


--Architecture of entity
--------------------------------------------------------------------------------
architecture Behavioral of PID_controller is
	signal saturation: std_logic;
	signal clk_downscaled: std_logic;
	signal integrator: std_logic_vector(24 downto 0) := (others => '0');
	signal err: integer range -65535 to 65535 := 0;
	signal ERROR_temp: std_logic_vector(10 downto 0) := (others => '0');
	signal prev_ERROR: std_logic_vector(10 downto 0) := (others => '0');
	
	signal P: integer := 0;
	signal I: integer := 0;
begin

-- Inputs conversion --
	err <= conv_integer(ERROR);

-- Clock scale --
clock_scale:
	process(CLK)
		variable i: integer range 0 to 500 := 0;
	begin
		if rising_edge(CLK) then
			if i < 500 then
				i := i + 1;
				clk_downscaled <= '0';
			else
				i := 1;
				clk_downscaled <= '1';
			end if;
		end if;
	end process;
	
-- Calculate PI contributions --
	P <= conv_integer(K_P) * err; -- P contribution
	I <= conv_integer(K_I) * (conv_integer(integrator(24 downto 0)) / 128); -- I contribution, Division by delta t

-- Integration --
integration_pro:
	process(clk_downscaled)
	begin
		if rising_edge(clk_downscaled) then
			if err > dead_band then -- Deadband check
				if saturation = '0' then -- Saturation check, no wind-up
					if (conv_integer(integrator(24 downto 0)) / (128*4)) < 45 then -- I limitation
						integrator <= integrator + prev_ERROR;
					end if;
				end if;
				if integrator < 0 then -- No negative integrator
					integrator <= (others => '0');
				end if;
			else
				integrator <= (others => '0');
			end if;
			prev_ERROR <= ERROR_temp;
			ERROR_temp <= ERROR;
		end if;
	end process;
	
-- Regulate the output --
Regulator_pro:
	process(clk_downscaled)
	variable out_temp: integer;
	begin
		if falling_edge(clk_downscaled) then
			saturation <= '0'; -- Reset saturation
			out_temp := (P/8) + (I/4); -- Sum of the PI contributions
			
			if out_temp < conv_integer(MIN_SPEED) then -- Min speed limitation + no negative PI values, DIR is calculated outside of controller
				out_temp := 0;
			elsif out_temp > conv_integer(MAX_SPEED) then -- Max speed limitation + no value above 8 bit
				out_temp := conv_integer(MAX_SPEED);
				saturation <= '1'; -- Saturation on
			end if;
			
			OUTPUT <= conv_std_logic_vector(out_temp, 8);
		end if;
	end process;

end Behavioral;

