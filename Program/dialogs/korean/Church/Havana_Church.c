// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데, "+GetSexPhrase("아들아","내 딸")+"?","물어봐, 듣고 있으니까..."),"듣고 있다, 이제 말해라. "+GetSexPhrase("아들아","내 딸")+"...","세 번째로, "+GetSexPhrase("아들아","내 딸")+", 필요한 것이 있으면 말해.","성직자는 할 일이 많으니 네가 방해하고 있군, "+GetSexPhrase("아들아","내 딸")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 아니오, 신부님..."),"할 말이 없소, 미안하오.","나중에 물어볼게. 용서해 주시오, 신부님.","실례합니다, 신부님...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "안녕하세요, 신부님. 수도원장 신부님 "+sld.name+" 빌렘스타드 교회의 사람이 나를 보냈소. 당신이 쿠바의 동굴에서 이상한 목격담을 이야기했다고 들었소.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "정글에 있는 동굴을 다녀왔습니다, 신부님.";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "신께 감사하군! 산 자들의 시체에 대한 소문이 내 귀에 들어오자마자, 나는 즉시 산티아고의 종교재판관인 빈첸토 신부님께 알렸네. 신부님께서는 조사해 보겠다고 약속하셨지만, 아직 아무런 조치도 취해지지 않았네! 아마 신부님께서 더 중요한 일들로 바쁘신 것 같아 걱정이군...";
			link.l1 = "내가 직접 알아볼 거야. 게다가 이런 소문들은 죄다 술 취한 사냥꾼들의 헛소리일 뿐이지. 그래서 종교재판소도 진지하게 받아들이지 않은 거고. 내가 직접 정글로 들어가서 내 눈으로 확인하겠어.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "내가 장담하마, 아들아, 이건 매우 중요하다. 내게 살아 움직이는 시체들에 대해 말해준 그 남자, 나는 그를 목숨 걸고 믿는다.";
			link.l1 = "좋소, 그럼 전투 준비를 하겠소. 만약 저 불경한 괴물들이 정말로 동굴에 둥지를 튼 것이라면, 내가 이 세상에서 깨끗이 쓸어버리겠소.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "주님의 축복과 함께 가거라, 아들아! 자, 이 성스러운 부적을 받아라. 네 임무에 도움이 될 것이다. 이제 가서, 악의 족속을 무찔러라!";
			link.l1 = "그때까지 안녕히 계십시오, 신부님 "+npchar.name+". 내가 끝내는 대로 바로 당신에게 돌아오겠소.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("You have received a church amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "무엇을 보았느냐, 아들아? 우리의 두려움이 괜한 것이었느냐?";
			link.l1 = "유감이지만 안 되겠습니다, 신부님 "+npchar.name+". 동굴 안에는 언데드가 들끓고 있었지만, 신의 도움으로 내가 승리했소. 이제 그놈들은 더 이상 아무도 괴롭히지 못할 것이오.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "주님을 찬양하라! 너는 정말로 그분의 징벌의 검이로구나, 아들아! 하바나 교구 전체를 대표하여 깊은 감사의 마음을 전하게 해다오. 부디, 이 성스럽게 축복된 부적들을 감사의 표시로 받아주게. 험난한 여정에서 반드시 도움이 될 것이네.";
			link.l1 = "감사합니다, 신부님 "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "또한, 평민과 귀족 모두에게 당신의 영웅적인 업적을 알릴 것이며, 밤낮으로 당신을 위해 끊임없이 기도하겠습니다.";
			link.l1 = "감사합니다, 신부님. 저도 한 가지 더 여쭙고 싶은 것이 있습니다.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "물어보거라, 아가야.";
			link.l1 = "말씀해 주시오, 신부님 "+npchar.name+", 최근에 조아킴 메리만이라는 이름의 남자가 당신네 마을에 도착했소? 중년의 나리, 콧수염과 황제 수염에 날카로운 눈빛을 가진 포르투갈인 말이오?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "이름도, 설명도 전혀 기억나지 않소. 미안하오. 이 사람이 누구요?";
			link.l1 = "메리먼은 흑마법사요. 종교재판소가 오랫동안 그를 쫓아왔소. 신부 "+sld.name+" 그리고 나는 쿠바에서 산 자처럼 움직이는 시체들이 나타난 것이 그자의 소행이라고 의심하고 있네. 얼마 전까지만 해도 그는 빌렘스타트에 살고 있었는데, 갑자기 자취를 감췄지. 그 직후, 그를 머물게 해주던 여자가 걷는 해골로 변해버렸네.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "이게 무슨 악몽이란 말인가! 즉시 종교재판관들에게, 빈첸토 신부님께 직접 알리겠소! 여기서 무슨 일이 벌어지는지 반드시 아셔야 하오! 말해 보아라, 아들아, 정글에서 사라진 사람들이... 어떻게 생각하느냐?\n";
			link.l1 = "정말이오, 동굴에 있던 그 언데드들은 분명 자네의 옛 시민들이었을 게 확실하오. 나는 쿠바에서 그 포르투갈 놈을 찾아내서 반드시 굴복시키고 싶소! 그 악당이 옛 이교도의 유물, 윰 시밀의 옥 해골을 손에 넣었더군. 유물과 인디언 주술까지 있으니, 아무도 막지 않으면 메리먼이 앞으로 더 큰 문제를 일으킬까 두렵소.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "그대는 언데드가 다시 일어날 것이라 믿는가?";
			link.l1 = "거의 확실하오. 그를 움직이는 것이 무엇인지는 모르겠으나, 그의 야망이 결코 고결하지는 않을 것이오.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "전능하신 분께서 우리에게 자비를 베푸시길! 그자를 찾아라, 아들아! 우리 성스러운 교회의 이름으로 그에게 어떤 조치든 취하는 것을 허락하겠다! 나는 즉시 사자를 산티아고로 보내 빈첸토 신부께 보고하겠다.";
			link.l1 = "그래, 그렇게 하시오. 안녕히 계시오, 신부님 "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
