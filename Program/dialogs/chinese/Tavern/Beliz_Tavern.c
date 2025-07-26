// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为你效劳。 你想了解什么? ",
                          "我们刚刚还在谈这个。 你一定是忘了... ", "今天这已经是你第三次问我了... ",
                          "你像鹦鹉一样重复着同样的话... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 也许下次吧。 ", "对, 不知为何我忘了... ",
                      "是的, 确实是第三次了... ", "哎... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // 真理守卫
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
            {
                link.l1 = "听着, 有没有一个炼金术士, 或者说医生, 到这个镇上来? 他是意大利人, 三十岁左右, 名叫吉诺.格维内利? ";
                link.l1.go = "guardoftruth";
            }
            // 卡勒幽船
            if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
            {
                link.l1 = "听着, 我需要一个叫弗格斯.胡珀的猎人。 有人告诉我他住在这里。 我在哪里可以找到他? ";
                link.l1.go = "caleuche";
            }
        break;
        
        case "guardoftruth":
            dialog.text = LinkRandPhrase("不, 没听说过。 我们有草药师和医生, 但没有叫这个名字的。 ", "这是我第一次听到这么奇怪的名字。 不, 我们这里从没有你说的那个人来访过。 ", "我们根本没有任何炼金术士。 我们有医生, 但没有叫那个名字的。 ");
            link.l1 = "我知道了。 真遗憾。 我会继续找的! ";
            link.l1.go = "exit";
            npchar.quest.jino = "true";
        break;
        
        // 卡勒幽船
        case "caleuche":
            dialog.text = "弗格斯? 他经常来我这儿。 但他从昨天起就进丛林了。 别担心, 他一周后就会回来, 喝着朗姆酒, 吹嘘他的海上冒险。 不过, 我承认他是个该死的好猎人。 我不知道还有谁能像他那样擅长抓蛇。 ";
            link.l1 = "蛇? 嗯。 我该什么时候再来这里才能找到他? ";
            link.l1.go = "caleuche_1";
        break;
        
        case "caleuche_1":
            dialog.text = "至少三天。 注意他总是不早于下午六点来这里, 不晚于十点离开。 ";
            link.l1 = "他长什么样? 我以前从没见过他。 ";
            link.l1.go = "caleuche_2";
        break;
        
        case "caleuche_2":
            dialog.text = "留着胡子, 中年, 穿着棕色外套。 帽子和长靴。 ";
            link.l1 = "谢谢! 你帮了我大忙, 伙计。 回头见! ";
            link.l1.go = "caleuche_3";
        break;
        
        case "caleuche_3":
            DialogExit();
            AddQuestRecord("Caleuche", "8");
            int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
            SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
            npchar.quest.Caleuche = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}