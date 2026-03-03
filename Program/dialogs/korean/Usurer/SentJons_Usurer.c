// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있습니까?","무엇을 도와드릴까요?"),"얼마 전에 그 질문을 저에게 하려고 했었지...","그래, 맞지... 또 빙빙 돌고 있는 거야?","이봐, 여기서 재정은 내가 맡고 있어, 질문엔 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"으음, 내 기억이 다 어디로 갔지...","맞췄군, 미안하네...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "당신의 채무자 중 한 명에 대해 이야기하고 싶소.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "어느 것입니까?";
			if (sti(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(존칭) 분명히 Charlie Knippel입니다.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(존칭) 이렇게 태연하게 내게 말할 배짱이 있군. 내 부하에게 현상금 사냥꾼들을 보냈지.";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "찰리? 하지만 그는 더 이상 내 채무자가 아니오. 그의 빚은 오래전에 다 갚았소, 나리.";
			link.l1 = "정말입니까? 혹시 비밀이 아니라면, 누가 그랬는지 말씀해 주시겠습니까?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "그렇지 않아. 그의 선장은 리처드 플리트우드야. 진정한 신사지; 모두가 그와 같은 친구를 두어야 해.";
			link.l1 = "있지, 이제 나는 찰리의 선장이야. 플리트우드 나리가... 그를 내 밑으로 보냈지. 약속을 지키고 너한테 돈을 준 걸 알게 되어 다행이야.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "그래서 그렇게 묻는 것이군.";
			link.l1 = "그것만이 아니야. 너 찰리를 잘 알지? 그가 체포됐고, 전에 용병들이 그를 쫓으러 갔어. 왜 그런지 짐작 가는 거라도 있어? 어쨌든 네가 아주... 다양한 부류의 사람들과 거래하잖아.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "찰리가 체포됐다고? 놀랍군, 나리, 나는 전혀 몰랐소. 그의... 적들에 대해서도 마찬가지요. 그처럼 선하고 신을 두려워하는 사람인데...";
			link.l1 = "그 말엔 반박할 수 없군. 뭐, 어쨌든 고맙네. 지휘관이 내 보석금을 받아주길 바라네.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "보석금을 마련할 자금이 필요하다면 언제든 다시 찾아오시오 – 좋은 조건으로 빌려주겠소.";
			link.l1 = "하하, 진심이오? 돈놀이꾼은 언제나 돈놀이꾼일 뿐이지. 보석금쯤은 내가 직접 낼 수 있소. 잘 가시오.";
			link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;
		
		case "DTSG_KnippelDolg_VD_7":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			AddQuestRecord("DTSG", "11");
			pchar.questTemp.DTSG_AntiguaZalog = true;
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		
		case "DTSG_KnippelDolg_2":
			dialog.text = "현상금 사냥꾼들? 당신 부하를 쫓는다고? 무슨 소리요?..";
			link.l1 = "부정하지 마라. 솔직히 자백하면 신사답게 해결하지. 하지만 시치미 떼면, 거칠게 상대할 수밖에 없을 거다.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "아, 아마 착각하신 것 같습니다!.. 경비병!!! 이 사람이 저를 죽이겠다고 협박하고 있어요!";
			link.l1 = "아, 젠장...";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
			GiveItem2Character(sld, "blade_10");
			EquipCharacterByItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			LAi_SetHP(sld, 140+MOD_SKILL_ENEMY_RATE*10, 140+MOD_SKILL_ENEMY_RATE*10);
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
