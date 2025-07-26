// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = RandPhraseSimple("什么问题? ", "你想做什么? ");
            link.l1 = RandPhraseSimple("我改变主意了。 ", "我现在没什么可说的。 ");
            link.l1.go = "exit";
            // 杰森, 海龟汤任务
            if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
            {
                link.l1 = "我在找琼斯先生。 你认识他吗? ";
                link.l1.go = "terrapin";
            }
        break;
        
        case "terrapin":
            if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10%概率或计数达标
            {
                dialog.text = "这儿叫琼斯的人很多。 我知道最有名的是福克斯上校的副官本杰明.琼斯。 他通常在团部总部接待访客。 ";
                link.l1 = "他有个叫莫莉的妹妹吗? ";
                link.l1.go = "terrapin_yes";
            }
            else
            {
                dialog.text = LinkRandPhrase("你要找哪个琼斯? 我至少认识二十多个... ", "我们这儿琼斯太多了, 你得说得更具体些。 ", "这儿有很多琼斯, 还有约翰逊和杰克逊。 你得说清楚点, 明白吗? ");
                link.l1 = "他有个成年妹妹叫莫莉, 听说她是个罕见的美人? ";
                link.l1.go = "terrapin_no";
            }
            npchar.quest.terrapin = "true";
        break;
        
        case "terrapin_no":
            dialog.text = RandPhraseSimple(LinkRandPhrase("嗯, 恐怕我帮不了你。 ", "不, 我不认识他。 ", "哈! 如果我认识的莫莉.琼斯算罕见美人, 那福克斯上校就是教区神父了。 "), LinkRandPhrase("我认识几个莫莉.琼斯, 其中一个有兄弟, 但... 她不是你要找的那个。 只有和猿猴一起生活的人才会称她为'罕见美人'。 ", "抱歉, 我认识的所有琼斯都没有姐妹。 ", "抱歉, 我帮不了你, 问问别人吧。 "));
            link.l1 = "明白了, 抱歉打扰。 ";
            link.l1.go = "exit";
            pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count) + 1;
        break;
        
        case "terrapin_yes":
            dialog.text = "是的, 但她与其做妹妹不如做哥哥。 这个壮实姑娘可能因为长相丑陋嫁不出去。 ";
            link.l1 = "多谢。 ";
            link.l1.go = "terrapin_yes_1";
        break;
        
        case "terrapin_yes_1":
            DialogExit();
            AddQuestRecord("Terrapin", "2");
            pchar.questTemp.Terrapin.Benjamin = true;
            DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
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
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}