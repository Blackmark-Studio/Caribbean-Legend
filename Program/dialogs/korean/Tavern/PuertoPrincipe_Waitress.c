// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("질문들, "+GetAddress_Form(NPChar)+"?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("음, 이게 다 무슨 짓이야, "+GetAddress_Form(NPChar)+"? ","또 이상한 질문이야? 자기야, 가서 럼주라도 한잔 해...")+"","오늘 하루 동안만 해도, 이 질문을 세 번째로 꺼내는군..."+GetSexPhrase(" 이게 애정의 표시인가?","")+"","질문이 더 있나 보군, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었어","지금은 할 말이 없어."),"아니, 아니, 이쁜이...","말도 안 돼, 자기야...","아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "몇 가지 물어볼 게 있어. 진 통이 사라진 날, 네가 이 선술집에서 일하고 있었지? 그날 여기서 무슨 일이 있었는지 말해 줄 수 있겠어?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "나... 나도 뭐라고 해야 할지 모르겠어. 모든 게 평범했고, 특별한 일은 없었어.";
			link.l1 = "그래? 별일 없었어? 'Sea Beast'에서 온 그 선원이 너한테 계속 들러붙던데? 밤에 자기랑 같이 있어줄 거라고 완전히 믿는 눈치였어.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "아, 그 사람! 그는... 그는 그냥 한 잔을 너무 많이 마셨을 뿐이야, 그게 다야. 여기선 그런 일이 자주 일어나거든. 내가 부추긴 건 절대 아니고, 그쪽에서 먼저 치근덕거리기 시작했지. 그래서 내가 제자리에 앉혀 놨어.";
			link.l1 = "격려는 없나? 그는 다르게 말하던데. 이번에는 왜 이렇게 소란을 피웠으면서, 다른 때는 조용했지?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "나... 나 더 이상 할 말이 없어! 정말 아무것도 몰라! 나는... 나는 저녁 내내 다 보이는 곳에 있었어! 아무것도 못 봤고, 아무 소리도 못 들었어! 그리고 그 통에 대해서는... 무슨 일이 있었는지 전혀 몰라! 왜 이렇게 캐묻는 거야? 난 그냥... 그냥 평소처럼 내 일만 했을 뿐이야!";
			link.l1 = "뭔가 숨기고 있는 것 같은데. 배의 창고에서 불도 음식도 없이 하룻밤 보내면 기억력이 기적처럼 돌아오더군. 직접 겪어 볼래? 아니면 제대로 대화해 볼까?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "네가 숨기고 있는 게 훨씬 더 많다는 걸 알고 있다. 지금이 기회야 — 전부 말하면 네가 이 일에 끼어든 걸 내가 비밀로 해주지. 하지만 계속 입 다물고 있으면, 더 나쁘게 될 거다. 네 도움이 있든 없든 진실은 내가 밝혀낼 거니까.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "나... 나... 전부 말할게! 이 모든 건 내... 구혼자, 잭 때문이야. 잭 베일스! 그가 나한테 '바다 괴수'에서 온 선원이라면 누구든 유혹하라고 시켰어. 그리고 그가 접근하면, 내가 일부러 소란을 일으켜서 주점 주인을 카운터에서 끌어내기로 했지. 소동이 조금 가라앉으면, 두 선원이 싸움을 벌여 주인을 큰 방에 붙잡아 두기로 했고. 실제로 딱 그렇게 됐어\n그 시간 동안, '바다 괴수'의 선장이 몰래 술통을 훔쳐 갔어. 내가 아는 건... 그게 전부야. "+GetSexPhrase("나리","부인")+"! 제발, 나를 넘기지 마! 난 그냥... 그냥... 그저... 잭이 드디어 나를 좀 존중해 주길 바랐을 뿐이야! 결국 내가 그 녀석을 도와주긴 했잖아...";
			link.l1 = "한 사람을 도우면서도 망설임 없이 다른 한 사람을 늑대에게 던져줬다니?! 그래도 약속은 지키지. 네가 한 일은 발설하지 않겠어. 하지만 네가 저지른 일은 평생 짊어지고 살아야 할 거다! 네 어리석음 때문에 주점 주인이 큰 위험에 처할 뻔했어. 네가 말한 그 잭은 어디에 있지? 그리고 기억해라: 나한테 거짓말하면 다시 올 거다. 내 말 믿어, 내가 돌아오면 절대 즐겁지 않을 거다.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "나... 나... 다 말할게! 이 모든 건 내... 구혼자, 잭 때문이야. 잭 베일스! 그가 나를 설득해서 'Sea Beast'의 어떤 선원이든 유인하라고 했어. 그리고 그가 접근할 때, 내가 소란을 일으켜서 주점 주인을 카운터 뒤에서 나오게 하라는 거였지. 소동이 가라앉기 시작하면, 두 선원이 싸움을 벌여서 주점 주인이 본관에 묶이게 만드는 거야. 실제로 딱 그렇게 됐어\n그 시간 동안 'Sea Beast'의 선장이 술통을 훔쳐갔어. 그게... 내가 아는 전부야. "+GetSexPhrase("나리","부인")+"! 제발, 나를 넘기지 마! 나는 그냥... 나는 단지... 그저... 잭이 드디어 나를 좀 존중해주길 바랐을 뿐이야! 결국 내가 그 녀석을 도와주긴 했잖아...";
			link.l1 = "한 사람을 도우면서도 다른 한 사람은 망설임 없이 늑대들에게 던져버렸군?! 그래도 약속은 지키지. 네가 한 일은 밝히지 않겠어. 하지만 네가 저지른 일은 평생 짊어지고 살아야 할 거다! 네 어리석음 때문에 주점 주인이 큰 위험에 빠질 뻔했어. 네가 말한 그 잭은 어디에 있지? 그리고 기억해라. 나한테 거짓말하면, 다시 올 거다. 내 말 믿어, 내가 돌아오면 절대 즐겁지 않을 거다.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "이렇게 심각한 줄은 몰랐어요! 결국 그냥 통 하나일 뿐이잖아요... 잭은 길 건너에 살아요. 저기 집을 빌려 살고 있어요, 저... 저 더 이상 아는 게 없어요! 제발 용서해 주세요! 선장님, 다시는 이런 짓 안 하겠다고 맹세합니다!";
			link.l1 = "네 일로 돌아가. 그리고 감히 울 생각도 하지 마라 — 주점 주인이 아무것도 눈치채면 안 되니까.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
