// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么样的问题啊, " + GetSexPhrase("我的孩子", "我的孩子") + "? ", "但说无妨, 我在听着呢…"), "我在听呢, 现在就说吧, " + GetSexPhrase("我的孩子", "我的孩子") + "…", "这都第三次了, " + GetSexPhrase("我的孩子", "我的孩子") + ", 需要什么就直说。 ",
                          "神职人员事务繁多, 你这是在打扰我呢, " + GetSexPhrase("我的孩子", "我的孩子") + "…", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改主意了…", "现在先不问了, 神父…"), "没什么想说的了, 抱歉。 ",
                      "我回头再问吧, 神父, 还请原谅。 ", "恕罪, 神父…", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";        
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
            {
                link.l1 = "神父, 我来向您请教一件不寻常的事。 不久前, 一个名叫盖伊.马沙的私掠船船长向您的教区捐赠了 一 件非常珍贵的物品 --一枚镶嵌天青石的黄金胸饰十字架。 这是真的吗? ";
                link.l1.go = "guardoftruth";
            }
        break;
        
        case "guardoftruth":
            dialog.text = "哦, 是的, 我的孩子! 这是我们教区最珍贵的物品, 我这辈子都没见过如此华丽的器物! 但你为什么问这个呢, 我的孩子? 你为什么对这枚十字架感兴趣? ";
            link.l1 = "神父, 我知道这可能让您不悦, 但这枚十字架是从另一个教区偷来的, 而且盗窃时还杀害了一位神职人员。 向您捐赠此物的人是个杀人犯。 ";
            link.l1.go = "guardoftruth_1";
        break;
        
        case "guardoftruth_1":
            dialog.text = "我们都有罪, 我的孩子, 但指控神职人员谋杀是很严重的。 你有证据吗? 这枚十字架是从哪个教区偷的? ";
            link.l1 = "我的话还不够证明吗? 这枚十字架是从圣地亚哥的教区偷的, 必须物归原主。 ";
            link.l1.go = "guardoftruth_2";
        break;
        
        case "guardoftruth_2":
            dialog.text = "圣地亚哥? 那不是西班牙的城市吗? 我的孩子, 你让我很惊讶…";
            link.l1 = "神父, 在上帝面前人人平等。 西班牙人跟我们一样是基督徒, 国家间的分歧不应影响信徒的情感。 我恳求您把这枚十字架归还给圣地亚哥教区。 ";
            link.l1.go = "guardoftruth_3";
        break;
        
        case "guardoftruth_3":
            dialog.text = "我的孩子, 你难道不明白这枚十字架是虔诚的基督徒献给我们教区的礼物吗? 不, 我的孩子, 我不能按你说的做。 ";
            link.l1 = "您难道不在乎这枚十字架沾染了鲜血吗? 无论是不是西班牙神职人员的血, 那都是鲜血啊。 ";
            link.l1.go = "guardoftruth_4";
        break;
        
        case "guardoftruth_4":
            dialog.text = "我的孩子, 你没有拿出任何证据, 我不能盲目相信你的话。 这枚十字架会留在我们教区, 这是我的最终决定。 另外, 你在这件事上帮助西班牙人, 让我很不安。 ";
            link.l1 = "既然如此, 那就再见了, 神父…";
            link.l1.go = "guardoftruth_5";
        break;
        
        case "guardoftruth_5":
            DialogExit();
            npchar.quest.utensil = "true";
            pchar.questTemp.Guardoftruth.Baster_church = "seek";
            AddQuestRecord("Guardoftruth", "27");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}