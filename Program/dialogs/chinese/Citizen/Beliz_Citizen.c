// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你想做什么? ");
            link.l1 = RandPhraseSimple("我改变主意了。 ", "我现在没什么可说的。 ");
            link.l1.go = "exit";
            // 雷贝比恩, 任务"导航星"==>
            if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter"))
            {
                if (rand(1) == 0)
                {
                    link.l1 = "你有没有碰巧遇见过埃德加多.索塔船长? 你能讲讲他的事吗? 听上去他是个值得认识的人。 ";
                    link.l1.go = "Sotta1";
                    link.l2 = "你不去看"牛皮大王"的处决吗? ";
                    link.l2.go = "Lutter1";
                }
                else
                {
                    link.l1 = "告诉我, 你见到今天的英雄埃德加多.索塔船长了吗? 可惜我错过了。 他是什么样的人? 真不敢相信一个商人抓住了臭名昭著的"牛皮大王"马特! ";
                    link.l1.go = "Sotta1_1";
                    link.l2 = "我看全镇都在庆祝卢特被抓, 连那些从不出海的人都在庆祝。 ";
                    link.l2.go = "Lutter1_1";
                }
            }
            // <== 任务"导航星"
        break;
        
        case "info":
        // 替换为某些NPC的描述, 关于任务
            dialog.text = "你以为我是" + NationNameGenitive(sti(NPChar.nation)) + "的特工吗? ";
            link.l1 = "好吧... 不是。 那么再见。 ";
            link.l1.go = "exit";
            link.l2 = "那么, 还有其他问题吗? ";
            link.l2.go = "new question";
        break;
        
        case "town":
        // 替换为如何通行的描述, 关于任务
            dialog.text = "我看起来像调查局的人吗? 我不知道, 什么都不知道。 ";

            link.l1 = "你真是个糊涂虫! 走开。 ";
            link.l1.go = "exit";
            link.l2 = "那么, 还有其他问题吗? ";
            link.l2.go = "new question";
        break;
        
        // 任务"导航星"==>
        case "Sotta1":
            dialog.text = "我没和他说上话, 但我看到了他的船 --一艘重型大帆船。 在这片水域独自航行很危险, 但索塔没有护航就出海了。 ";
            link.l1 = "可能是在追逐每一枚金币, 能省则省吧。 好了, 不打扰你了。 日安。 ";
            link.l1.go = "Exit";
            
            npchar.questTemp.Sotta = true;
            pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
            AddDialogExitQuest("PZ_LongwayBelizDialog");
        break;
        
        case "Sotta1_1":
            dialog.text = "是啊, 真难以置信! 但先生, 别轻信传言。 我见过他, 就像现在见你一样清楚。 他抓住卢特是好事, 但为什么要装成商人呢? 他的举止像个军人。 我总能看出来 --我有个亲戚当了好几年兵。 ";
            link.l1 = "有意思。 好吧, 每个人都有自己的秘密。 我该走了。 谢谢你的见解。 ";
            link.l1.go = "Exit";
            
            npchar.questTemp.Sotta = true;
            pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
            AddDialogExitQuest("PZ_LongwayBelizDialog");
        break;
        
        case "Lutter1":
            dialog.text = "我已经见过那个人了。 很难相信这就是多年来恐吓我们商人的那个海盗。 他最初是怎么当上首领的? 我看到押送他的士兵 --又喊又哭又笑。 一个疯子。 ";
            link.l1 = "也许失败和即将到来的死亡对他来说太沉重了。 但没关系。 再见! ";
            link.l1.go = "Exit";
            
            npchar.questTemp.Lutter = true;
            pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
            AddDialogExitQuest("PZ_LongwayBelizDialog");
        break;
        
        case "Lutter1_1":
            dialog.text = "是的, 我也在庆祝 --很多同胞死在他手里。 不幸的人失去了父亲。 兄弟或儿子 --你明白的。 那种野蛮行径持续太久了! 要我说, 马特可能是近年来最幸运的海盗之一。 ";
            link.l1 = "运气迟早会用完的。 回头见。 ";
            link.l1.go = "Exit";
            
            npchar.questTemp.Lutter = true;
            pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
            AddDialogExitQuest("PZ_LongwayBelizDialog");
        break;
        // <== 任务"导航星"
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}