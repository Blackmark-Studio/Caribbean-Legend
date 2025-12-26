int iDiplomatPseudoGlobal;

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
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "patent_2";
 	}
 	
 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}
 	
 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
 	}
 	
 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "CityInfo";
 	}
 	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "다시 만나서 반갑소.";
			link.l1 = "다시 한 번 당신의 도움이 필요하오.";
			link.l1.go = "relation";
			link.l2 = "가봐야겠어.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "당신에게 거래를 제안하고 싶어."link.l4.go ="D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "자기소개를 하지. 나는 여기 있는 어떤 총독에게도 너를 추천해줄 수 있는 사람이야. 물론 공짜는 아니지만, 내 서비스를 믿어도 좋아. 내 재능에 돈을 쓰면 절대 후회하지 않을 거야.";
				link.l1 = "흥미롭군. 계속해.";
				link.l1.go = "relation";
				link.l2 = "다음에 보자.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "조건이 무엇이오?";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "이런 왕실의 관대함이라니! 당연히 동의하지!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "아니, 거래는 없어.";
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "relation":
			dialog.text = "어떻게 도와줄 수 있을지 한번 보자.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "영국과 화해하고 싶소.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "나는 프랑스와 화해하고 싶어.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "나는 스페인과 화해하고 싶어.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "나는 네덜란드와 화해하고 싶어.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "밀수업자들과 평화를 맺고 싶어.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "나에게 사략 허가장이 필요해.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "거래 허가증 있나?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "식민지 소유권에 대해 질문이 있습니다.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "있잖아, 내가 직접 처리하는 게 낫겠어.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "나는 항상 가지고 있지, 시대도 다양하게. 어느 나라의 면허장이 필요해?";
		    link.l1 = "영국 출신";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "프랑스의";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "스페인 출신";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "홀란드 출신";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "있잖아, 내가 직접 처리하는 게 낫겠어.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "기간?";
		    link.l1 = "30일";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60일";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90일";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "내 마음이 바뀌었어.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "그래서, 무역 허가증이"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gen")+" 위해 "+sti(npchar.LicenceType)+" 일 수, 가격은 "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "동의하오.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "내 마음이 바뀌었어.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "여기 있다. 항구에 들어갈 때는 우호적인 깃발을 다는 걸 잊지 마라.\n그리고 순찰대가 면허 날짜를 확인할 수도 있다는 것도 기억해.";
			link.l9 = "감사하오.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "훌륭하군! 돈이 충분해지면 다시 오시오.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "훌륭하군. 우선, 그대가 국가에 충성을 다한다는 것을 증명해야 하오"+" 그에 대한 훌륭한 봉사로 말이오. 어느 총독에게든 가시오\n"+//NationNameGenitive(sti(NPChar.nation))+" 그의 임무 몇 가지를 완수하면, 그가 면허를 내줄 거야.";
			link.l1 = "말해 보시오, "+GetAddress_FormToNPC(NPChar)+", 이 지루한 형식적인 절차를 피할 방법이 있을까?";
			link.l1.go = "patent_1";
			link.l2 = "안녕히 가시오, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "뇌물을 달라는 건가!? 내가 직접 면허증을 만들어 주길 바라는 거야?";
			link.l1 = "정확히 그렇다!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "아니. 잘 가라, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "이런 일을 할 만한 연줄은 없어. 그리고 도장과 서명이 다 찍힌 공란 면허증도 구해줄 수 없어.";
            link.l1 = "안타깝군. 잘 가라."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "알겠소, 그 일은 내가 처리해 줄 수 있소. 어떤 종류의 면허가 필요하오?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "영국 출신";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "프랑스의";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "스페인 출신";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "네덜란드 출신";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "이건 내가 직접 처리하는 게 낫겠어.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "이것은 버그입니다. 이 메시지를 보셨다면 ALexusB에게 연락해 주십시오";
                    link.l1 = "내가 보기엔 괜찮아. 네 조건에 동의하지!";
                    break;
                case HOLLAND :
                    dialog.text = "네덜란드는 거의 평화로운 나라요. 많은 친구를 사귀게 될 것이고, 적은 몇 명뿐일 것이오. 그리고 면허 자체도 비용이 적게 들 것이오 "+pchar.PatentPrice+" 페소입니다.";
                    link.l1 = "내가 보기엔 괜찮아. 네 조건에 동의하지!";
                    break;
                case FRANCE :
                    dialog.text = "프랑스의 친구와 적들이 모두 당신의 친구와 적이 될 것이오. 그들의 적에게 속한 배를 침몰시키는 것도 허락받게 될 것이오. 그리고 그 면허 자체는 비용이 들 것이오. "+pchar.PatentPrice+" 페소입니다.";
                    link.l1 = "좋아! 난 누구를 섬기든 상관없어! 프랑스도 괜찮지.";
                    break;
                case SPAIN :
                    dialog.text = "스페인에는 적이 많으니, 그 자들이 곧 그대의 적이 될 것이오! 스페인은 바다의 전사들로 이루어진 나라요. 그리고 면허 자체도 비용이 들 것이오 "+pchar.PatentPrice+" 페소입니다.";
                    link.l1 = "내가 원하던 거야! 이 보잘것없는 동전 몇 닢은 싸움과 고위 인물들의 임무에 대한 보상으로 받아라!";
                    break;
                case ENGLAND :
                    dialog.text = "솔직히 말해서, 영국 총독이 이렇게 자기 주머니를 채우는 거지. 그리고 면허 자체도 돈이 들어. "+pchar.PatentPrice+" 페소입니다.";
                    link.l1 = "좋아. 내가 밀수와 선상 습격으로 번 피의 돈을 그에게 주어라!";
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

			link.l2 = "아니, 나를 위한 게 아니야.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "우리가 거래를 성사시켜서 기쁩니다.";
			link.l1 = "안녕히 가시오, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			iDiplomatPseudoGlobal = CalculateRelationContraSum(false);
			dialog.Text = "좋아. 값이 들 거야 " + iDiplomatPseudoGlobal + " 페소입니다.";
			Link.l1 = "동의하오.";
			if(makeint(Pchar.money) < iDiplomatPseudoGlobal)
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "내 마음이 바뀌었어.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "대단히 훌륭합니다, 제가 모든 것을 정리하겠습니다. 그들이 당신과 함께 일할 것입니다.";
			Link.l99 = "고맙다.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
		break;
        // boal <--
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iDiplomatPseudoGlobal = CalculateRelationSum(i, false);
			dialog.text = "흠... 뭐라고 해야 할지 모르겠군. 물론 네가 요청한 대로 화친을 맺어줄 수는 있지. "+XI_ConvertString(Nations[i].Name+"Abl")+", 비용이 들 거야 "+FindRussianMoneyString(iDiplomatPseudoGlobal)+".";
			if(sti(pchar.money) >= iDiplomatPseudoGlobal)
			{
				link.l1 = "선택의 여지가 없는 것 같군. 내 돈 가져가.";
				link.l1.go = "relation3";
			}
			link.l2 = "아니, 그건 너무 많아. 안녕히 가시오.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "훌륭하군! 너와 거래하는 게 생각보다 쉽구나. 걱정 마라, 네 문제는 15일 안에 해결해 주겠다.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "이제 곧 네 문제는 해결될 거야. 그냥 앉아서 기다려, 더 빨리 될 수는 없어.";
			Link.l99 = "고맙다.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "어느 식민지의 소유권에 대해 이야기하고 싶으신가요?";
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
			Link.l99 = "아니. 아무것도 없어.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Colony "+GetCityName(colonies[i].id)+", 소속되어 있었소 "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+", 재포획 시도를 막기 위한 몸값은 "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "그래, 바로 내가 필요로 하던 거야.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "고맙지만 사양하겠소. 관심 없어.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "좋아, 거래는 진행 중이야. 붙잡으려는 시도는 없을 거야 "+GetCityName(colonies[i].id)+" 다시.";
			Link.l2 = "감사합니다. 좋은 하루 되십시오.";
			Link.l2.go = "exit";
			Link.l3 = "질문이 하나 더 있습니다.";
			Link.l3.go = "relation";
		break;
	}
}
