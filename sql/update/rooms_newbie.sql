CREATE TABLE `rooms_newbie` (
  `id` int(11) NOT NULL,
  `model` varchar(150) NOT NULL,
  `wallpaper` varchar(150) NOT NULL DEFAULT '0',
  `floor` varchar(5) NOT NULL DEFAULT '0',
  `items` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `rooms_newbie`
--

INSERT INTO `rooms_newbie` (`id`, `model`, `wallpaper`, `floor`, `items`) VALUES
(1, 'model_newbie', '1501', '601', '1650;r,3,0 5,35|1048;3;4;0|1054;3;6;0|1054;2;6;0'),
(2, 'model_newbie', '607', '0', '1650;r,3,0 5,35|1049;3;5;0|1055;2;3;4|1055;4;3;4'),
(3, 'model_newbie', '1901', '301', '1650;r,3,0 5,35|1050;3;4;0|1056;3;2;4|1056;3;6;0'),
(4, 'model_newbie', '1801', '110', '1650;r,3,0 5,35|1051;3;4;0|1057;3;6;0|1057;3;2;4'),
(5, 'model_newbie', '503', '104', '1650;r,3,0 5,35|1052;3;5;2|1058;2;3;4|1058;4;3;4'),
(6, 'model_newbie', '604', '107', '1650;r,3,0 5,35|1053;3;4;0|1059;3;6;0|1059;2;6;0');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `rooms_newbie`
--
ALTER TABLE `rooms_newbie`
  ADD UNIQUE KEY `id` (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `rooms_newbie`
--
ALTER TABLE `rooms_newbie`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;