// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你想要什么? ");
            link.l1 = RandPhraseSimple("我改变主意了。 ", "我现在没什么可说的。 ");
            link.l1.go = "exit";
        break;
        
        case "info":
            dialog.text = LinkRandPhrase("你对谁感兴趣? ", "你指的是谁? ", "嗯, 是谁呢? ");
            link.l1 = "我想了解更多关于莫斯科人法代的信息。 ";
            link.l1.go = "fadey";
            link.l2 = "没谁, 当我没问。 ";
            link.l2.go = "new question";
        break;
        
        case "town":
            dialog.text = LinkRandPhrase("你想去哪里? ", "你在找什么? ", "你具体需要什么? ");
            link.l1 = "法代的家在哪里? ";
            link.l1.go = "fadey_house";
            link.l2 = "我们聊点别的吧... ";
            link.l2.go = "new question";
        break;
        
        case "fadey":
            dialog.text = RandPhraseSimple("啊, 一个重要人物。 他拥有当地的工厂, 并且与巴斯特尔的上流社会关系密切。 他口音很重, 而且非常喜欢喝酒... 但他从不喝醉。 ", "他是个大人物, 也是总督的朋友。 法代拥有一家当地工厂。 他来自一个很远很远的北方国家... 我甚至不知道它的名字。 他力气很大, 能喝下整整一桶朗姆酒而不醉。 ");
            link.l1 = "谢谢。 ";
            link.l1.go = "exit";
        break;
        
        case "fadey_house":
            dialog.text = RandPhraseSimple("从码头直走, 直到你看到广场, 左边的房子就是法代的豪宅。 ", "从总督官邸穿过广场到码头, 右边的房子就是法代的豪宅。 ");
            link.l1 = "谢谢。 ";
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}