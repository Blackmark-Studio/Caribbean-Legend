// Рамона Лоцано - горячая испанская сеньорита
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "가라, 나리. 넌 자기 일 하려는 평범한 사람들을 공격하잖아.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "오, 오! 여긴 처음이거나 아니면 화물칸 어딘가에 숨어 있었던 모양이군, 네 얼굴은 오늘 처음 보거든.";
				link.l1 = TimeGreeting()+". 짐칸에 숨어 있는 건 내 스타일이 아니지. 나는 선장실이 더 좋다... 하지만 그래, 나도 여기 처음이야.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+pchar.name+"! "+TimeGreeting()+"! 다시 만나서 반갑네! 무슨 일로 왔나?";
				link.l1 = LinkRandPhrase("친애하는 라모나! 정의의 섬에서는 어떻게 지내고 있나요?", "섬에서 새로운 일이라도 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그저 네 아름다운 얼굴이 보고 싶었을 뿐이야. 다음에 또 보자, 라모나!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "그럼 서로 좀 알아가 보자... 선장. 나는 라모나 로사노야 - '나리' 로사노라고 부르려거든 애초에 시도도 하지 마. 정말 싫거든. 너 이름이 뭐지?";
			link.l1 = ""+GetFullName(pchar)+"만나서 반갑소, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "정말 기쁜 거야, 아니면 그냥 예의를 차리는 거야, "+GetFullName(pchar)+"? 말해 봐, 너 진짜 선장이야 아니면 농담한 거야?";
			link.l1 = "오호, 질문이 참 많구나! 순서대로 대답해도 되겠어? 첫째, 정말 기쁘다네; 이렇게 예쁜 아가씨는 매일 만나는 게 아니거든. 둘째, 나는 분명 선장이지만, 내 배는 지금 스페인 본토 해안에 정박해 있지.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "재미있군! 그런데 선장, 당신은 여기 있는데 당신 배는 메인 해안에 있다니 어찌 된 일이오? 선원들이 뿔뿔이 흩어지고 당신 배를 빼앗길까 두렵지 않소?";
			link.l1 = "나는 이 바다를 탐험하려고 바크선을 타고 여기까지 왔어. 내 배는 내 자랑이자 기쁨이라 위험을 감수하고 싶지 않았지. 그런데 밤에, 바크선이 어둠 속에서 암초나 난파선에 부딪혀 뒤집혔고, 그리하여! 내가 여기 있게 된 거야.\n내 배는 내가 돌아갈 때까지 얼마든지 기다릴 거야. 대니 호크가 선원들을 잘 챙길 테니까.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "대니 호크? 설마... 다니엘 호크 말하는 거야? 그녀랑 같이 항해한다는 거냐?";
			link.l1 = "신께 맹세코, 라모나, 거짓말 아니야; 대니는 내 부하 장교야. 내가 바크를 타고 나갈 때 그녀에게 지휘를 맡겼지... 그녀를 어떻게 아는 거야?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "하! 스페인 식민지에 있는 누구나 해적 다니엘 호크와 그녀의 남편 나다니엘을 알지. 그래, 너 말이야, 나리\n "+GetFullName(pchar)+", 강인한 사람이겠군... 그럼 너도 해적인가? 걱정 마, 난 너희 같은 부류와도 잘 지내. 나는 강한 남자가 좋거든.";
			link.l1 = "글쎄, 나는 사실 해적은 아니야... 지금은 얀 스벤손 밑에서 일하고 있어. 대니가 사라진 남편을 찾는 걸 도와주려고.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "그리고 네가 해적이 아니라고? 너는 숲의 악마 밑에서 일하고, 네 일등항해사는 다니엘 호크고, 네이선리얼을 찾고 있다며... 그리고 분명히 여기 온 것도 제독 때문이겠지. 맞지?";
			link.l1 = "라모나, 원하면 나를 해적이라고 불러도 돼. 닻이라고 불러도 상관없어 – 다만 나를 진짜 닻으로 쓰지만 마!";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "정말로 강인한 사내 중 한 명인 것 같군, "+pchar.name+". 그럼, 난 이만 가봐야겠어. 정의의 섬에서 또 볼 수 있길 바라. 왠지 우리, 친구가 될 것 같은 느낌이 들어... 아주 가까운 친구 말이야.";
			link.l1 = "왜 안 되겠어? 좋은 하루 보내!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "오, 정말이야? 그래, 물어봐. 내가 아는 건 대답해주지...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기엔 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "분명 정의의 섬을 떠나려고 해본 적 있겠지?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "여기서 어떻게 살아가나요?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "여기서 무슨 일을 해? 음식이 공짜는 아니겠지?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없어. 실례...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "긴 얘기야... 내게 이런 일이 생긴 건 모두 새아버지 때문이야.\n4년 전, 나는 아바나에서 행복하게 살고 있었어. 어머니가 돌아가시고, 나는 어머니 재산의 유일한 상속인이 되었지. 우리가 부자는 아니었지만, 편하게 살 만큼의 돈은 충분히 있었어.\n새아버지는 그게 마음에 들지 않았고, 나를 없애기로 결심했지. 물론, 그 사실을 알게 된 건 시 외곽 문에서 고용된 두 깡패에게 습격당한 후였어. 그 멍청이들이 직접 누가 왜 자신들을 고용했는지 내게 말해줬거든.\n다행히도, 그 자들은 전문가가 아니었어. 아니었더라면 지금쯤 나는 목이 잘린 채 덤불 속에 누워 있었겠지. 그 바보들은 먼저 장난이나 치려고 했으니까.\n운명이 나를 살렸어. 마침 너 같은 선장이 그곳을 지나가고 있었거든. 그가 상황을 보고는 바로 그 쓰레기들을 죽였지. 놈들은 반격할 틈도 없었어. 나는 내 처지를 그에게 털어놓고, 조금 울기도 했지... 그는 내가 갈 곳이 없다는 걸 알고, 나를 새아버지에게서 구해주려고 자기 배에 태웠어. 처음엔 임시로 데려간 거였지만, 그 후로는...\n아마 계속 그와 함께했을 거야. 하지만 두 달 후, 그는 순찰대를 만났고, 돛대 하나를 잃었으며, 강풍에 휩쓸려 결국 외곽 환초 바닥에서 영면했지. 나는 모든 걸 견디고 살아남아, 정의의 섬 공동체에 합류하게 되었어.";
			link.l1 = "슬픈 이야기군, 할 말이 없어.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "당연히 아니지, 그건 불가능하거든. 이곳을 빠져나가려고 장주에 올랐던 남자를 본 적이 있어... 이틀 뒤에 돌아왔지. 익사하지 않으려고 난파된 돛대에 몸을 묶었는데, 돌아왔을 땐 온몸이 파랗게 질려 돌처럼 죽어 있었어.\n그리고 내게 말해봐, "+pchar.name+", 내가 탈출에 성공한다 해도 대체 뭘 할 수 있겠어? 아바나는 나한테 너무 위험해 — 의붓아버지가 분명 또 날 죽이려고 할 거야. 집도 없고, 돈도 없어. 어디로 가란 말이지? 창관에라도 가야 하나?";
			link.l1 = "그래도 카리브 해로 돌아가고 싶어?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "어떻게 생각해? 물론이지, 나도 그래. 하지만 그건 불가능해, 그리고 방금 그 이유를 말해줬잖아. 누군가 내 의붓아버지를 처리할 수만 있다면—칼이든 총알이든—내가 예전 삶으로 돌아갈 희망이 있을지도 몰라. 하지만 내 의붓아버지가 아바나 총독의 절친이라는 걸 알면서 누가 감히 그런 일을 하겠어? 그러니 우리가 무슨 얘기를 하고 있는 거지? 여기서 나갈 방법은 없어...\n";
			link.l1 = "두고 보자. 언젠가 때가 올지도 모르지...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "나는 그냥 살아. 다른 선택지는 없어. 내 친구들은 대부분 남자야, 왜냐하면 우리 정의의 섬에 시집갈 만한 미녀 둘, 질리언이랑 타네케가 나를 안 좋아하거든. 내털리는 원래 괜찮은 애였는데, 그 두 멍청이랑 어울리기 시작한 뒤로 달라졌지. 멍청함은 전염되는 법이야.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "나도 다른 여자들처럼 일해, 주로 남자들을 도와주지. 정의의 섬에서는 여자들이 할 일이 많아서 늘 바쁘게 지내. 그리고 선물도 자주 받아, 여기서는 흔한 일이야. 하지만 날 함부로 취급하지 마. 난 제대로 교육받았고, 좋은 집안 출신이야. 그냥... 어떤 여자들처럼 성녀인 척하지 않을 뿐이야...";
			link.l1 = "나는 전혀 너를 나쁘게 생각하지 않았어...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("뭐 하는 거야 - 아! 도둑이야!", "저것 좀 봐! 내가 등만 돌리면 바로 내 궤짝을 뒤지려고 하잖아!", "내 상자를 뒤지다니?! 그냥 넘어가지 않을 거야!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "개자식아! 내가 등을 돌린 사이에 내 궤짝을 털다니?!";
			link.l1 = "조용히 해!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("나리, 무기 좀 치우시오. 그거 때문에 불안하오.", "멍청이들이 칼을 뽑고 돌아다니는 건 우리 맘에 안 들어. 집어넣어.", "칼 뽑고 이리저리 뛰어다니는 거, 완전 바보 같아 보여. 집어넣어라...");
			link.l1 = LinkRandPhrase("좋아.", "그래.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 칼 집어넣어. 사람들 불안하게 하잖아.", "멍청이들이 칼을 뽑고 돌아다니는 건 우리도 싫어해. 집어넣어.");
				link.l1 = LinkRandPhrase("좋아.", "그래.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "나리, 무기 좀 치우시오. 그거 보면 불안해지거든.", "칼 빼들고 여기저기 뛰어다니는 거, 바보 같아 보여. 집어넣어라...");
				link.l1 = RandPhraseSimple("미안해.", "나는 이걸 치우고 있다.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
