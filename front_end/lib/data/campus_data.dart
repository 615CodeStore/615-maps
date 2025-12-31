import '../models/campus_location.dart';
import 'package:flutter/material.dart';

// 模拟辽工程校园地点数据
final List<CampusLocation> campusLocations = [
  CampusLocation(
    name: '主教学楼',
    description: '学校主要教学场所',
    icon: Icons.school,
    category: '教学',
  ),
  CampusLocation(
    name: '图书馆',
    description: '馆藏丰富的学习资源中心',
    icon: Icons.library_books,
    category: '学习',
  ),
  CampusLocation(
    name: '食堂',
    description: '提供各种美食的用餐场所',
    icon: Icons.restaurant,
    category: '生活',
  ),
  CampusLocation(
    name: '学生宿舍',
    description: '学生居住的公寓',
    icon: Icons.home,
    category: '生活',
  ),
  CampusLocation(
    name: '体育馆',
    description: '体育锻炼和比赛的场所',
    icon: Icons.sports_basketball,
    category: '运动',
  ),
  CampusLocation(
    name: '实验楼',
    description: '进行各种实验的场所',
    icon: Icons.science,
    category: '教学',
  ),
];