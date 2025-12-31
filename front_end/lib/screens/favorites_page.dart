import 'package:flutter/material.dart';
import '../data/campus_data.dart';
import '../models/campus_location.dart';

// 收藏页面
class FavoritesPage extends StatefulWidget {
  const FavoritesPage({super.key});

  @override
  State<FavoritesPage> createState() => _FavoritesPageState();
}

class _FavoritesPageState extends State<FavoritesPage> {
  List<CampusLocation> _favoriteLocations = campusLocations.sublist(0, 3);

  void _toggleFavorite(CampusLocation location) {
    setState(() {
      if (_favoriteLocations.contains(location)) {
        _favoriteLocations.remove(location);
      } else {
        _favoriteLocations.add(location);
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('我的收藏'),
      ),
      body: _favoriteLocations.isEmpty
          ? const Center(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Icon(
                    Icons.favorite_border,
                    size: 80,
                    color: Colors.grey,
                  ),
                  SizedBox(height: 16),
                  Text(
                    '暂无收藏地点',
                    style: TextStyle(fontSize: 18, color: Colors.grey),
                  ),
                  SizedBox(height: 8),
                  Text(
                    '去搜索并收藏你常用的地点吧',
                    style: TextStyle(fontSize: 14, color: Colors.grey),
                  ),
                ],
              ),
            )
          : ListView.builder(
              itemCount: _favoriteLocations.length,
              itemBuilder: (context, index) {
                final location = _favoriteLocations[index];
                return Card(
                  margin: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
                  child: ListTile(
                    leading: CircleAvatar(
                      backgroundColor: const Color(0xFF2196F3).withOpacity(0.2),
                      child: Icon(location.icon, color: const Color(0xFF2196F3)),
                    ),
                    title: Text(location.name),
                    subtitle: Text(location.description),
                    trailing: Row(
                      mainAxisSize: MainAxisSize.min,
                      children: [
                        IconButton(
                          icon: const Icon(Icons.directions),
                          onPressed: () {
                            // 开始导航
                          },
                        ),
                        IconButton(
                          icon: const Icon(Icons.favorite, color: Colors.red),
                          onPressed: () {
                            _toggleFavorite(location);
                          },
                        ),
                      ],
                    ),
                    onTap: () {
                      // 查看详情
                    },
                  ),
                );
              },
            ),
    );
  }
}