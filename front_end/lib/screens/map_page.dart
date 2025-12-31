import 'package:flutter/material.dart';
import '../data/campus_data.dart';

// 地图页面
class MapPage extends StatelessWidget {
  const MapPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('辽工程校园地图'),
        actions: [
          IconButton(
            icon: const Icon(Icons.layers),
            onPressed: () {
              // 切换地图图层
            },
          ),
        ],
      ),
      body: Stack(
        children: [
          // 地图控件占位符
          Container(
            color: Colors.black,
            child: const Center(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Icon(
                    Icons.map,
                    size: 80,
                    color: Colors.grey,
                  ),
                  SizedBox(height: 16),
                  Text(
                    '地图加载中...',
                    style: TextStyle(fontSize: 18, color: Colors.grey),
                  ),
                ],
              ),
            ),
          ),
          // 悬浮常用地点列表
          Positioned(
            left: 16,
            right: 16,
            bottom: 16,
            child: Container(
              height: 150,
              padding: const EdgeInsets.all(12),
              decoration: BoxDecoration(
                color: const Color(0xFF1E1E1E),
                borderRadius: BorderRadius.circular(16),
                boxShadow: [
                  BoxShadow(
                    color: Colors.black.withOpacity(0.3),
                    blurRadius: 10,
                    offset: const Offset(0, 5),
                  ),
                ],
              ),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  const Text(
                    '常用地点',
                    style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
                  ),
                  const SizedBox(height: 8),
                  Expanded(
                    child: ListView.builder(
                      scrollDirection: Axis.horizontal,
                      itemCount: campusLocations.length,
                      itemBuilder: (context, index) {
                        final location = campusLocations[index];
                        return Padding(
                          padding: const EdgeInsets.only(right: 12),
                          child: GestureDetector(
                            onTap: () {
                              // 导航到该地点
                            },
                            child: Column(
                              children: [
                                CircleAvatar(
                                  radius: 30,
                                  backgroundColor: const Color(0xFF2196F3).withOpacity(0.2),
                                  child: Icon(
                                    location.icon,
                                    color: const Color(0xFF2196F3),
                                    size: 30,
                                  ),
                                ),
                                const SizedBox(height: 4),
                                SizedBox(
                                  width: 70,
                                  child: Text(
                                    location.name,
                                    textAlign: TextAlign.center,
                                    style: const TextStyle(fontSize: 12),
                                    maxLines: 1,
                                    overflow: TextOverflow.ellipsis,
                                  ),
                                ),
                              ],
                            ),
                          ),
                        );
                      },
                    ),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}