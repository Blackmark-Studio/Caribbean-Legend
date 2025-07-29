// boal 25/04/04 通用教堂对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // 调用城市对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // 调用城市对话 <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("我的孩子","我的女儿") +", 不幸的是, 我不能为你提供庇护。 快跑! ", "城市卫兵正在全城搜捕你, "+ GetSexPhrase("我的孩子","我的女儿") +"。 我的教堂之门永远为受苦之人敞开, 但我不能为你提供庇护... ", ""+ GetSexPhrase("我的孩子","我的女儿") +", 你必须快跑! 不要拖延, 我求你! "), 
					LinkRandPhrase("你在教堂里做什么, 堕落的灵魂? 我要求你立刻离开, 在士兵在这里找到你并制造屠杀之前! ", "立刻离开圣殿, 你这个嘲笑者! 我永远不会保护像你这样的恶棍! ", "立刻离开我们主的圣殿! 我们这里不需要杀人犯! "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("哦, 来吧, 神父... ", "反正我也不需要你的帮助... "), 
					LinkRandPhrase("别挡我的路, 神父... ", "我会离开的, 别担心... ", "神父, 别大惊小怪了 —我真的没时间应付这个"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "... 他们将在炽热的地狱中永远燃烧! 他们永远不会看到... ";
					link.l1 = RandPhraseSimple("呃! 我打扰你了吗, 神父? ", "这就是演讲! ");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // 每月最多提供一次任务
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+ GetSexPhrase("我的孩子","我的女儿") +", 很高兴再次见到你! ";
					link.l1 = "我也很高兴看到你身体健康, "+ Npchar.name+"神父... ";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+ GetSexPhrase("我的孩子","我的女儿") +"! 很高兴看到你身体健康。 精神饱满。 主一定在我们的事情上帮助了我们, 对吗? ";
					link.l1 = "是的, "+ RandPhraseSimple("神父", "神父") +", 尽管并非总是一帆风顺, 尽管我花费了更多的时间。 精力和金钱 —你的任务完成了。 ";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "欢迎来到我们神圣的住所, "+ GetSexPhrase("我的孩子","我的女儿") +"。 ";
				link.l1 = "你好, 神父。 ";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "问候你, 艾伦, 我的孩子。 ";
					link.l1 = "也问候你, 神父。 ";
				}
				link.l1.go = "node_3";
				Link.l2 = "你不是我父亲, 再也不要那样称呼我。 ";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// 如果今天没给, 就等明天
			}
			else
			{
				Dialog.Text = "离开主的圣殿, 亵渎者! 我们没什么可谈的! ";
				Link.l1 = "我甚至不想谈。 ";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "哦, 你这个亵渎者! 走开! 不要胆敢用你的存在玷污我们主的圣殿! ";
			link.l1 = "我甚至没打算留在这里。 ";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "我很高兴, 尽管你和简有那些... 追求, 但你没有忘记我们的主和他的殿。 我能帮你什么吗? ";
			}
			else
			{
				dialog.text = "愿主保佑你和你的事务... 你来找我有什么特别的原因吗? ";
			}
    		link.l1 = RandPhraseSimple("我想做一笔捐赠。 ", "我想为一项善举捐款。 ");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("我想是时候忏悔了。 ","我想忏悔, "+RandPhraseSimple("神父。 ", "神父。 "));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("我和你有事务要谈, "+ RandPhraseSimple("神父。 ", "神父。 "),
                                           "我因事务而来, "+ RandPhraseSimple("神父。 ", "神父。 "));
    		link.l3.go = "work";
			
			//--> 传奇
			// 卡塔赫纳, 奇卡.贡萨莱斯
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "我想为一位女士的灵魂订购一场祈祷仪式。 ";
				link.l4.go = "saga";				
			}
			// 寻找解除诅咒的治疗
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // 除布里奇敦外的所有教堂
				link.l4 = "神父, 我需要帮助。 我真的病了。 某种邪恶的异教诅咒降临到我身上。 请帮助我, 我求你! ";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // 到达布里奇敦
				link.l4 = "神父, 我需要帮助。 我真的病了。 某种邪恶的异教诅咒降临到我身上。 请帮助我, 我求你! ";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // 按指示来到布里奇敦
				link.l4 = "神父, 我需要帮助。 我真的病了。 某种邪恶的异教诅咒降临到我身上。 有人告诉我你是能帮助我的人。 我求你... ";
				link.l4.go = "findtreatment";
			}
			// 为杰斯解除诅咒的治疗
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "神父, 我需要帮助。 我真的病了。 某种邪恶的异教诅咒降临到我身上。 我是被... 杰西卡.罗斯派来的。 她告诉我你能帮助我。 ";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "关于蜡烛... ";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "我准备好祈祷了, 神父。 ";
				link.l4.go = "prayer";
			}
			//< —传奇
			
			// 战舰, 30.05.11。 来自荣誉事务"神圣审判"的迷你任务。 
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "可怕的事情正在发生, 神父。 ";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "打扰了, 但我得走了。 ";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "别担心, 我的孩子。 主会看到你的苦难, 他会伸出援助之手。 永远随身携带十字架以增强你的信仰。 ";
			Link.l1 = "谢谢你, 神父。 ";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------传奇----------------------------------------------
		//--> 奇卡.贡萨莱斯
		case "saga" :
			dialog.text = "我将以1000比索谦卑地执行你的意愿。 ";
			Link.l1 = "给你, 神父 —请收下这些硬币。 ";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "谢谢你, 我的孩子。 我将为其灵魂祈祷的女士叫什么名字? ";
			Link.l1 = "她的名字是奇卡.贡萨莱斯, 她已经离开这个世界很多年了。 ";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "真奇怪... 阿尔瓦雷斯发生了什么事吗, 他让你问这个? ";
			Link.l1 = "这个阿尔瓦雷斯是谁, 我的请求有什么奇怪的? ";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "嗯, 怎么说呢! 二十年来, 我们灯塔的守卫阿尔瓦雷斯每个月都会为这位女士的灵魂订购一场祈祷仪式。 除了他之外, 还没有人关心过贡萨莱斯女士。 而你来了。 所以我想到了。 不过, 这不是我的事。 当然, 我会很高兴谦卑地执行你的意愿, 帮助迷途的灵魂找到平静和通往天堂的道路。 ";
			Link.l1 = "谢谢你, 神父。 ";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; // 移除可能的中断
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour 参与了卡塔赫纳事件
		case "saga_5" :
			dialog.text = "你还想为其他人的灵魂订购安魂曲吗? ";
			Link.l1 = "嗯... 不, 我想没有。 我需要为其他人订购吗? ";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "那么, 也许为数百名在你或你那些不敬神的同伴掠夺这座不幸城市时倒在你刀下的无辜百姓? ... 然而, 一个谦卑的神父不太可能希望触及 一 个毫无悔意地杀害普通和平公民的人的良心... ";
			Link.l1 = "神父, 你不明白... 那都是过去的事了。 此时此地, 我不打算伤害任何人。 ";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "我能相信你的话吗... ? 但无论如何, 这是圣地, 不应沾染鲜血。 所以, 我不会叫卫兵。 平安地去吧。 也许在你面对上帝的审判之前, 你还有时间赎回至少部分罪孽。 ";
			Link.l1 = "也许吧。 愿上帝的旨意成就。 ";
			Link.l1.go = "saga_4";
		break;
		// < —奇卡.贡萨莱斯
		
		// --> 解除诅咒的治疗
		case "treatment":
			dialog.text = "杰西卡? 我记得她。 可怜的罪人。 但她不是死了吗? ";
			link.l1 = "她死了, 神父。 现在她死了, 愿主安息她的灵魂。 但她向我保证你能帮助我。 ";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "是谁对你下了这些咒语, 我的孩子? 诚实地告诉我。 ";
			link.l1 = "她... 是她。 杰西卡。 ";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "上帝保佑我们! 这正是我所想的。 涉足异教仪式甚至可能将最坚强的灵魂拖入黑暗的深渊... 但是... 她真的死了吗? 或者... 没有完全死? ";
			link.l1 = "你洞察力极强, 神父。 现在她完全死了。 ";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "这个可怜的罪人向我忏悔过很多次。 仇恨从内部彻底摧毁了她。 我知道她在做什么。 我试图阻止她, 试图让她走正路, 但我所有的努力都白费了。 我警告过她那些邪恶行为的可怕危险和可怕后果... ";
			link.l1 = "是的, 神父。 我所看到的确实可怕。 但是... 我怎样才能治愈? ";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "通过祈祷的力量, 我的孩子。 通过我们圣殿里神圣的净化祈祷的力量。 你将不得不祈祷很长时间, 而且不仅为你自己。 你还必须为她祈祷。 ";
			link.l1 = "为杰西卡? ";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "是的。 为你自己和她的灵魂。 晚上十点来这里, 这样就不会有人打扰你。 你必须整夜祈祷。 带上二十支粗蜡烛, 点燃它们, 一直祈祷到它们全部燃尽。 ";
			link.l1 = "然后我就会痊愈吗? ";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "一切都在主的手中。 我会教你如何祈祷, 并为你留下圣经。 神圣祈祷的力量将摧毁降临在你身上的邪恶咒语, 也将净化可怜的杰西卡的灵魂。 ";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "我身上有二十支蜡烛。 我准备留在圣殿开始祈祷。 ";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "我身上还没有二十支蜡烛。 我会去拿的! ";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "好的, 我的孩子。 我会等你。 不要浪费时间! ";
			link.l1 = "我很快就会来... ";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "你带来二十支蜡烛了吗, 我的孩子? ";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "是的, 神父。 我身上有二十支蜡烛。 我准备留在圣殿开始祈祷。 ";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "还没有 - 但我一定会拿到的。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "好的, 我的孩子。 把它们给我, 明天晚上十点以后再来。 我会教你必要的祈祷, 并让你在教堂里过夜。 ";
			link.l1 = "谢谢你, 神父。 明天见! ";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "我已经为你准备了祈祷文本, 我的孩子。 我还留下了你的二十支蜡烛和圣经。 点燃蜡烛, 开始祈祷。 不停地祈祷; 为你的康复和这个可怜的罪人杰西卡的灵魂祈祷。 如果你忘记了什么或有不明白的地方 - 这并不重要。 从心底祈祷, 你真诚的愿望是我们的主所看重的。 ";
			link.l1 = "谢谢你, 神父。 我知道了。 ";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "我早上会回来。 我也会为你祈祷... ";
			link.l1 = "谢谢你, 神父。 ";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;// 关闭位置
		break;
		
		case "seektreatment":
			dialog.text = "什么异教咒语袭击了你, 我的孩子? ";
			link.l1 = "我不知道它们叫什么。 我身体虚弱。 行动迟缓; 我不能奔跑, 战斗也非常困难。 ";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "我听说过那些... 它们是由这些红皮肤异教的邪恶女巫带入我们世界的。 我建议你去见布里奇敦教堂的院长 - 他花了几年时间研究印第安诅咒对基督徒身体和灵魂的有害影响。 ";
				link.l1 = "他能帮助我吗? ! ";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "我听说过那些... 它们是由这些红皮肤异教的邪恶女巫带入我们世界的。 不幸的是, 我能给你的唯一建议就是多花时间祈祷, 我的孩子, 并寄希望于我们主的怜悯。 ";
				link.l1 = "但真的没有办法吗, 神父? ! 我会这样一直下去... 直到生命尽头? ";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "不要绝望, 我的孩子。 主会听到你的祈祷, 他会派来帮助。 但我建议你去其他圣地问问 - 也许有牧师知道如何解除异教诅咒。 ";
			link.l1 = "谢谢你, 神父! 我会痊愈的 - 即使我必须访问群岛上的每一个教堂! ";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "去吧, 我的孩子, 愿主保佑你。 ";
			link.l1 = "再见, 神父。 ";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "只有主能帮助你 - 还有你自己, 我的孩子。 牧师只能教你做什么和怎么做。 去见他吧。 ";
			link.l1 = "谢谢你, 神父! 你救了我! 我会立即航行到巴巴多斯! ";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "现在去吧, 愿主保佑你。 ";
			link.l1 = "再见, 神父。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "什么异教诅咒降临到你身上, 我的孩子? 让我猜猜: 你不能奔跑,  军刀对你来说太重了, 你的动作缓慢而迟钝? ";
			link.l1 = "你怎么知道的, 神父? ";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "看着你走近我的步伐, 很容易看出这一点, 我的孩子。 愿主怜悯我们有罪的灵魂... 告诉我, 我的孩子, 诚实地说 - 是谁对你下了这些魔咒? ";
			link.l1 = "你需要一个名字吗, 神父? ";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "如果你知道名字, 就说出来。 ";
			link.l1 = "她的名字是... 杰西卡.罗斯。 ";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "上帝保佑我们! 涉足异教仪式甚至可能将最坚强的灵魂拖入黑暗的深渊... 她怎么样了, 这个可怜的灵魂? ";
			link.l1 = "她死了, 神父。 ";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "但是... 她真的死了吗? 或者... 没有完全死? ";
			link.l1 = "你洞察力极强, 神父。 现在她完全死了。 ";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // 如果有的话
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // 如果有的话
		break;
		//< —传奇
		
		// 教堂 GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "... 和主的怜悯! 愿普遍的黑暗吞噬他们的灵魂, 因为他们的罪孽... ";
			link.l1 = LinkRandPhrase("神父", "神父", "父亲") + ", 你是不是有点太热心了? 你知道, 你可能会中风... ";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "好吧... 该死。 那么再见。 ";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "哦, "+ GetSexPhrase("我的孩子","我的女儿") +", 可怕的亵渎, 最恶劣的罪行刚刚发生! 从教堂偷窃! 这就像把手伸进主的口袋里! ";
			link.l1 = "哦, 我明白了... 这是怎么发生的? ";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("这很悲哀, 但我真的得走了... ", "哀悼你, 神父, 但我得走了... ", "你一定是太依赖全能者了。 你应该用更安全的锁。 好吧, 我得走了... ");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "在夜幕的掩护下, 一些恶棍抢走了教区收集的所有东西! 这些亵渎者甚至拿走了圣餐杯! ";
			link.l1 = "时代啊, 道德啊... 但是, 我希望你已经在追踪线索了? ";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "但当然! 我已经将这些亵渎的强盗逐出教会, 现在我正在对他们发出诅咒! ";
			link.l1 = "我毫不怀疑这是一个非常有效的措施。 但我的意思是更实际的东西。 例如, 组织追捕。 ";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "啊, 一个简单的神父, 受限于不抵抗邪恶的誓言, 能做什么呢? 这些恶棍肯定已经远离这里, 在酒馆里挥霍抢劫来的钱财, 或者在堕落的女人陪伴下放纵和挥霍! 我确实希望他们会在那里迎来末日! ";
			link.l1 = RandPhraseSimple("我相信, 这样的结局比被绞死更有吸引力。 不过, 我不会再打扰你了。 一切顺利。 ", "嗯, 总有一天, 我们都会去见祖先, 但我不会反对他们更快地结束。 不过, 我得走了。 祝你好运。 ");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("神父", "神父", "父亲") + ", 但我不受任何誓言的束缚, 我愿意帮助主带来报应的时刻。 ";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": // 以上 - 没有确认就退出对话 - 很奇怪, 不过
			dialog.text = "我会为你祈祷, 我的孩子! 现在去吧, 给这些骗子应得的惩罚! ";
			link.l1 = "毫无疑问, 神父";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// 我们询问的城市
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // 我们询问强盗在哪个岛上
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "嗯, 也许全能的造物主派来瘟疫和饥饿来惩罚他愚蠢的孩子们的罪孽... ";
				link.l1 = "例如, 因为骄傲或贪婪... 你为什么脸色苍白, 神父? ";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // 神父真诚地忏悔... 
			{
				dialog.text = "耶稣, 我的主, 怜悯你有罪的仆人... 你... 你找到强盗了吗? 你杀了他们吗? ";
					link.l1 = "让我们记住每一个好基督徒从摇篮里就知道的十诫: 不可杀人, 不可偷窃, 不可作假见证。 一个敬畏神的人能违反它们吗 - 更何况是一位神职人员... ?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "这里的空气真闷... 那么你找到强盗了吗? 你杀了他们吗? ";
					link.l1 = "让我们记住每一个好基督徒从摇篮里就知道的十诫: 不可杀人, 不可偷窃, 不可作假见证。 一个敬畏神的人能违反它们吗 - 更何况是一位神职人员? ! ..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+ GetSexPhrase("我的孩子","我的女儿") +"... 上帝原谅我... 这么多钱, 如此诱人... 人是软弱的, 真的软弱! 我无法忍受... 我失去了理智... 我日夜祈祷, 做补赎, 我严格禁食, 我折磨自己的肉体... 不配, 我只恳求上天放过那些可怜的人, 我因自己的贪婪而诱惑了他们... ";
			link.l1 = LinkRandPhrase("神父", "神父", "父亲") + ", 冷静点。 他们什么也没说... 而且他们肯定不会说的。 顺便说一句, 他们自愿把圣餐杯还给了我, 我把它还给你。 ";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "我的主, 我感谢你! 我的上帝, 你听到了你不配的仆人, 一个陷入污秽和罪恶的迷途罪人的祈祷... ";
			link.l1 = "任何人都可能失足... 但既然你的忏悔看起来是真诚的, 我想说: 你是个正派的人, 也是个好神父。 如果你站在法庭上, 不会有什么好结果。 是否继续为主服务由你决定 - 只有他能告诉你并指引你... ";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // 神父想给主角钱
			{
				dialog.text = ""+ GetSexPhrase("我的孩子","我的女儿") +"... 我将带着忏悔和感激的泪水从你手中接过这个杯子。 你灵魂的纯洁和高贵真的震撼了我。 我全心全意地祝福你, 并谦卑地请求你接受这" + FindRussianMoneyString(iMoneyToCharacter) + "... 我希望这足够支付你的费用? ";
				// 主角不要钱。 增加声望
				link.l1 = "这没有必要, "+ NPChar.name+"神父。 我不是最贫穷的人, 所以你最好把这笔钱用于教区的善事。 ";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// 主角要钱
				link.l2 = "谢谢你, "+ LinkRandPhrase("神父", "神父", "神父") +", 这足够了。 ";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("我的孩子","我的女儿") +"... 我将带着忏悔和感激的泪水从你手中接过这个杯子, 作为主的怜悯和宽恕的标志。 你灵魂的纯洁和高贵真的震撼了我。 我全心全意地祝福你! ";
				link.l1 = "谢谢你的祝福, "+ LinkRandPhrase("神父。 ", "父亲。 ") +"。 ";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "祝福当然是必要的, 但考虑到我所承担的相当大的费用, 用更物质的东西来支持它也不会有什么坏处... ";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "哦, 孩子, 我真的很抱歉... 我希望这" + FindRussianMoneyString(iMoneyToCharacter) + "的小额捐款足够支付你的费用? ";
			link.l1 = "是的, "+ LinkRandPhrase("神父。 ", "父亲。 ") +", 足够了, 谢谢。 ";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "我不太明白你的暗示, "+ GetSexPhrase("我的孩子","我的女儿") +", 你在说什么? ! ";
			link.l1 = "我在说贪婪会对一个人做的可怕事情, 以及我从所谓抢劫你教堂的流浪汉那里得到的... 你想说什么吗? ";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "我告诉你, 孩子, 你在和神职人员说话, 你应该表现出一点尊重, 否则你可能会后悔。 至于这个杯子 - 我以前从未见过, 但如果你愿意把它捐赠给教区, 那么... ";
			link.l1 = "等等, 神父。 在你解释清楚之前, 你不会得到它。 ";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // 只是几种不同的对话变体
			{
				dialog.text = "有什么好解释的? ! 现在, 看 - 你是个"+ GetSexPhrase("聪明人","聪明女孩") +", 你肯定明白这些骗子可能告诉你的任何事情 - 说我雇了他们 - 都是公然的谎言! 主会惩罚这些亵渎者, 不仅因为亵渎, 还因为作伪证! ";
				link.l1 = "别把主扯进来! 你怎么知道那些可怜的人跟我说了什么 - 那些你让我对付的人? 也许, 我在他们有时间说你坏话之前就杀了他们? ";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "我没什么可和你谈的! 你没有履行你在主面前的义务; 你在圣殿里发誓; 你试图敲诈一位神父, 展示一些教堂用具 - 而且还不知道你是怎么得到它的! 感谢上帝, 我没有叫辅祭来当场抓住你! ";
				link.l1 = "好吧... 我看到你已经深陷罪恶之中, 不再害怕人的审判。 但还有神圣的正义, 我们每个人迟早都要为此负责。 拿着你的'教堂用具', 想想你是否配得上触摸它, "+ Npchar.name+"神父。 ";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "请原谅我的怀疑, 神父, 因为凡人的心是软弱的, 灵魂是困惑的。 请拿走杯子, 给我你的祝福。 ";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "嗯... "+ GetSexPhrase("我的孩子... 先生... 先生... ","我的女儿... 小姐... 女士... ") +" " +pchar.name+ "... 我准备向你屈服... 并考虑我们的分歧, 可以这么说... 并用这" + FindRussianMoneyString(iMoneyToCharacter) + "的微薄款项补偿你的费用... 当然, 如果你不打算让别人卷入这件事... ";
			// 这种情况下增加声望
			link.l1 = "我不打算让任何人卷入。 拿走杯子! 而且不要以为我会接受你从教区居民口袋里偷偷摸来的金子! ";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// 这种情况下减少声望
			link.l2 = "我不打算让任何人卷入。 拿走杯子! 我拿这些金子只是因为我在你身上花费了大量的时间和金钱。 ";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// 什么都没给神父带来。 
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "坏消息, "+ LinkRandPhrase("神父", "神父", "父亲") + ": 强盗太狡猾和机智了, 所以我没能把教堂的金子拿回来... ";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// 只给神父带来了杯子。 
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "坏消息, "+ LinkRandPhrase("神父", "神父", "父亲") + ": 我设法追上了强盗, 但我唯一的战利品就是这个杯子。 ";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// 给神父带来了钱和杯子。 
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "我确信, 你会喜欢这个消息 - 我大约惩罚了强盗, 从他们那里拿回了教区的钱, 还有这个杯子。 ";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// 钱可以扣下。 
				link.l2 = LinkRandPhrase("神父", "神父", "父亲") + ", 我带来了坏消息... 我不得不花费大量时间。 精力和资源来追捕这些恶棍, 但当我找到他们时, 我发现他们已经有时间把所有东西都喝光和花光了, 除了这个杯子... ";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// 神父是小偷。 
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "哦, "+ GetSexPhrase("我的孩子","我的女儿") +", 我可能发生了什么事? 你的道路充满危险和焦虑, 而我宁静的小屋, 沉思和祈祷的领地, 是人类激情汹涌海洋中的一个宁静小岛... ";
					link.l1 = "有什么能打扰你幸福宁静的独处吗? ";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// 任务完成的短变体。 
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "我相信这个消息会让你高兴 - 我惩罚了强盗, 带回了教区的钱。 ";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// 钱可以扣下。 
				link.l2 = LinkRandPhrase("神父", "神父", "父亲") + "... 我不得不让你失望。 我在群岛上追捕强盗, 克服了许多危险和障碍, 几乎毁了自己, 最终追上了他们, 但唉... 他们已经有时间挥霍教堂的钱了。 ";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // 主角决定扣下钱... 
			if(rand(1) == 0)	// 神父相信主角但不给钱... 
			{
				if(rand(4) == 3) // 事件结果更"温和"。 
				{
					dialog.text = "哦, "+ GetSexPhrase("我的孩子","我的女儿") +"。 你的话让我陷入深深的悲伤 - 但不是绝望, 因为绝望是一种致命的罪! 主让我们面临另一个考验, 以加强我们的信仰。 ";
						link.l1 = "阿门, 神父... ";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("我的孩子","我的女儿") +", 不要对你的精神牧羊人撒谎。 ";
						link.l1 = "我真的很抱歉, 神父, 但我发誓我说的是实话。 ";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// 神父给主角钱... 
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "哦, "+ GetSexPhrase("我的孩子","我的女儿") +"。 你的话让我陷入深深的悲伤 - 但不是绝望, 因为绝望是一种致命的罪! 主让我们面临另一个考验, 以加强我们的信仰。 但你的努力和费用应该得到补偿, 尽管没有结果。 请接受这微薄的款项 - " + FindRussianMoneyString(iMoneyToCharacter) + " - 并继续你正义的道路! ";
					link.l1 = "嗯!... 谢谢你, 神父, 我会把这笔钱用于善事。 ";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("神父", "神父", "父亲") + "... 我不能接受我没有完成的工作的报酬。 你最好用这笔钱来更新祭坛。 ";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "好吧, 我相信你, "+ GetSexPhrase("我的孩子","我的女儿") +"。 主让我们面临另一个考验, 以加强我们的信仰。 ";
				link.l1 = "阿门... ";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "卑鄙, 你真的想欺骗我们的主吗? 诅咒你"+ GetSexPhrase(", 无赖",", 荡妇") +"! 出去, 记住这些钱不会给你带来任何好处! ";
				link.l1 = "怎么会这样? ! 神父! ..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // 相信了。 
			{
				dialog.text = "哦, "+ GetSexPhrase("我的孩子","我的女儿") +"。 你的话让我陷入深深的悲伤 - 但不是绝望, 因为绝望是一种致命的罪! 主让我们面临另一个考验, 以加强我们的信仰。 ";
				link.l1 = "阿门, 神父... ";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // 跳转到这里, 因为是一样的。 
			}
			else
			{
				dialog.text = "是的, 这正是和钱一起被偷走的那个杯子... 但是... 如果你拿到了它, 为什么你没有把钱带回来? 那是一笔巨款, 那些恶棍肯定不能这么快就把它花光... "+ GetSexPhrase("我的孩子","我的女儿") +", 记住, 没有比在上帝面前对你的精神牧羊人流谎和作伪证更大的罪了! ";
				link.l1 = NPChar.name+"神父, 我几乎失去了生命才得到这个花瓶, 想让你高兴。 我不会说我为此花了多少钱! ";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "出去, 感谢全能者给了我一颗温顺的心。 这是你还没有被标记为小偷和流氓的唯一原因! ";
			link.l1 = "怎么会这样? ! "+ LinkRandPhrase("神父", "神父", "父亲") +"! ..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "哦, "+ GetSexPhrase("我的孩子","我的女儿") +"。 你的话让我陷入深深的悲伤 - 但不是绝望, 因为绝望是一种致命的罪! 主让我们面临另一个考验, 以加强我们的信仰。 ";
			link.l1 = "阿门, 神父... ";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "主啊, 我感谢你! 事实上, 你是他的工具, 我的孩子! 我知道我们的天父会为你指明道路, 并为你提供所需的一切帮助。 我不停地祈祷, 并且... ";
			link.l1 = "你知道, 神父, 在这样的事情中, 武器肯定比祈祷更有用。 但是, 显然, 你的祈祷确实被听到了。 ";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+ GetSexPhrase("我的孩子","我的女儿") +", 我想适当地奖励你, 你"+ GetSexPhrase(", 就像母教会的真正骑士一样","") +"尽一切努力追... ";
			link.l1 = "神父, 你真的夸大了我微不足道的成就。 我现在让你去赞美我们的主... ";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// < —教堂任务

		case "donation":
			dialog.Text = "当然, " + GetSexPhrase("我的孩子", "我的女儿") + "。 你想向神圣的教会捐赠多少? ";
			Link.l1 = "抱歉, 神父, 我改变主意了。 ";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "我的捐赠将是微薄的 - 仅100比索。 ";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000比索。 我想这应该足够了。 ";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "我在金钱上很幸运, 所以我将捐赠5000比索。 ";
				Link.l4.go = "donation paid_5000";
			}
			//-->> 妓院老板娘捐赠任务
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "神父, 我想以他人名义进行捐赠。 我是按要求这么做的。 ";
				Link.l5.go = "HostessChurch";
			}
			//<< —妓院老板娘捐赠任务
		break;

		case "No donation":
			dialog.Text = "嗯... 好吧, 这是你的决定, 你可以改变主意。 别忘了这在审判日会被记录。 ";
			Link.l1 = "许多其他事情也会如此。 我们换个话题吧。 ";
			Link.l1.go = "node_3";
			Link.l2 = "抱歉, 神父, 但我该走了。 ";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "我代表神圣教会感谢你, " + GetSexPhrase("我的孩子", "我的女儿") + ", 感谢你的礼物。 ";
			Link.l1 = "我需要和你谈谈, 神父。 ";
			Link.l1.go = "node_3";
			Link.l2 = "抱歉, 神父, 但我该走了。 ";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "我代表神圣教会感谢你。 ";
            Link.l1 = "我需要和你谈谈, 神父。 ";
			Link.l1.go = "node_3";
			Link.l2 = "抱歉, 神父, 但我该走了。 ";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "我代表神圣教会感谢你, 感谢你的礼物。 ";
            Link.l1 = "我需要和你谈谈, 神父。 ";
			Link.l1.go = "node_3";
			Link.l2 = "抱歉, 神父, 但我该走了。 ";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "当然, " + GetSexPhrase("我的孩子", "我的女儿") + ", 我在听你说。 ";
			link.l1 = "我改变主意了。 也许下次吧。 ";
			link.l1.go = "exit";
			link.l2 = "我罪孽深重, 神父。 列举我所有的恶行一天都不够... ";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "我们每个人都是罪人, 我的孩子... ";
			link.l1 = "是的, 但我的良心上背负着成千上万条生命的沉重负担。 我抢劫并击沉船只... ";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "我希望那些船中没有悬挂" + NationNameGenitive(sti(NPChar.nation)) + "旗帜的? ";
			link.l1 = "不, 当然没有, 神父。 ";
			link.l1.go = "ispoved_3";
			link.l2 = "各种都有, 神父... ";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "那么我们的主会赦免你的这些罪。 因为这是一个残酷的时代, 通过消灭你君主的敌人, 你正在拯救他忠诚臣民的生命。 ";
			link.l1 = "谢谢你, 神父, 这是一个巨大的安慰... 我现在要走了。 ";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "主不会赦免你这样的罪! 祈祷并悔改, 悔改并祈祷! 你现在只有一条路 - 去修道院! ";
			link.l1 = "修道院得等一等。 至少这辈子不行。 再见... ";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "抱歉, " + GetSexPhrase("我的孩子", "我的女儿") + ", 但目前所有忏悔室都在使用中。 我至少半小时后才能听你忏悔。 ";
				link.l1 = "打扰了, " + RandPhraseSimple("神父", "父亲") + ", 这是另一件事。 " + PChar.GenQuest.ChurchQuest_1.PriestName + "神父, 来自" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + ", 曾经给过你神学图书馆的珍贵宝藏。 他让我把它们取回。 ";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "是什么事务把你带到这里来, " + GetSexPhrase("我的孩子", "我的女儿") + "?";
			link.l1 = "我想问你一个问题, 神父... ";
			link.l1.go = "quests"; // 链接到NPC
            link.l2 = RandPhraseSimple("我想谈谈为" + NationNameGenitive(sti(NPChar.nation)) + "教会的利益工作。 ",
                                        "教区情况如何? 你需要任何帮助吗? ");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("神父", "父亲") + ", 我想和你谈谈财务事务。 "; //(转账到贷款)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "我需要治疗。 ";
                link.l4.go = "healthAdd_1";
            }
            
			//市长任务 - 与我们的间谍建立联系
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("神父", "神父") + ", 我是应一个人的请求来这里的。 他的名字是" + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "总督。 ";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason 教堂公文
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "神父, 我从" + XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.StartCity) + "镇的一位修士那里给你带来了文件。 ";
	            link.l10.go = "Monkletter";
            }
			//< —教堂公文
			//--> Jason 运送祈祷书
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "神父, 我来自" + XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity) + "殖民地。 当地教会需要更多祈祷书, 当地修士建议我就此事见你。 ";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "父亲, 我为你的教区带来了祈祷书。 ";
	            link.l11.go = "Churchbooks_2";
            }
			//< —运送祈祷书
			link.l99 = "我改变主意了, 我有很多事要做。 ";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "那很好。 不过在这些严峻的时代, " + GetSexPhrase("我的孩子", "我的女儿") + ", 不是每个圣殿的访客都能对我们的母教会有用。 ";
				link.l1 = LinkRandPhrase("神父", "神父", "父亲") + ", 我是一个真正的基督徒, 我为我们母教会服务的意图是最真诚的。 " + GetSexPhrase("如果不是我这样忠诚的骑士, 谁会支持她? ", "") + "";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // 每月最多提供一次任务
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// 如果今天没给, 就等明天
			}	
            dialog.text = "目前教区一切平静, " + GetSexPhrase("我的孩子", "我的女儿") + "。 感谢你的提议。 ";
    		link.l2 = "好吧, 如果一切顺利, 我想我该去忙我的事了。 ";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// 如果今天没给, 就等明天
		break;
		
		// 教堂通用任务_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "嗯, 我有一个微妙的任务, 这不仅需要纯洁的意图, 还需要极大的勇气和相当的谨慎... ";
			link.l1 = LinkRandPhrase("神父", "神父", "父亲") + ", 我很乐意为你提供任何服务, 即使为此我必须直奔地狱! 愿上帝原谅我这不敬的话。 ";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "哦! 好的... 但是, 这 again 是一个非常微妙的事情... 不久前, 来自" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + "岛" + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Voc") + "的" + PChar.GenQuest.ChurchQuest_1.ToName + "院长从教堂图书馆借了一些神学著作和古代手稿给我一段时间。 因为这个请求得到了大主教的支持, 他坚持不要阻止知识之光的传播, 所以我无法拒绝, 尽管我推测海上航行的困难不会让他及时归还手稿... 你能帮我解决这个问题吗? ";
			link.l1 = "恐怕, " + LinkRandPhrase("神父", "神父", "神父") + ", 我无法为你做这件事。 这是一个非常微妙的事务, 只有真正的外交家才能成功解决。 ";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("神父", "神父", "父亲") + ", 你的任务对我来说似乎并不太复杂。 我马上就去那里。 ";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// 任务已接
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// 场景2а
			{
				dialog.text = "哦! 是的... 确实, 现在我想起来了... 但是, " + GetSexPhrase("我的孩子", "我的女儿") + ", 这些宝藏更多是精神层面而非物质层面的! 它们已经极大地帮助了我的教区居民, 将来也可能继续如此! ";
				link.l1 = "但是, " + LinkRandPhrase("神父", "神父", "父亲") + ", " + PChar.GenQuest.ChurchQuest_1.PriestName + "神父的教区居民也需要救赎, 没有这些著作, 他将缺乏神学支柱的支持, 他的布道也会缺乏灵感。 ";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// 场景2б-а和2б-б
			{
				dialog.text = "哦, 是的! .. 确实... " + GetSexPhrase("我的孩子", "我的女儿") + ", 这些宝藏更多是精神层面而非物质层面的! 它们已经极大地帮助了我的教区居民, 所以, 让我感到羞耻的是, 我'忘记'将它们归还给合法的主人... ";
				link.l1 = "确实, " + RandPhraseSimple("神父", "神父", "父亲") + ", 确实如此。 这就是为什么" + PChar.GenQuest.ChurchQuest_1.PriestName + "神父让我亲自把这些书送给他。 ";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // 场景2а
			dialog.text = "我明白, 我的孩子, 但我们不是每天都在向主祈祷:'免我们的债, 如同我们免了人的债'吗? 而且" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + "的教堂比我这个简陋的教区更富有。 ";
			link.l1 = "你当然是对的, 神父, 但我刚想到圣经中的其他经文:'不要寻求容易的道路, 因为魔鬼在那里等待我们, 道路越容易, 他的声音就越微妙, 诱惑就越强烈!'而" + PChar.GenQuest.ChurchQuest_1.PriestName + "神父已经打算就你的健忘给大主教送信 - 我刚刚才劝他不要这样做。 ";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "给... 给大主教? ! 因为这样一件小事! .. 为什么? 真的吗? 我本来就打算把这些作品寄给我亲爱的主内兄弟 - 只是没有好的机会送给他。 但在你身上, " + GetSexPhrase("我的孩子", "我的女儿") + ", 我看到了一个真正值得的主的仆人。 给 - 拿着这些书和手稿, 请安全地交给" + PChar.GenQuest.ChurchQuest_1.PriestName + "神父。 并代我向他表达最诚挚的感谢。 ";
			link.l1 = "当然, " + LinkRandPhrase("神父", "神父", "父亲") + "。 当然... ";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// 物品"手稿" -->
			AddItems(PChar, "Bible", 1);	// 给予手稿
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// 更改名称。 之后要改回来! 
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // 更改描述。 之后要改回来! 
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // 变量。 之后删除! 
			// < —物品"手稿"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// 场景2б-а和2б-б
			// 生成船长 -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // 不介意被射击的标志
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// < —生成船长
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // 场景2б-а
			{
				dialog.text = "但是, " + GetSexPhrase("我的孩子", "我的女儿") + "... 你看, 事情是这样的, 上周我遇到了'" + sld.Ship.Name + "'号船的船长, 我被叫去为一名垂死的水手主持圣餐。 令我非常高兴的是, " + GetFullName(sld) + "船长告诉我, 他正要去" + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + "。 尽管他没有保证任何条款, 但他仍然同意帮助, 并向我保证他一定会访问" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + "港。 所以我利用这个机会, 把书交给了那个善良的人, 并把它们的未来交给了主。 ";
				link.l1 = "嗯, 你确定这个船长可以信任吗? 他意识到托付给他的作品的价值和这次任务的重要性了吗? ";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // 场景2б-б
			{
				dialog.text = "哦, " + GetSexPhrase("我的孩子", "我的女儿") + "! 你就晚了几个小时! 我已经把" + PChar.GenQuest.ChurchQuest_1.PriestName + "神父的书交给了" + PChar.GenQuest.ChurchQuest_1.CapFullName + "船长。 今天早上, 那个敬畏神的人来忏悔, 并提到今天他的船要航行到" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + "。 尽管船长先生没有保证任何条款, 但他仍然同意帮助, 并向我保证他一定会访问" + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + "港。 ";
				link.l1 = LinkRandPhrase("神父", "神父", "父亲") + "... 你确定这个船长可以信任吗? 我还想知道他的船叫什么名字。 ";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "我信任人们, " + GetSexPhrase("我的孩子", "我的女儿") + ", 我们每个人都是按照主的形象和样式创造的, 每个灵魂中都燃烧着他的圣火! ";
			link.l1 = "呃。 这当然是一个有力的论据。 好吧... 那么祝福我吧, 神父, 并祝我在寻找那个船长时好运。 ";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // 船长的完整信息
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "你应该信任人们, " + GetSexPhrase("我的孩子", "我的女儿") + "。 至于他的船 - 我没什么可说的。 ";
			link.l1 = "你把珍贵的手稿给了某个船长, 甚至懒得知道他的船名? !!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "你看, " + GetSexPhrase("我的孩子", "我的女儿") + ", " + PChar.GenQuest.ChurchQuest_1.CapFullName + "船长是一个非常敬畏神的... ";
			link.l1 = "嗯, 我已经听说了。 ";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "耐心点, " + GetSexPhrase("年轻人", "年轻女士") + "! " + PChar.GenQuest.ChurchQuest_1.CapFullName + "船长是一个非常敬畏神的人, 直到今天他的船还叫着一个神职人员甚至连想都不该想。 更不用说大声说出来的名字! 今天在他忏悔时, 我向他指出了这一点。 因为, 正如圣经所说, 我们罪人必须比身体的纯洁更要保护灵魂的纯洁, 因为主拒绝让满口脏话的人进入他的王国... ";
			link.l1 = "我明白了, " + LinkRandPhrase("神父", "神父", "父亲") + ", 我明白了! " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", 一个在整个加勒比地区闻名的臭名昭著的赌徒和酒鬼, 决定根据你的建议重命名他的旧船? ";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "你洞察力很强, " + GetSexPhrase("我的孩子", "我的女儿") + "。 我不知道这艘船的新名字, 但肯定是崇高的。 ";
			link.l1 = "哦, " + RandPhraseSimple("神父", "神父", "父亲") + "... 感谢你所做的一切。 请为我有罪的灵魂祈祷... ";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "哦, 我的孩子! 我一直在热诚地祈祷, 一切似乎都以最好的方式解决了! 因为你的帮助和信仰, " + GetSexPhrase("我的孩子", "我的女儿") + ", 天堂和天使的歌唱肯定在等待着... ";
			link.l1 = RandPhraseSimple("神父。 ", "父亲。 ") + ", 我不打算很快见到圣彼得, 但愿不会。 至于生者 - 除了天堂祝福的承诺之外, 他们确实需要许多物质的东西... ";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "是的, 是的, " + GetSexPhrase("我的孩子", "我的女儿") + ", 当然。 我会给你应得的奖励。 拿着这个, 记住主会惩罚那些渴望太多世俗祝福和崇拜黄金魔鬼的愚蠢灵魂! ";
			link.l1 = "谢谢你, " + LinkRandPhrase("神父", "神父", "神父") + "。 请拿走你期待已久的书和手稿, 并为我有罪的灵魂祈祷... 再见! ";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // 领导力奖励
			AddCharacterExpToSkill(PChar, "Fortune", 50); // 幸运奖励
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // 移除船长
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // 完成, 如果有的话
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// < —教堂通用任务_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // 极好
            {
                dialog.text = "你的健康状况是" + GetHealthNameMaxSmall(pchar) + ", 伤口会自行愈合。 你只需要避免流血并照顾好自己的健康。 ";
    			link.l1 = "谢谢你, 这肯定是一种解脱。 我会尽量在一段时间内避免战斗。 ";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "你的健康状况是" + GetHealthNameMaxSmall(pchar) + ", 虽然伤口会自行愈合, 但你应该注意。 ";
    			link.l1 = "为此需要做什么? ";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "为什么我的健康会恶化? ";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "这很简单, " + GetSexPhrase("我的孩子", "我的女儿") + "。 每次受伤时你都会受到伤害。 这不会不留痕迹。 每次受伤你的健康都会恶化, 结果你会变得更虚弱。 你的船员看到一个虚弱的船长, 会失去对你的尊重。 然而, 你会变得更加小心, 自卫能力会暂时提高。 休息和尽量减少伤口将帮助你保持体力。 ";
			link.l1 = "感谢你的开导。 ";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "祈祷和戒除暴力, " + GetSexPhrase("我的孩子", "我的女儿") + "。 然后主会把你失去的还给你。 ";
			link.l1 = "但你能为我祈祷吗? ";
			link.l1.go = "healthAdd_3";
			link.l2 = "所以没有办法? 嗯... 你真的让我放心了, 谢谢。 ";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "我? 这很可能。 但你将不得不向我们的教区捐款。 ";
    			link.l1 = pcharrepphrase("多少? ", "很高兴! 多少? ");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "我想我自己能行... ";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = "" + GetSexPhrase("我的孩子", "我的女儿") + ", 我已经在为你的健康祈祷了。 这些祈祷将占用我直到月底的所有时间。 ";
    			link.l1    = "谢谢你, " + RandPhraseSimple("神父。 ", "神父。 ");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "十万比索将是治愈奇迹的足够费用。 ";
			link.l1 = pcharrepphrase("什么? !! 你完全疯了吗? 等我抢了几个教堂后会付这么多钱的! ", "这对我来说太多了。 他们说的是实话 - 健康是金钱买不到的。 ");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "我同意! ";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // 可以不检查, 因为显然小于51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "好的。 你的健康会稍微改善。 但你仍然需要避免冲突并好好照顾自己, 否则这种效果会消失。 我需要花整整一个月为你易逝的身体祈祷。 ";
			link.l1 = "谢谢。 如果有什么事, 我一个月后再来看你。 ";
			link.l1.go = "exit";
		break;
		
		//妓院老板娘捐赠任务
		case "HostessChurch":
			dialog.text = "那位捐款的善良灵魂是谁? ";
			link.l1 = "嗯... 是当地妓院的老板娘。 ";
			link.l1.go = "HostessChurch_call";
			link.l2 = "我更愿意保密名字。 可以匿名捐赠, 对吗? ";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //返回标志
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //随机基于幸运
				{
					dialog.text = "你是个罪人, 却为罪人请求? 事实上, 你最好先想想自己的灵魂, 我们都会出现在主面前! ";
					link.l1 = "这是真的。 我希望我们的主会对我仁慈... 那么, 捐赠呢? ";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "你这撒旦的使者, 退去吧! 拿着你这不洁的钱出去! ";
					link.l1 = "怎么会这样, 神父? ! 我们诚心来找你, 而你... ";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //随机基于魅力
				{
					dialog.text = "我很高兴你在帮助罪人找到通往我们主的道路。 为此你将在天堂得到回报! ";
					link.l1 = "那太好了! 那么, 捐赠呢? ";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "我不能接受从罪恶中获得的钱。 把它还给那个堕落的女人, " + GetSexPhrase("我的孩子", "我的女儿") + "。 没有人能通过金钱找到上帝的道路。 ";
					link.l1 = "很遗憾你拒绝了她。 确实很遗憾。 ";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "接受这笔钱, 甚至不知道它来自哪里... ";
				link.l1 = "是的, 神父, 正是如此。 请接受这份发自内心的捐赠! ";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "接受这笔钱, 甚至不知道它来自哪里? 你疯了吗? ! 如果这笔钱沾满了鲜血呢! ";
				link.l1 = "神父, 所有的钱都沾满了鲜血... ";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "我接受, " + GetSexPhrase("我的孩子", "我的女儿") + "。 去告诉你那个堕落的女人。 ";
			link.l1 = "好的, 神父。 谢谢你。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//捐赠成功或失败的标志
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "我接受, " + GetSexPhrase("我的孩子", "我的女儿") + "。 告诉你的那位捐赠者。 ";
			link.l1 = "好的, 神父。 谢谢你。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//捐赠成功或失败的标志
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "出去, 地狱之子, 再也不敢在这里露面! ";
			link.l1 = "呵, 如你所愿。 ";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//捐赠成功或失败的标志
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "这是我的决定。 平安地去吧, " + GetSexPhrase("我的孩子", "我的女儿") + "。 ";
			link.l1 = "再见, 神父。 ";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//捐赠成功或失败的标志
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "你就是这么想的, 亵渎者? ! 立即离开圣殿, 再也不敢在这里露面! ";
			link.l1 = "哦, 真的吗? 没关系, 我这就走... ";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//捐赠成功或失败的标志
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason 教堂公文
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "我几乎失去了再次见到这些文件的希望。 你为什么花了这么长时间, 我的孩子? ";
				link.l1 = "这是... 意外情况, 神父。 ";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "我一直在等这些文件, 孩子。 谢谢你的快速送达。 请接受这些硬币, 并带着我的祝福离开。 ";
				link.l1 = "谢谢你, 神父。 能帮助神圣教会是我的荣幸! ";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "我们都在上帝的手中, 我的孩子... 谋事在人, 成事在天。 把这些文件交给我, 平安地去吧。 ";
			link.l1 = "给你, 神父。 祝你一切顺利! ";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//替换为所需
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "上帝的祝福, 我的孩子。 愿全能者在你的旅途中保佑你! ";
			link.l1 = "再见, 神父。 ";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //移除计时器
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//替换为所需
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//< —教堂公文
		
		//--> Jason 运送祈祷书
		case "Churchbooks":
			dialog.text = "你被派来从我们这里拿祈祷书 - 给" + XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity + "Gen") + "的教堂? 好吧。 我有一个装有三十本祈祷书的包裹。 拿着吧, 我的孩子。 ";
			link.l1 = "谢谢你, 神父。 再见! ";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "愿主在你的旅途中保佑你! 平安地去吧... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//放置相应物品
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "谢谢你的帮助, 我的孩子, 尽管来迟了。 ";
				link.l1 = "我被意外情况耽搁了, 神父。 ";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "谢谢你的帮助, 我的孩子。 你及时带来了这些书。 请接受这个神圣的护身符作为奖励 - 它会在最黑暗的时刻救你脱离危险。 ";
				link.l1 = "谢谢你, 神父。 能帮助神圣教会是我的荣幸! ";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "一切都在上帝的手中, 我的孩子。 平安地去吧! ";
			link.l1 = "再见, 神父。 ";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//替换为所需
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "愿上帝保佑你, 我的孩子。 愿全能的主保佑你一路平安! ";
			link.l1 = "再见, 神父。 ";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймeр patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//замeнить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("你已获得'" + XI_ConvertString(pchar.GenQuest.Churchbooks.Item) + "'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь мeдом нe казалась... Какиe сцeны будут в квeстe, опрeдeляeм в самом началe.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("教堂任务生成器1: 关键场景 - 2A (直接从牧师处获取手稿)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("教堂任务生成器1: 关键场景 - 2B-A (寻找船长。 有关于他的完整信息).");
		break;
		
		case "2": // 这个标志我们已经不检查了, 因为如果没有上面的, 肯定有这个
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("教堂任务生成器1: 关键场景 - 2B-B (寻找船长。 船名未知)."); 
		break;
	}
}