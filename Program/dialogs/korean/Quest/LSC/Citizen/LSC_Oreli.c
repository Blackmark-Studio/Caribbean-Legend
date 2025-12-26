// Орели Бертин - просто жительница
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
				dialog.text = "날 내버려 둬, 나리. 누군가를 다치게 했잖아! 저리 가!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "좋은 하루입니다, 나리.";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+", 나는 여기 온 지 얼마 안 돼서 주민들을 알아가는 중이야.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "오, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐라도 필요해?";
				link.l1 = LinkRandPhrase("안녕하세요, Bertine 부인. 정의의 섬에는 무슨 새 소식이 있나요?", "섬에 무슨 새로운 일이라도 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서 왔어. 또 보자!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "알겠어. 내 이름은 오렐리 베르틴이야. 어떻게 여기 오게 된 거지?";
			link.l1 = "전설적인 정의의 섬을 한번 보고 싶었다고만 해두지.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "그러니까 네가 자진해서 이 섬에 온 미친놈들 중 하나라는 거군... 뭐, 이제 이 정의의 섬을 실컷 구경하고 '정의'도 충분히 맛볼 시간이 넉넉할 거다.";
			link.l1 = "네 비꼼을 보니, 이 정의의 섬 방식에 뭔가 문제가 있다고 보나?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "아니, 다 괜찮아. 하지만 이상하게도 예전에는 모두가 무료로 먹던 음식을 이제는 해적들에게 돈을 내야 해. 얼마 전까지만 해도 그랬는데 말이야. 그리고 클랜들이 우리 구역에서 싸움을 벌이면, 우리는 총이나 칼에 맞지 않으려고 배 안에 틀어박혀 있어야 해.\n그러니까, 걔네들은 우리 땅에서 뭐든 마음대로 할 수 있는데 우리는 그들 구역에서 똑같이 못 한다는 거지. 뭐, 괜찮아, 아무 문제 없어... 정말 하나도 없어...";
			link.l1 = "그렇군요... 그래도 만나서 반가웠습니다. 그럼 이만, 베르틴 부인!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "어서 말해 봐.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기서 오래 살았어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "섬에 흥미로운 게 있나?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "그 클랜들에 대해 어떻게 생각해?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "해적들이 너를 괴롭히나?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없어. 미안...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "아주 오랜 시간이 지났지. 몇 년이 흘렀는지도 잊어버렸어... 열일곱 해쯤 됐나... 아니, 어쩌면 열여덟... 아니면 스무 해인가? 지금이 몇 년이지?";
			link.l1 = "그럼, 너 오래된 놈이란 말이야?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "이렇게 말할 수 있지. 나는 아직도 쿠바에서 온 버커니어들이 우리와 거래하던 때를 기억해. 그리고 가장 영리하고 무모한 나르발 녀석들이 본토로 건너가서, 난파선 화물에서 건진 물건을 식량과 바꿔 오곤 했지.\n하지만 이제는 태어나서부터 정의의 섬밖에 모르는 사람들이 많아. 그들은 단순한 터줏대감이 아니라, 이곳의 토박이야.";
			link.l1 = "흥미롭군!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "그래. 이 섬은 흥미로운 곳이지. 직접 돌아다녀 보고, 난파선들 사이를 헤엄쳐 다녀 보고, 선술집이나 상점, 교회도 들러 봐. \n하지만 장담하는데, 신기함도 일주일이면 사라질 거야.";
			link.l1 = "좋아...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "뭐라고 말해주길 바라나? 난 그놈들을 피하려고 하지. 적어도 나르발들은 섬에 도움이 되는 짓을 좀 하긴 해. 그들 중에는 아주 재능 있는 장인들도 있거든. 하지만 리바도스는 그냥 야만인에다가 이교도일 뿐이야.\n그들은 수백 년 전 조상들처럼 아프리카 법대로 살아. 짐승들이지. 총 쏘는 법만 배웠을 뿐이야. 어떤 사람들은 리바도스가 의식적으로 식인 풍습까지 저지른다고 하더군!";
			link.l1 = "악몽이 따로 없군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "우리한테 우리 음식을 팔아먹는 건 좀 거슬리지만, 시민들에게 해를 끼친 적은 없어. 오히려, 그들이 각 클랜을 굴복시키고 끊임없는 전쟁을 멈췄지.\n한 번은, 사람들에게 말썽을 피우던 시민이 있었어. 칼을 휘두르는 걸 좋아했지. 그가 현지인 두 명을 다치게 했거든. 해적들이 그를 타르타로스에 몇 주 동안 가둬뒀고, 이제 그 남자는 아주 얌전해졌어. 자주 보진 못해 – 바깥 고리가 그의 새 집이거든...";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("뭐 하는 거야, 도둑놈?!", "내가 등만 돌리면 바로 내 상자를 뒤지는 거야?!", "내 상자를 뒤지는 거냐, 이놈아? 가만두지 않겠다!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "이 도둑놈아! 이런 짓을 했으니 타르타로스에서 썩게 될 거다!";
			link.l1 = "닥쳐!";
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
			dialog.text = LinkRandPhrase("무기를 거두어 주시오, 나리. 그거 보니 불안하오.", "여기서는 칼을 들고 뛰어다니는 거 용납 안 돼. 집어넣어.", "해적들도 네가 칼 들고 돌아다니는 걸 달가워하지 않을 거야. 사실 나도 마찬가지고...");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "무기를 거두어 주시오, 나리. 그걸 보면 불안해지거든.", "있지, 여기서는 칼을 들고 뛰어다니는 거 용납 안 해. 집어넣어.");
				link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "무기를 거두어 주시오, 나리. 그걸 보면 불안해지거든.", "해적들이 네가 칼 들고 돌아다니는 걸 좋아할 리 없지. 사실 나도 마찬가지고...");
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
