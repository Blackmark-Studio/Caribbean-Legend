// Дугал Эббот - дворянин
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
				dialog.text = "당신하고는 말 안 해, 나리. 당신은 아무 이유 없이 평화로운 사람들을 공격했잖아. 내 눈앞에서 꺼져!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕하십니까, 나리. 제 소개를 하겠습니다: 더걸 애벗입니다. 여기서 귀족을 뵙게 되어 반갑습니다. 이 농민들은 참으로 성가십니다. 이런 천한 자들과 평생을 함께 살아야 할 줄은 상상도 못 했습니다.";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 만나서 반갑네. 그런데 왜 현지인들을 좋아하지 않나?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 무엇을 도와줄까?";
				link.l1 = LinkRandPhrase("더걸! 섬에 무슨 소식이 있나?", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "그냥 어떻게 지내는지 궁금해서 왔어. 잘 가!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "그 녀석들 좀 더 알아가 봐. 방금 도착한 거야? 새로운 난파선 소식은 못 들었는데...";
			link.l1 = "나는 작은 바르크선을 타고 여기 왔어. 한밤중에 갑자기 침몰해 버렸지.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "그래, 그런 일은 일어나지. 배가 침몰하고 극소수만이 겨우 해안에 닿아 살아남아. 가끔은 사람들이 여기서 몇 달씩 살아도 서로 얼굴 한 번 못 볼 때도 있지.";
			link.l1 = "알겠습니다. 만나서 반가웠습니다, Abbot 나리. 안녕히 가십시오!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("안녕, Dougall! 무슨 소식 있어?", "섬에 무슨 새로운 일이 있었나?", "최근 소문 좀 들려줄래?");
			link.l2.go = "rumours_LSC";
			link.l3 = "이 섬에 대해 몇 가지 물어보고 싶어.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "듣고 있어.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "여기엔 어떻게 오게 됐어?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "여기 주민들에 대해 뭐 아는 거 있어?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "그 클랜들에 대해 뭐 알고 있는 게 있나?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "여기 날씨는 어때? 폭풍이 자주 불어?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "5년 전 일이지만, 아직도 어제 일처럼 생생히 기억나. 나는 고가의 화물이 가득 실린 플라이트를 타고 포트 로얄에서 벨리즈로 출항했지.\n다음 날부터 일이 꼬이기 시작했어. 먼저, 내 보스웨인이 술에 취해 바다에 빠졌고, 그다음엔 암초에 거의 부딪칠 뻔했지. 그리고 항해사가 실수해서 남쪽이 아니라 북쪽으로 우리를 보냈어.\n스페인 브리그와 갤리온이 우릴 발견했지. 우리는 도망쳤고, 그들이 뒤쫓아왔어. 갤리온은 따돌렸지만 브리그가 결국 따라잡았지.\n갤리온이 너무 멀리 떨어져 있어서 작은 동료를 지원할 수 없었으니, 나는 즉시 방향을 틀어 브리그에 승선하라고 명령했어. 스페인 놈들은 전혀 예상 못 했지, 크크! (한숨) 우리가 이기긴 했지만, 내 선원 대부분을 잃었어.\n몇 시간 뒤, 폭풍이 몰아쳤고, 남은 선원이 너무 적어서 버틸 수가 없었지. 그래서 지금 이렇게 된 거야. 내 플라이트는 바깥 고리 어딘가에 난파됐고, 나랑 다른 세 명의 생존자가 여기서 살고 있어. 푸흣!";
			link.l1 = "꽤나 사연이 많군.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "쓰레기들. 전부 다! 퉤! (침 뱉는다) 온갖 천한 놈들뿐이지. 리처드 샴본은 얼굴에 죄인이라고 써 있잖아. 카셀? 그 자식은 사람 죽이는 게 숨 쉬는 것만큼 자연스러워. 재스퍼 프랫은 죄수고, 머스킷은 술주정뱅이야. 더 말해야 하나?\n조셉 로더데일만이 여기서 유일하게 괜찮은 사람이야 - 물론 너는 예외고. 그는 영국 해군 장교지. 귀족도 둘 있는데, 안토니오 데 베탕쿠르트와 로렌초 솔데라야 - 젠장할 스페인 놈들! 난 걔네랑 같은 식탁에 앉지도 않을 거야.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "한 무리의 악당들과 쓰레기들이지. 그래도 우리한테 해를 끼치진 않아; 서로 죽이는 데 훨씬 더 관심이 많거든. 그리고 그놈들은 한 번도 멈춘 적이 없어 – 폭력 없이는 못 사는 놈들이지.\n나도 해적들은 별로지만, 솔직히 말해 그들이 온 뒤로 정의의 섬이 좀 더 평화로워졌어. 나르발과 리바도스를 서로 견제해 주거든.";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "절대 아니야. 섬 주변에는 폭풍이 자주 일어나지만, 정작 정의의 섬 자체는 언제나 고요하지. 아마 신의 뜻이거나 무슨 마법일지도 모르겠어, 나도 잘 몰라. 가끔 강한 바람과 비가 오긴 하지만, 피해를 줄 정도로 심각한 건 아니야.";
			link.l1 = "흥미롭군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("아하! 처음 봤을 때부터 네가 그냥 평범한 도적놈인 줄 알았지!", "내 물건에 손대지 마, 이 쓰레기들아!", "더러운 손가락 내 가슴에서 치워! 이 일로 널 꿰뚫어버릴 거야!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "내 물건 훔칠 생각 꿈도 꾸지 마, 이 망할 놈아! 썩 꺼져!";
			link.l1 = "진정해, 여자!";
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
			dialog.text = LinkRandPhrase("나리, 무기를 집어넣으시오. 불안하게 하시잖소.", "무기 집어넣어, 소란 피우고 있잖아.", "그렇게 무장하고 돌아다니면 누군가 다칠 수도 있소. 집어넣으시오, 나리.");
			link.l1 = LinkRandPhrase("좋아.", "좋아.", "말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이 도시의 신사로서 나는 네가 무기를 거두길 요구한다!", "신사 같은 분이라면 굳이 무기를 휘두를 필요는 없을 텐데.");
				link.l1 = LinkRandPhrase("좋아.", "좋아, 그럼.", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "나리, 무기를 집어넣으시오. 불안하게 하잖소.", "무기를 거두어 주시길 부탁드립니다, 나리. 당신 때문에 불안해집니다.");
				link.l1 = RandPhraseSimple("좋소.", "나는 이것을 치우고 있다.");
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
