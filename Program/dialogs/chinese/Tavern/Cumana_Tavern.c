// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为您效劳。 您想了解什么? ",
                          "我们刚才还在说这个呢。 您一定是忘了... ", "这已经是您第三次来打扰我了... ",
                          "您像只鹦鹉一样反复问同样的话... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("您知道吗, " + Npchar.name+ ", 或许下次吧。 ", "对, 不知怎么的我就忘了... ",
                      "是的, 确实是第三次了... ", "嗯... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
            {
                link.l1 = "告诉我, 我在哪里可以找到贝琳达.德.里韦罗夫人? ";
                link.l1.go = "guardoftruth";
            }
        break;
        
        case "guardoftruth":
            dialog.text = "当然是在总督府。 她是唐.费尔南多.德.比列加斯的表妹。 您可以在午后她午睡时去那里找她, 她早上通常有事务要处理。 她现在正陷入一些麻烦, 所以请记住这一点。 但她不会介意和您交谈的。 贝琳达夫人是个好人。 ";
            link.l1 = "谢谢您! ";
            link.l1.go = "guardoftruth_1";
        break;
        
        case "guardoftruth_1":
            DialogExit();
            npchar.quest.utensil = "true";
            pchar.questTemp.Guardoftruth.Belinda = "seek";
            // 设置贝琳达
            sld = GetCharacter(NPC_GenerateCharacter("GOT_Belinda", "Belinda", "woman", "towngirl", 3, SPAIN, -1, true, "quest"));
            SetFantomParamFromRank(sld, 3, true);
            sld.name = "Belinda";
            sld.lastname = "de Ribero";
            sld.dialog.FileName = "Quest\Sharlie\guardoftruth.c";
            sld.dialog.currentnode = "belinda";
            sld.greeting = "noble_female";
            LAi_SetLoginTime(sld, 13.0, 20.0);
            LAi_SetOwnerType(sld);
            LAi_SetImmortal(sld, true);
            ChangeCharacterAddressGroup(sld, "Cumana_TownhallRoom", "barmen", "stay");
            LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}