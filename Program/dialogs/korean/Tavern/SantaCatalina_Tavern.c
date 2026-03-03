// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("물론이지, Helen. 무슨 일이야?","아, 드디어 뭘 원했는지 기억났어?","정말 괜찮은 거 맞아? 점점 걱정되는데. 의사한테 한번 가보는 게 어때? ","알겠어, Helen. 좀 자고, 신선한 공기도 쐬고—그러니까, 잠깐 쉬어. 그 다음에 다시 와. 응?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("아니, 별일 없어.","아니, 아니, 폐를 끼쳐 미안하오.","아마 네 말이 맞을 거야...","그래, 네 말이 맞는 것 같아. 그게 제일 좋은 방법이지.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 내게 질문하려고 했었지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안, 그 질문을 네가 꺼낸 게 벌써 세 번째야...","또 질문이 있나 보군?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","그래, 정말 이번이 세 번째야...","아니, 무슨 질문이야?…",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "들어봐, "+npchar.name+", Jan Svenson이 누구고, 어떻게 그를 찾을 수 있지?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "이봐, 이 마을에 연금술사나 의사가 온 적 있나? 이탈리아인이고, 서른 살쯤 된 남자인데, 이름이 지노 그비네일리야. 그에 대해 들은 거 있어?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "내가 숲의 악마가 누군지 모르는 사람을 만난 건 이번이 처음이군. 그 별명은 스페인 놈들이 붙인 거야, 그리고 그 프로비던스 섬 출신 사략선장의 목에 금화 자루 하나를 걸었지, 벌써 15년 전 일이야! 그래, 세월이 참 빠르지... 사람들은 벌써 우리 얀을 잊기 시작했어. 어쩌면 이제 그도 정말 쉴 때가 된 걸지도 모르지.";
			link.l1 = "여기에 막 도착해서 아는 게 별로 없어...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "과거에 관심이 있다면 역사책을 팔 수 있지. 많은 사람들이 그걸 위해 큰돈을 내겠지만, 나는...";
			link.l2 = "핑계 대지 마! 내가 질문했잖아. 다시 묻지: 얀 스벤손은 어디에 사는 거지? 그와 중요한 얘기를 해야 해.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "그 사람은 우리 시장 저택 맞은편, 분수 옆에 있는 대저택에 살고 있어요.\n하지만 지금은 힘든 시기를 겪고 있으니, 정말 중요한 일이 아니라면 괴롭히지 않는 게 좋겠소.";
			link.l1 = "왜 그러지?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "그가 가장 아끼던 아가씨 헬렌, 일명 룸바, 그의 고(故) 친구 션 맥아더의 딸이 사라졌어. 편히 쉬시오, 영감님... 얀은 자식이 없어서 그 어린 악동을 친딸처럼 여겼지. 그런데 그 아가씨가 자신의 스쿠너 '레인보우'와 전 선원들과 함께 흔적도 없이 사라져버렸어\n그 아가씨가 안됐지. 보기 드문 미인에 머리도 비상했어. 불처럼 뜨겁고 당찬 성격이라서 다들 룸바라고 불렀지! 그녀의 아버지가 아는 걸 전부 가르쳐줬고, 배도 물려받았으며, 모든 선원이 그녀 곁을 지켰어. 바다에서 잔뼈 굵은 늙은 뱃사람들조차 그녀를 선장으로 인정했지...";
			link.l1 = "여자 해적이라고? 그녀에게 무슨 일이 있었던 거지?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "누가 알겠어... 일주일이 그리 긴 시간은 아니지만, 맥아더의 미망인은 딸에게 무슨 일이 생겼다고 확신하고 있고, 그걸 스벤손에게도 납득시켰지. 그래서 스벤손이 부하들을 불러 모아 직접 수색을 시작했지만, 아직 아무 소득도 없어. '레인보우'와 그 선원들은 그냥 사라져 버렸지\n글래디스를 어디서 찾을 수 있는지 알려줄 수 있지, 은화 천 닢만 주면.";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "자네 지식이 꽤 비싸군, 하지만 흥미가 생겼어. 돈은 여기 있다. 그녀는 어디에 있지?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "하지 마. 필요하면 내가 직접 할 거야. 잘 있어, 이야기 고마워!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "그녀의 집은 부두 옆, 계류장 왼쪽에 있어. 하지만 아마 거기엔 없을 거야. 하루 종일 요새 성벽 근처를 맴돌면서 사랑하는 딸을 기다리고 있지. 이미 눈물이 다 마를 정도로 울었을 거야.";
			link.l1 = "이야기 고마워! 잘 가라, 친구!";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("아니, 못 들어봤어. 우리한텐 약초사랑 의원들이 있지만, 그런 이름을 가진 사람은 없어.","이렇게 이상한 이름은 처음 들어보네. 아니, 네가 말한 그 남자는 우리한테 온 적 없어.","여기엔 연금술사 같은 건 전혀 없어. 의사는 있지만, 그런 이상한 이름 가진 사람은 없어.");
			link.l1 = "알겠소. 안타깝군. 계속 찾아보겠소!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
