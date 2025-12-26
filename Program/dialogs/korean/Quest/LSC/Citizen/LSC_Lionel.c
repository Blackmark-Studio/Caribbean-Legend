// Лайонел Маскетт - мещанин
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
				dialog.text = "너랑 말하고 싶지 않아. 너는 아무 이유 없이 평화로운 사람들을 공격하고 싸움을 부추기잖아. 저리 꺼져!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕하시오, "+GetAddress_Form(NPChar)+". 너 여기 처음 왔나?";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+" - 그래, 맞아.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+", "+TimeGreeting()+"뭐 필요해?";
				link.l1 = LinkRandPhrase("나한테 해줄 만한 흥미로운 얘기라도 있어?", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서 와봤어. 잘 있어.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "내 이름은 라이오넬이야. 만나서 반가워. 어떻게 여기 오게 됐어?";
			link.l1 = "바르크를 타고 왔지... 이 근처에 밀수업자들의 은신처가 있다는 소문을 듣고 찾아보려고 했거든... 뭐, 내 바르크는 침몰했고, 그래서 여기 있게 됐어.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "사람들이 정말 이 섬을 밀수꾼들의 은신처라고 생각하나?";
			link.l1 = "공식적으로는 아니야. 대부분 사람들은 네 존재조차 믿지 않아.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "그리고 왜 그래야 하지? 우리는 어떤 지도에도 없어. 이곳을 떠날 수도 없고. 현지인들은 정의의 섬이 한때 쿠바와 교역했다고 말하지만, 나는 기억이 안 나. 여기 산 지도 거의 8년이나 됐거든.";
			link.l1 = "알겠소. 당신과 이야기해서 즐거웠소. 안녕히 가시오.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("나한테 해줄 만한 흥미로운 얘기라도 있나?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "듣고 있다.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기 어떻게 오게 된 거야?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "떠나서 본토로 가고 싶으신가?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "여기, 정의의 섬에서는 사람들이 뭘 하며 지내지?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "여기서는 물건을 어디서 구하지? 음식, 옷, 술 같은 거?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "이상한 이야기지. 나는 카리브 해에서 정의의 섬밖에 모른다네. 영국에서 운이 너무 안 좋아서 신세계로 가는 상선에 승선권을 샀지. 벨리즈에서 일자리를 구하려 했어, 아마 항만 관리인의 서기 같은 일로 말이야. 하지만 우리는 끝내 벨리즈에 도착하지 못했지.\n나는 뱃사람이 아니라서 자세한 건 모르지만, 갑자기 폭풍이 몰아쳐서 암초에 난파당했어. 그 끔찍한 충격과 비명소리는 절대 잊지 못할 거야...\n누군가가 '배에 구멍이 났다!'고 외치자 사람들이 바다로 뛰어내리기 시작했지. 나는... 수영을 못 해서 남아 있었어. 아이러니하게도 그게 내 목숨을 살렸지. 배는 살아남았고, 폭풍은 새벽에 잦아들었거든.\n배에서 내리기 전에 음식을 챙기고, 뗏목을 만들어 잔잔한 바다를 노 저어 바깥 고리까지 갔어. 그렇게 살아남았지. 선원들 중에 나만 살아남았어.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "여기 처음 2년 동안은 그게 내 꿈이었지. 하지만 지금은... 이 섬이 다른 어떤 곳보다 정말 더 나쁜가? 푸른 들판이나 나무는 없지만, 웅장한 바다와 별로 가득한 밤하늘이 있잖아. 나는 잘 먹고, 영국에 살 때보다 더 좋은 옷도 입고 있어. 친구도 많고...\n아니요, 나리, 난 이곳을 떠나고 싶지 않아요. 밖에 나가면 나한테 뭐가 있겠어요? 성질 더러운 상사 밑에서 주당 삼백 페소 받으며 책상머리에 앉아 있는 일? 싫어요, 나리! 내가 찾던 모든 게 바로 여기 있었어요. 더는 아무것도 필요 없어요.";
			link.l1 = "알겠어. 잘 됐다니 기쁘네!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "무엇이든 자기들 마음대로지. 나르발과 리바도스는 전쟁을 벌이고, 해적들은 식량을 팔아. 악셀 요스트는 난파선 물건을 사고팔고, 산초 카르펜테로는 술을 따라주며 사람들을 즐겁게 하지. 줄리안 형제는 기도하고 미사를 드리며 약을 팔고, 로더데일과 솔데라는 서로를 상대로 음모를 꾸며. 아보트는 햇볕 아래서 으스대는 걸 좋아하고, 질리안과 타네케는 진정한 사랑을 꿈꾸지...\n";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "난파선에서지, 친구. 난파선에서. 바깥쪽 고리의 부서진 배들을 인양하는 게 이 섬 주민들한테는 가장 인기 있는 오락거리야. 거기선 뭐든지 찾을 수 있지: 무기, 약, 향신료, 럼주까지. 아직도 탐험되지 않은 난파선이 많아 – 조류가 계속해서 새로운 희생자들을 데려오거든...\n";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("내 물건에서 손 떼, 도둑놈아!", "잠깐 한눈판 사이에 나를 털려고 했어?! 어디 한번 당해봐라!", "내 궤짝을 뒤진다고?! 이대로 넘어갈 줄 알지 마!");
			link.l1 = "입 닥쳐!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "감히 내 물건을 허락도 없이 건드리다니! 누구 없나, 도둑이다!";
			link.l1 = "입 닥쳐!";
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
			dialog.text = LinkRandPhrase("무기 좀 치워, 친구. 그거 보면 신경이 곤두서.", "여기서는 칼 들고 뛰어다니는 거 용납 안 돼. 집어넣어.", "이봐, 정의의 기사 흉내 내면서 칼 휘두르고 다니지 마. 너한테 안 어울려, 집어넣어...");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 나는 이 섬의 주민이야. 그러니 칼을 내려놓아 줘.", "이봐, 나는 이 섬의 주민이니 칼을 내려두라고 부탁하겠어.");
				link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "조심해, 친구. 무기를 들고 돌아다니면... 내가 불안해지거든.", "무기를 들고 돌아다니는 남자는 싫어. 무서워서 그래.");
				link.l1 = RandPhraseSimple("미안해.", "나는 이걸 치우고 있어.");
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
