import 'package:flutter/material.dart';
import 'screens/main_page.dart';

void main() {
  runApp(const LiaoningEngineeringNavigationApp());
}

class LiaoningEngineeringNavigationApp extends StatelessWidget {
  const LiaoningEngineeringNavigationApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: '辽工程校园导航',
      // 黑色主题配置
      theme: ThemeData.dark().copyWith(
        primaryColor: const Color(0xFF2196F3),
        scaffoldBackgroundColor: const Color(0xFF121212),
        appBarTheme: const AppBarTheme(
          backgroundColor: Color(0xFF1E1E1E),
          elevation: 0,
        ),
        bottomNavigationBarTheme: const BottomNavigationBarThemeData(
          backgroundColor: Color(0xFF1E1E1E),
          selectedItemColor: Color(0xFF2196F3),
          unselectedItemColor: Colors.grey,
        ),
        cardTheme: CardThemeData(
          color: const Color(0xFF1E1E1E),
          elevation: 2,
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(12),
          ),
        ),
        textTheme: const TextTheme(
          bodyLarge: TextStyle(color: Colors.white),
          bodyMedium: TextStyle(color: Colors.grey),
          titleLarge: TextStyle(color: Colors.white),
          titleMedium: TextStyle(color: Colors.white70),
        ),
        visualDensity: VisualDensity.adaptivePlatformDensity,
        // 调整点击反馈效果颜色，解决深色主题下的闪烁问题
        splashColor: const Color(0xFF2196F3).withOpacity(0.2),
        highlightColor: const Color(0xFF2196F3).withOpacity(0.1),
        splashFactory: InkRipple.splashFactory,
      ),
      home: const MainPage(),
    );
  }
}