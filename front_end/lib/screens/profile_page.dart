import 'package:flutter/material.dart';

// 个人中心页面
class ProfilePage extends StatelessWidget {
  const ProfilePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('个人中心'),
      ),
      body: ListView(
        children: [
          // 用户信息卡片
          Container(
            padding: const EdgeInsets.all(20),
            decoration: const BoxDecoration(
              color: Color(0xFF1E1E1E),
              borderRadius: BorderRadius.only(
                bottomLeft: Radius.circular(20),
                bottomRight: Radius.circular(20),
              ),
            ),
            child: Column(
              children: [
                const CircleAvatar(
                  radius: 50,
                  backgroundImage: NetworkImage(
                      'https://via.placeholder.com/150'), // 用户头像占位符
                ),
                const SizedBox(height: 12),
                const Text(
                  '辽工程学生',
                  style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
                ),
                const SizedBox(height: 4),
                Text(
                  '电气工程学院',
                  style: TextStyle(fontSize: 14, color: Colors.grey),
                ),
              ],
            ),
          ),
          // 设置选项
          const SizedBox(height: 20),
          Column(
            children: [
              ListTile(
                leading: const Icon(Icons.settings),
                title: const Text('设置'),
                trailing: const Icon(Icons.arrow_forward_ios),
                onTap: () {
                  // 进入设置页面
                },
              ),
              const Divider(height: 1, color: Color(0xFF333333)),
              ListTile(
                leading: const Icon(Icons.help_outline),
                title: const Text('帮助与反馈'),
                trailing: const Icon(Icons.arrow_forward_ios),
                onTap: () {
                  // 进入帮助页面
                },
              ),
              const Divider(height: 1, color: Color(0xFF333333)),
              ListTile(
                leading: const Icon(Icons.info_outline),
                title: const Text('关于应用'),
                trailing: const Icon(Icons.arrow_forward_ios),
                onTap: () {
                  // 进入关于页面
                },
              ),
              const Divider(height: 1, color: Color(0xFF333333)),
              ListTile(
                leading: const Icon(Icons.exit_to_app),
                title: const Text('退出登录'),
                trailing: const Icon(Icons.arrow_forward_ios),
                onTap: () {
                  // 退出登录
                },
              ),
            ],
          ),
          // 版本信息
          const SizedBox(height: 40),
          const Center(
            child: Text(
              '辽工程校园导航 v1.0.0',
              style: TextStyle(color: Colors.grey),
            ),
          ),
        ],
      ),
    );
  }
}