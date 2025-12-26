// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데, "+GetSexPhrase("아들아","내 딸")+"?","물어봐, 듣고 있으니까..."),"듣고 있다, 이제 말해라. "+GetSexPhrase("아들아","내 딸")+"...","세 번째로, "+GetSexPhrase("아들아","내 딸")+", 필요한 것이 있으면 말하시오.","성직자는 할 일이 많으니 네가 나를 방해하고 있구나, "+GetSexPhrase("아들아","내 딸")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 아니오, 신부님..."),"드릴 말씀이 없습니다, 용서하십시오.","나중에 물어보겠소. 용서하시오, 신부님.","실례합니다, 신부님...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "실례합니다, 신부님, 당신 교구의 성직자 중 한 분이 요아킴 메리먼이 방을 빌려 살던 집을 조사해 달라고 부탁하셨습니다...";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "그래서? 거기에 다녀왔느냐, 아들아?";
			link.l1 = "봤어. 하지만 솔직히 안 보는 게 나았을 거야. 위층 방에서 거대한 도끼를 든 해골한테 공격당했거든. 쉽진 않았지만, 그래도 내가 이겼지.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "주님, 우리 영혼을 불쌍히 여겨 주옵소서! 내 가장 두려웠던 일이 현실이 되었나이다!";
			link.l1 = "그게 다가 아닙니다, 신부님. 결국 그걸 쓰러뜨렸을 때, 여자처럼 비명을 지르더군요. 뼈를 살펴보니 장신구도 발견했으니, 실종된 여주인일 거라고 봐도 무방하겠습니다.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(성호를 그으며)... 불쌍한 하느님의 종이여, 주님께서 그녀의 영혼에 안식을 허락하시길...";
			link.l1 = "메리먼이 정말로 흑마법사인 것 같군. 어떻게 살아 있는 사람을 그런 괴물로 만들 수 있는지 전혀 모르겠어.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "요아킴 메리먼은 아주 무서운 흑마법사란다, 아들아. 내가 유럽에서 그를 알았지만, 그때는 그런 일을 할 만한 능력이 없었지. 하지만 여기 카리브 해에서는, 그가 초자연적인 힘을 얻게 해주는 무언가를 손에 넣었구나.";
			link.l1 = "메리먼을 알고 계셨습니까, 신부님?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "그렇소. 그때 나는 리스본의 어느 본당에서 소박한 신부였지. 요아킴 메리먼은 부유한 귀족이었고, 어느 순간부터 먼 나라에서 선원들이 가져온 고문서와 두루마리에 관심을 가지기 시작했소. 그는 연금술도 연구하기 시작했으나, 얼마 지나지 않아 은둔 생활에 들어갔지.\n사람들은 그의 집에서 번쩍이는 빛을 보았고, 때로는 이상한 냄새도 맡았소. 밤에는 공동묘지에서 그를 목격하기도 했지. 한 번은 그가 갓 묻힌 시신을 파내어 집으로 가져가는 걸 봤다고 하오. 결국 인내심이 바닥나자, 지역 신부가 종교재판소에 연락했지.\n경비병들이 메리먼의 집 문을 부수고 들어갔을 때, 요아킴은 이미 없었소. 비밀 통로로 도망쳤던 거요. 지하실에서는 실험실이 발견되었고, 노련한 병사들조차 그 광경에 충격과 구역질을 느꼈지. 썩고 잘린 시신들, 인간과 동물의 해골, 기이한 것들... 메리먼에 대한 공포와 증오가 극에 달해 그의 집은 순식간에 허물어졌소.\n메리먼은 흔적도 없이 사라졌지. 종교재판소는 그를 위험한 흑마법사로 간주하여 부재 중에 화형을 선고하고 수색을 시작했으나, 결국 찾지 못했소. 그리고 이제, 수년이 지난 지금, 나는 윌렘스타트 거리에서 그를 다시 보았소.";
			link.l1 = "왜 이단심문관들에게 말하지 않았지?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "아들아, 우리 교회가 종교재판소와 사이가 좋지 않다는 걸 모르느냐? 나는 빈첸토 신부와 그 불량배들은 피하고 싶구나.";
			link.l1 = "알겠습니다. 신부님, 메리먼이 어디서 힘을 얻었는지 알 것 같습니다. 그는 차빈 부족 인디언들이 숭배하던 고대 죽음의 신, 윰 시밀의 옥 해골이라는 고대 유물을 손에 넣었습니다.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "흠, 메리먼은 시체를 대상으로 마법 의식과 실험을 벌인 것으로 유명했으니, 그 말이 사실일 수도 있겠구나. 이런 끔찍한 자가 윌렘스타드를 떠나고, 네가 그가 이곳에 뿌리려 했던 악마의 씨앗을 없애 주었으니 하나님께 감사드린다. 우리는 너에게 큰 빚을 졌다, 아들아. 이 성스러운 물품들을 보상으로 받아주거라.";
			link.l1 = "감사합니다, 신부님";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "하지만 그것이 우리 고난의 끝은 아니었단다, 아들아. 최근에 나는 편지를 받았다 "+sld.name+", 아바나 교회의 주임 신부입니다. 그는 끔찍한 소식을 전해왔습니다. 쿠바 정글의 한 동굴에서 사냥꾼들이 무시무시한 괴물들, 즉 살아 움직이는 시체들을 목격했다고 합니다. 게다가 최근 정글로 들어간 사람들이 실종되는 일이 이어지고 있어 더욱 불안합니다.";
			link.l1 = "흠... 이것도 메리먼의 짓이라고 말하는 거냐?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "무슨 생각을 해야 할지 모르겠구나, 아들아. 하지만 그 흑마술사가 그렇게 강해졌다면, 군도에 사는 모든 이들이 큰 위험에 처한 셈이야. 이 악마의 하수인이 무슨 꿍꿍이를 품고 있는지 오직 하느님만이 아시겠지\n나는 정말로 바라네, 신부님 "+sld.name+" 잘못하긴 했지만, 어쨌든 하바나로 가서 그와 이야기해 주시오. 내가 한 달간 유효한 무역 허가증을 준비해 두었소. 이것만 있으면 하바나 항구에 아무런 문제 없이 들어갈 수 있을 것이오.";
			link.l1 = "알겠습니다, 신부님. 아바나로 가겠습니다.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "무슨 생각을 해야 할지 모르겠구나, 아들아. 하지만 그 흑마술사가 그렇게 강력해졌다면, 군도에 사는 모든 이들이 큰 위험에 처한 셈이다. 이 악마의 하수인이 무슨 꿍꿍이를 품고 있는지 오직 신만이 아시지.\n나는 정말로 바라네, 신부님께서 "+sld.name+" 잘못했지만, 상관없소 – 하바나로 가서 그와 이야기해 주시오.";
			link.l1 = "물론입니다, 신부님. 바로 아바나로 가겠습니다.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "그대가 진정한 교회의 아들이라니 기쁘구나. 밤낮으로 그대의 건강과 평안을 위해 기도하겠다. 내 축복과 함께 가거라. 주께서 이 불경한 세력과의 싸움에서 그대를 굳세게 하시길 바라노라.";
			link.l1 = "감사합니다, 그리고 안녕히 계십시오, 신부님.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
			AddLandQuestMark(characterFromId("Havana_Priest"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
