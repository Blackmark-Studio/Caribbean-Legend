// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch(Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = "说吧, 我在听";
            link.l1 = "我搞错了。 再见。 ";
            link.l1.go = "Exit";
            /* //--> 加斯科涅人的负担
            if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
            {
                link.l1 = "军官先生, 我听说你们监狱里有个叫福尔克.德吕克的人。 我能做些什么来释放他吗? ";
                link.l1.go = "Sharlie";
            }
            if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
            {
                link.l1 = "军官先生, 我又来打听囚犯福尔克.德吕克的事了。 我已经买下了他的债务权, 希望能释放他并把他交给我。 这是他的债务文件, 请看一下。 ";
                link.l1.go = "Sharlie_3";
            }    
            //< —加斯科涅人的负担 */
            
            //--> 迷你任务"德吕克" (德吕克再次入狱) 
            if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
            {
                link.l1 = "下午好, 军官。 我想打听一下我的船员... ";
                link.l1.go = "Del_Deluck";
            }
            if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
            {
                link.l1 = "这是文件, 现在释放我的人。 ";
                link.l1.go = "Del_DeluckSvoboda";
            }
            //< —迷你任务"德吕克"
        break;
        
        //--> 加斯科涅人的负担
        case "Sharlie":
            DelLandQuestMark(npchar);
            dialog.text = "啊, 那个水手? 他从我们的银行家那里借了一大笔钱, 没有偿还, 甚至还试图逃跑。 但很快就被找到了。 从那以后他就一直被关押在这里, 直到他还清债务为止。 ";
            link.l1 = "嗯。 那他待在监狱里怎么还钱呢? ";
            link.l1.go = "Sharlie_1";
        break;
        
        case "Sharlie_1":
            dialog.text = "我不在乎这个, 先生。 ";
            link.l1 = "有趣... 那这个可怜人欠了多少钱? ";
            link.l1.go = "Sharlie_2";
        break;
        
        case "Sharlie_2":
            dialog.text = "我不知道。 去问银行家吧, 他会告诉你详细情况。 ";
            link.l1 = "我知道了, 谢谢你的信息, 军官。 ";
            link.l1.go = "exit";
            pchar.questTemp.Sharlie = "bankskiper";
            LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
            AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
        break;
        
        case "Sharlie_3":
            Log_Info("你已提交债务文件");
            PlaySound("interface\important_item.wav");
            RemoveItems(pchar, "letter_open", 1);
            DelLandQuestMark(npchar);
            dialog.text = "嗯。 文件都没问题。 你真的想让我释放那个囚犯吗? ";
            link.l1 = "是的。 我需要他偿还债务, 而且我知道他可以怎么做。 ";
            link.l1.go = "Sharlie_4";
        break;
        
        case "Sharlie_4":
            dialog.text = "好吧, 我没有理由拒绝你。 德吕克很快就会被带过来。 但我必须警告你, 这只狐狸一有机会就会逃跑, 所以不要对他抱有任何幻想。 ";
            link.l1 = "我知道了, 军官。 现在我想带走我的债务人。 ";
            link.l1.go = "Sharlie_5";
        break;
        
        case "Sharlie_5":
            dialog.text = "好的, 当然。 中士! 把囚犯带过来! 福尔克.德吕克, 看来你现在有了新主人! ";
            link.l1 = "... ";
            link.l1.go = "Sharlie_6";
        break;
        
        case "Sharlie_6":
            DialogExit();
            chrDisableReloadToLocation = true;//关闭地点
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//禁止战斗
            // 冻结主角
            LAi_SetActorType(pchar);
            LAi_ActorTurnToLocator(pchar, "goto", "goto17"); // 170712
			// создаем штурмана
			ref sld;
			InitFolke("福尔克", "德吕克");
		break;
        //< —加斯科涅人的负担
        
        //--> 迷你任务"德吕克" (德吕克再次入狱) 
        case "Del_Deluck":
            DelLandQuestMark(npchar);
            dialog.text = "哈! 我说, 关于你困境的流言会让圣皮埃尔娱乐很久。 但别往心里去, 船长。 你显然是时运不济的受害者。 进来吧, 别担心: 你的领航员不会从这次谈话中逃脱的, 哈哈哈! ";
            link.l1 = "真有趣。 谢谢你, 军官。 ";
            link.l1.go = "Del_Deluck_2";
        break;
        
        case "Del_Deluck_2":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.Del_Deluck");
            pchar.questTemp.jailCanMove = true;
            AddLandQuestMark(characterFromId("Folke"), "questmarkmain");
        break;
        
        case "Del_DeluckSvoboda":
            dialog.text = "明白了, 船长。 我们会按程序办理。 ";
            link.l1 = "... ";
            link.l1.go = "Del_DeluckSvoboda_2";
            Log_Info("你已提交债务文件");
            PlaySound("interface\important_item.wav");
            RemoveItems(pchar, "letter_open", 1);
            DelLandQuestMark(npchar);
        break;
        
        case "Del_DeluckSvoboda_2":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
            chrDisableReloadToLocation = true;
            LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
            LAi_SetActorType(pchar);
            LAi_ActorTurnToLocator(pchar, "goto", "goto17");
            
            sld = CharacterFromID("Folke");
            LAi_CharacterEnableDialog(sld);
            sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
            sld.dialog.currentnode = "Del_Folke_10";
            ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto23");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocator(sld, "reload", "reload1", "FolkeStay", -1);
                                
            sld = GetCharacter(NPC_GenerateCharacter("Del_Ohranik", "sold_fra_2", "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
            LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
            ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto12");
            LAi_SetActorType(sld);
            LAi_ActorFollow(sld, CharacterFromID("Folke"), "", -1);
            
            StartQuestMovie(true, false, true);
            DoQuestCheckDelay("Del_Turma", 0.1);
        break;
        //< —迷你任务"德吕克"
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}