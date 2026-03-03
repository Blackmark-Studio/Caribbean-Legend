// Гхерад Смиитс - матрос
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
				dialog.text = "꺼져, 이봐. 난 죄 없는 민간인들 때리는 놈들이랑 말 안 섞어!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕, 친구야, 하하! 여기서 뭐 하고 있냐?";
				link.l1 = TimeGreeting()+". 좋은 하루요! 아직 당신을 만난 적이 없는 것 같소.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "이봐, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭘 도와줄까?";
				link.l1 = LinkRandPhrase("이봐! 소식 좀 있나?", "섬에 무슨 새로운 일이 있었어?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서. 또 보자!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "그래, 아직 못 봤겠지, 하지만 이제 봤잖아! 내 이름은 헤라르트 스미츠, 선원이야 - 로테르담 출신 뱃사람이지. 그리고 보아하니 네가 사관 같은데, 내 착각은 아니겠지...?";
			link.l1 = "그런 셈이지. 내 이름은 "+GetFullName(pchar)+". 만나서 반갑소.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "사실, 너는 선주나 급여 담당자처럼 보이는데... 교육도 잘 받은 사람인 게 분명하군. 만나서 반갑다! 어떻게 여기까지 오게 됐어?";
			link.l1 = "나는 멕시코 만을 탐험하기로 했어. 쿠바에서 온 버커니어들이 이 근처에 미지의 섬이 있다고 말하더군. 그 말이 사실인지 직접 확인해 보고 싶었지.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "너만 살아남은 거야? 네 배는 어디서 침몰했어, 바깥 고리에서?";
			link.l1 = "내가 정말 유일하지. 그리고 내 바크선은 여기 남쪽 바다 밑에 가라앉아 있어; 바깥 고리에도 닿지 못했지.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "아. 뭐, 여기 갇혔으니 산초에게 가서 럼주라도 받아. 슬픔을 술로 달래는 게 정의의 섬 생활의 시작이지, 헤헤.";
			link.l1 = "고마워... 그럼 이만!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("이봐, 스미츠, 소식 있어?", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "이 섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "그래, 친구. 뭐든 물어봐!";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "말해 봐, 여기 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "섬을 떠나 예전 삶으로 돌아가고 싶어?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "그 클랜들이 너를 괴롭히나?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "이 섬이 어떻게 생긴 건지 알아? 혹시 짐작가는 거라도 있어?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "나는 그 잘난 척하는 공작새 같은 애벗과 함께 여기 오게 됐지. 그의 배에서 일했어. 알지? 저런 인간들은 절대 배에 발을 들이면 안 돼. 재수 없거든. 악마가 우리 배에 그 자를 태운 게 틀림없어.\n우린 자메이카에서 벨리즈로 항해를 시작했어. 식은 죽 먹기였지. 그런데 불운이 따라붙더라. 갑판장이 바다에 빠지고, 항해사는 길을 잘못 잡고, 빌어먹을 스페인 놈들이 덮치고, 폭풍이 우리 배를 산산조각 냈어. 그래서 이렇게 된 거야.";
			link.l1 = "이런!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "예전엔 그랬지, 하지만... 솔직히 말해서, 친구야, 나도 잘 모르겠어. 여기서의 삶도 괜찮아. 럼주랑 와인도 많고, 음식도 좋아. 많진 않지만, 벌레 먹은 배빵보다는 훨씬 낫지.\n여기 좋은 놈들도 많고, 술 마시고 수다 떠는 재미도 있지. 난 여기 마음에 들어. 그래서 잘 모르겠어... 아니, 생각해보니 나가고 싶지 않아. 예전엔 늘 화나고 배고프게 살았는데—지금 내 배 좀 봐, 하하!";
			link.l1 = "좋아! 잘 됐다니 나도 기쁘네.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "아니, 그렇지 않아. 그냥 그들의 영역을 침범하지 마, 그건 절대 용납 안 해. 나르발 녀석들은 괜찮은 놈들이야 - 대부분 여기서 태어나서 다른 삶을 몰라. 실력 좋은 녀석들도 많지. 예를 들면 위르겐 슈미트, 그 사람은 대장장이의 신이야, 살아 있는 헤파이스토스라니까!\n";
			link.l1 = "알아두면 좋지.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "폭풍과 암초지, 친구. 바깥 고리는 위아래로 전부 배들로 이루어져 있어. 배들이 폭풍에 휩쓸려 암초나 바깥 고리 위에 처박히는 거야. 그렇게 정의의 섬이 커지는 거지!\n그런데 왜 안쪽 배들은 물 위에 떠 있는지 나는 전혀 모르겠어. 아마 우리 발밑에 여울이 있어서 떠받치고 있는 걸 거야.";
			link.l1 = "흥미롭군!";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("이봐, 도둑놈! 나를 홀랑 털 수 있을 줄 알았냐?", "내가 등만 돌리면 이런 일이 벌어진다니! 더러운 도둑놈이 기어들어오네!", "이봐! 내 바다 상자에 손대지 마, 이놈아!");
			link.l1 = "젠장, 모르겠다!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "내 상자를 뒤진다고?! 감히 그런 짓을 하다니!";
			link.l1 = "젠장...";
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
			dialog.text = LinkRandPhrase("이봐, 칼 좀 집어넣지 않겠어? 너 때문에 불안하잖아.", "칼 빼들고 돌아다니는 거 아무한테도 들키지 마. 그거 집어넣어.", "칼 뽑고 기사인 척하지 마라, 완전 바보 같아 보여. 집어넣어...");
			link.l1 = LinkRandPhrase("좋아.", "원하시는 대로...", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 여기선 멍청이들이 무기 꺼내 들고 돌아다니는 거 못 참아. 집어넣어.", "난 남자가 칼을 그렇게 함부로 휘두르는 거 싫어. 집어넣어.");
				link.l1 = LinkRandPhrase("좋아.", "뭐, 그러든가.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 칼 좀 집어넣지 그래? 너 때문에 불안하잖아.", "나는 남자가 칼을 그렇게 함부로 휘두르는 게 싫어. 무섭거든...");
				link.l1 = RandPhraseSimple("알겠어.", "내가 가져간다.");
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
