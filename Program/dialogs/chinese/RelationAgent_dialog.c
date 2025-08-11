#define DIPLOMAT_SUM 80000

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;
	
	if (!CheckAttribute(npchar, "PatentPrice"))
    {
        npchar.PatentPrice = (8000 + rand(6) * 1000);
    }
    int i;
    string attrLoc;
	ref    sld;
	
    attrLoc   = Dialog.CurrentNode;
    
    if (findsubstr(attrLoc, "SetNationPatent_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индeх в концe
 	    Dialog.CurrentNode = "patent_2";
 	}
 	
 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индeх в концe
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индeх в концe
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}
 	
 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индeх в концe
		// провeрка на ужe договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else
		{
 	    	Dialog.CurrentNode = "RelationAny_Done";
 	    	npchar.quest.relation.summ = CalculateRelationSum(sti(npchar.quest.relation));
 	    }
 	}
 	
 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индeх в концe
 	    Dialog.CurrentNode = "CityInfo";
 	}
 	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "很高兴再次见到你。 ";
			link.l1 = "我需要再次使用你的服务。 ";
			link.l1.go = "relation";
			link.l2 = "我该走了。 ";
			link.l2.go = "exit";

			// 生成器 "找到的文件"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "我想给你提供一个交易。 "
				link.l4.go = "D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "让我介绍一下自己。 我是那个可以帮你在任何地方的总督面前美言几句的人。 当然, 这不是免费的, 但相信我, 我的服务物有所值。 你不会后悔为我的才能付费的。 ";
				link.l1 = "有意思。 继续说。 ";
				link.l1.go = "relation";
				link.l2 = "也许下次吧。 ";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** 生成器 - "你找到了航运文件。 " **************		
		case "D_ShipLetters_1":
			dialog.text = "你的条件是什么? ";
			s1 = "幸运的是, 我找到了一整套合法的船舶文件。 有人在找它们吗? ";
			s1 = s1 + "这艘船还在航行并且在登记册中, 所以不用担心。 那个愚蠢的船主只是把它弄丢了";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "让我看看! 是的, 这里的标记是有效的。 你是个幸运的" + GetSexPhrase("男人","女人") + "! ";
			s1 = s1 + "我正好需要这样的文件包, 我可以给你" + sti(pchar.questTemp.different.GiveShipLetters.price5) + "比索。 你觉得怎么样? ";
			dialog.text = s1;
			link.l1 = "如此慷慨! 我当然同意! ";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "不, 不交易。 ";
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; // 移除计时器 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "relation":
			dialog.text = "让我看看如何能帮你。 ";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "我想与英格兰和解。 ";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "我想与法国和解。 ";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "我想与西班牙和解。 ";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "我想与荷兰和解。 ";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
				Link.l5 = "我想与走私者和解。 ";
				Link.l5.go = "Contraband";
            }
			Link.l8 = "我需要一份私掠许可证。 ";
			Link.l8.go = "patent_0";
			
			Link.l9 = "有贸易许可证吗? ";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "我有一个关于殖民地所有权的问题。 ";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "你知道, 我最好自己处理。 ";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "我总是有不同期限的许可证。 你想要哪个国家的许可证? ";
			link.l1 = "英国人";
			link.l1.go = "SetNationLicence_0";
			link.l2 = "法国人";
			link.l2.go = "SetNationLicence_1";
			link.l3 = "西班牙人";
			link.l3.go = "SetNationLicence_2";
			link.l4 = "荷兰人";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "你知道, 我最好自己处理。 ";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
			dialog.text = "期限? ";
			link.l1 = "30天";
			link.l1.go = "NationLicenceType_30";
			link.l2 = "60天";
			link.l2.go = "NationLicenceType_60";
			link.l3 = "90天";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "我改变主意了。 ";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "那么, " + XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name + "Gen") + "的" + sti(npchar.LicenceType) + "天贸易许可证, 价格是" + FindRussianMoneyString(iSumm) + "。 ";
			link.l1 = "我同意。 ";
			if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "我改变主意了。 ";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "给你。 进入港口时别忘了升起友好旗帜。 记住巡逻队会检查许可证的日期。 ";
			link.l9 = "谢谢。 ";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "太好了! 等你有足够的钱再来。 ";
			link.l1 = "好的。 ";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "太好了。 首先, 你必须通过为国家出色服务来证明你对国家的忠诚" + 
						  "。 去任何" + //NationNameGenitive(sti(NPChar.nation)) +
						  "的总督那里, 完成他的几个任务。 然后他会授予你许可证。 ";
			link.l1 = "告诉我, " + GetAddress_FormToNPC(NPChar) + ", 我能绕过这个无聊的手续吗? ";
			link.l1.go = "patent_1";
			link.l2 = "再见, " + GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "你是说贿赂! ? 你想让我自己给你办许可证? ";
			link.l1 = "正是! ";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
				link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "不。 再见, " + GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "我没有那样的关系来做这件事。 我不能给你带有所有印章和签名的空白许可证。 ";
			link.l1 = "太遗憾了。 再见。 " + GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "好吧, 我可以为你安排。 你需要哪种许可证? ";
			if (GetPatentNation() != ENGLAND)
			{
				link.l1 = "英国人";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
				link.l2 = "法国人";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
				link.l3 = "西班牙人";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
				link.l4 = "荷兰人";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "你知道我最好自己处理。 ";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
				case PIRATE :
					dialog.text = "这是一个错误, 如果你看到它, 请联系ALexusB";
					link.l1 = "我觉得没问题。 我同意你的条件! ";
                    break;
                case HOLLAND :
					dialog.text = "荷兰几乎是一个和平的国家。 你会得到很多朋友和一些敌人。 许可证本身将花费你" + pchar.PatentPrice + "比索。 ";
					link.l1 = "看起来不错。 我同意你的条件! ";
                    break;
                case FRANCE :
					dialog.text = "法国的朋友和敌人将成为你的朋友和敌人。 你将被允许击沉他们敌人的船只。 许可证本身将花费你" + pchar.PatentPrice + "比索。 ";
					link.l1 = "听起来不错! 我真的不在乎我应该为谁服务! 法国就好。 ";
                    break;
                case SPAIN :
					dialog.text = "西班牙有很多敌人, 他们也将成为你的敌人! 西班牙是海洋战士的国家。 许可证本身将花费你" + pchar.PatentPrice + "比索。 ";
					link.l1 = "这正是我想要的! 拿这些可怜的硬币去为高层人士战斗和完成任务吧! ";
                    break;
                case ENGLAND :
					dialog.text = "老实说, 这就是英国总督将军填满自己口袋的方式。 许可证本身将花费你" + pchar.PatentPrice + "比索。 ";
					link.l1 = "很好。 把我通过走私和登船获得的血腥钱给他! ";
                    break;
			}

            if(makeint(Pchar.money) < makeint(pchar.PatentPrice))
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = "不, 这不是我想要的。 ";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "我很高兴我们达成了协议。 ";
			link.l1 = "再见, " + GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation.nobility)*DIPLOMAT_SUM);
			dialog.Text = "好的。 这将花费你" + Pchar.questTemp.Relations.sum + "比索。 ";
			Link.l1 = "我同意。 ";
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "我改变主意了。 ";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "太好了, 我会解决一切。 他们会和你合作的。 ";
			Link.l99 = "谢谢。 ";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = "嗯... 我甚至不知道该说什么。 当然, 我可以帮你与" + XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Abl") + "和解, 这将花费" + FindRussianMoneyString(iSumm) + "。 ";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "我认为我没有选择。 拿我的钱吧。 ";
				link.l1.go = "relation3";
			}
			link.l2 = "不, 太贵了。 再见。 ";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "太好了! 和你打交道出奇地容易。 别担心, 我会在15天内解决你的问题。 ";
			link.l1 = "好的。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "你的问题现在即将解决。 你只需坐着等待, 不能再快了。 ";
			Link.l99 = "谢谢。 ";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "你想讨论哪个殖民地的所有权? ";
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = "不。 没什么。 ";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "殖民地" + GetCityName(colonies[i].id) + ", 属于" + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)) + "Gen") + ", 停止收复尝试的赎金是" + FindRussianMoneyString(iSumm) + "。 ";
			if(sti(pchar.money) >= iSumm)
			{
				Link.l1 = "是的, 正是我需要的。 ";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "不, 谢谢。 我不感兴趣。 ";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "好的, 交易正在进行中。 不会再有试图夺回" + GetCityName(colonies[i].id) + "的尝试了。 ";
			Link.l2 = "谢谢。 祝你今天愉快。 ";
			Link.l2.go = "exit";
			Link.l3 = "还有一个问题。 ";
			Link.l3.go = "relation";
		break;
	}
}