--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   00:53:54 05/20/2016
-- Design Name:   
-- Module Name:   C:/Users/black_000/Dropbox/Programmering/VHDL/Project Robinson/PT_driver/SPI.vhd
-- Project Name:  PT_driver
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: SPI_slave
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY SPI IS
END SPI;
 
ARCHITECTURE behavior OF SPI IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT SPI_slave
    PORT(
         S_CLK : IN  std_logic;
         MOSI : IN  std_logic;
         MISO : OUT  std_logic;
         SS : IN  std_logic;
         CURRENT_POS_TILT : IN  std_logic_vector(10 downto 0);
         CURRENT_POS_PAN : IN  std_logic_vector(10 downto 0);
         TARGET_POS_TILT : OUT  std_logic_vector(10 downto 0);
         TARGET_POS_PAN : OUT  std_logic_vector(10 downto 0);
         MAX_SPEED_TILT : OUT  std_logic_vector(7 downto 0);
         MAX_SPEED_PAN : OUT  std_logic_vector(7 downto 0);
         MIN_SPEED_TILT : OUT  std_logic_vector(7 downto 0);
         MIN_SPEED_PAN : OUT  std_logic_vector(7 downto 0);
         MOTOR_ENABLE_TILT : OUT  std_logic;
         MOTOR_ENABLE_PAN : OUT  std_logic;
			DILLER_REG: out std_logic_vector(13 downto 0);
			EV: out std_logic_vector(1 downto 0);
			COUNTER: out std_logic_vector(3 downto 0);
         CLK : IN  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal S_CLK : std_logic := '0';
   signal MOSI : std_logic := '0';
   signal SS : std_logic := '0';
   signal CURRENT_POS_TILT : std_logic_vector(10 downto 0) := (others => '0');
   signal CURRENT_POS_PAN : std_logic_vector(10 downto 0) := (others => '0');
   signal CLK : std_logic := '0';

 	--Outputs
   signal MISO : std_logic;
   signal TARGET_POS_TILT : std_logic_vector(10 downto 0);
   signal TARGET_POS_PAN : std_logic_vector(10 downto 0);
   signal MAX_SPEED_TILT : std_logic_vector(7 downto 0);
   signal MAX_SPEED_PAN : std_logic_vector(7 downto 0);
   signal MIN_SPEED_TILT : std_logic_vector(7 downto 0);
   signal MIN_SPEED_PAN : std_logic_vector(7 downto 0);
   signal MOTOR_ENABLE_TILT : std_logic;
   signal MOTOR_ENABLE_PAN : std_logic;
	signal DILLER_REG: std_logic_vector(13 downto 0);
	signal EV: std_logic_vector(1 downto 0);
	signal COUNTER: std_logic_vector(3 downto 0);

   -- Clock period definitions
   constant CLK_period : time := 1 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: SPI_slave PORT MAP (
          S_CLK => S_CLK,
          MOSI => MOSI,
          MISO => MISO,
          SS => SS,
          CURRENT_POS_TILT => CURRENT_POS_TILT,
          CURRENT_POS_PAN => CURRENT_POS_PAN,
          TARGET_POS_TILT => TARGET_POS_TILT,
          TARGET_POS_PAN => TARGET_POS_PAN,
          MAX_SPEED_TILT => MAX_SPEED_TILT,
          MAX_SPEED_PAN => MAX_SPEED_PAN,
          MIN_SPEED_TILT => MIN_SPEED_TILT,
          MIN_SPEED_PAN => MIN_SPEED_PAN,
          MOTOR_ENABLE_TILT => MOTOR_ENABLE_TILT,
          MOTOR_ENABLE_PAN => MOTOR_ENABLE_PAN,
			 DILLER_REG => DILLER_REG,
			 EV => EV,
			 COUNTER => COUNTER,
          CLK => CLK
        );
 
   CLK_process :process
   begin
		CLK <= '0';
		wait for CLK_period/2;
		CLK <= '1';
		wait for CLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin
		SS <= '1';
		MOSI <= '0';
		S_CLK <= '0';
		CURRENT_POS_TILT <= "00110011001";
		CURRENT_POS_PAN <= "00110011001";
		
      wait for 10 ns;
		SS <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		MOSI <= '1';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		MOSI <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		MOSI <= '1';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		MOSI <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		MOSI <= '1';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		MOSI <= '1';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		MOSI <= '1';
		
		wait for 10 ns;
		S_CLK <= '1';
		wait for 10 ns;
		S_CLK <= '0';
		
		wait for 10 ns;
		SS <= '1';

      wait;
   end process;

END;
