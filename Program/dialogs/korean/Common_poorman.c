#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "이봐, 나리, 재미있는 물건 하나 안 사시겠소? 값도 싸고, 몇 천 페소면 충분하오...";
				link.l1 = "흠. 아마 이 '작은 물건'을 훔쳐 놓고, 이제 떼어내려고 하는 거지?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("안녕하세요. 제 이름은 "+GetFullName(npchar)+"... 나를 만나서 기쁘지는 않겠지만, 적어도 내 이름은 기억해 주겠지...","안녕하시오, "+GetAddress_Form(NPChar)+". 내 이름은 "+GetFullName(npchar)+".","내 이름은 "+GetFullName(npchar)+", "+GetAddress_Form(NPChar)+". 만나서 반갑소.");
				link.l1 = RandPhraseSimple("안녕하시오.","안녕하세요.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "이봐, 들어봐, 이런 보잘것없는 동냥 대신에 몇 천 페소 벌고 싶지 않아?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "그 카메오가 박힌 펜던트... 어디서 찾았지?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("내가 이렇게까지 추락하다니...","구걸로 살아가는 건 쉽지 않지...","이 가난에서 벗어날 수만 있다면 뭐든지 내줄 텐데!","또 너냐?..","block",1,npchar,Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("알겠어. 뭐, 별일 아니야.","물론이지. 있잖아, 역사상 가장 위대한 인물도 가장 가난했거든.","그럼 하루 종일 여기 앉아만 있지 말고 뭔가 좀 해야지.","아하. 벌써 내가 성가시냐?",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("무슨 일이야?","뭘 원하지?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "이봐, 들어봐, 이런 보잘것없는 동냥 대신에 몇 천 페소 벌고 싶지 않아?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "그 보석이 박힌 펜던트... 어디서 찾았지?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("재미있는 이야기 좀 해줄 수 있나?","마을에 무슨 새 소식 있어?","오, 최신 소문 좀 듣고 싶은데...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("아니, 왜, 벌써 짜증났어? 보다시피 난 딱히 바쁘지도 않은데...","그저 피곤할 뿐이야. 가난하지만, 그래도 난 아직 남자다.");
			link.l1 = "헤, 알겠군...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("흠, "+GetAddress_Form(NPChar)+", 사람들은 당신에 대해 끔찍한 소문을 많이 하더군요. 하지만 저는 여전히 사람을 믿습니다—당신 같은 이조차도요. 제발, 빵과 물을 살 수 있게 자비를 베풀어 주십시오, 불쌍히 여겨 주세요.","부탁드립니다, "+GetAddress_Form(NPChar)+"! 제발, 가난한 사람을 외면하지 마시오, 한 끼라도 먹을 수 있게 자선을 베풀어 주시오...");
				link.l1 = RandPhraseSimple("아무것도 안 줄 거야.","돈 없이도 어떻게든 할 수 있을 거야.");
				link.l1.go = "exit";
				Link.l2 = "좋아, 그래서 얼마나 필요하지?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("너한테서? 아무것도 없어.","나는 아무것도 필요 없어, "+GetAddress_Form(NPChar)+", 감사합니다.");
				link.l1 = RandPhraseSimple("흠, 알겠어.","보아하니, 네 인생은 그렇게 나쁘진 않은 것 같군, 이 친구.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "동전 한 닢이라도 마다하지 않겠어, "+GetAddress_Form(NPChar)+"... 당신의 주머니와 자비가 허락하는 만큼...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "약하고 지친 자를 조롱하는 것은 죄악이오...";
				link.l1 = "하하하! 내가 너 같은 미친 거지한테 돈을 줄 거라고 진짜 생각했냐?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "감사합니다 "+FindRussianMoneyString(iTemp)+", "+GetAddress_Form(NPChar)+"... 이제 이 돈으로 빵이라도 좀 살 수 있겠군...";
				link.l1 = "여기 있다, 떠돌이놈아 - 가서 기운 좀 차려라.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "감사합니다, "+GetAddress_Form(NPChar)+". 그 돈이면 일주일은 살 수 있겠어!";
				link.l1 = "도와드릴 수 있어 기뻤습니다.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "감사합니다, "+GetAddress_Form(NPChar)+". 당신의 친절함을 모두에게 알리겠어요!";
				link.l1 = "이건 굳이 필요하지 않아.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "감사합니다, 존경하는 분 "+GetSexPhrase("나리","아가씨")+" "+GetAddress_Form(NPChar)+"... 주님께서 그대를 지켜주시길...";
				link.l1 = "그래, 그분의 보호가 있으면 나쁠 건 없지!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "감사합니다, "+GetSexPhrase("가장 존경하는 나리","가장 존귀하신 부인")+" "+GetAddress_Form(NPChar)+". 행운을 빕니다!";
				link.l1 = "고맙다, 친구.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "들어봐, "+GetAddress_Form(NPChar)+", 너 미쳤어 아니면 뭐야? 나한테 주는 게 "+FindRussianMoneyString(iTemp)+"! 이런 돈은 받을 수 없어, 분명히 뭔가 꿍꿍이가 있겠지... 나를 그냥 내버려 둬!";
				link.l1 = "글쎄, 원하시는 대로...";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "이만오천 받아들였어... 이 돈이면 레일라랑 나, 1년은 충분히 살 수 있겠어!";
				link.l1 = "올해부터 먼저 살아남아라...";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "들어봐, "+GetAddress_Form(NPChar)+", 너 미쳤어 아니면 뭐야? 나한테 주고 있잖아 "+FindRussianMoneyString(iTemp)+"! 이런 돈은 받을 수 없어, 분명 뭔가 꿍꿍이가 있겠지... 나를 그냥 내버려 둬!";
				link.l1 = "그래, 원하는 대로 해...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "어리석은 질문이군, 나리! 물론이지! 하지만... 내가 뭘 해야 하지? 설마 내 아름다운 미소만으로 그 돈을 주려는 건 아니겠지.";
			link.l1 = "당연히 아니지. 이제 잘 들어. 나는 총독님을 대신해 행동하고 있다. 총독 각하께서는 조선소에 누군가가 일부러 '알라칸타라'라는 자신의 갈레온선 진수를 방해하고 있다고 의심하고 계시네. 그리고 최근 프랑스 첩자가 붙잡힌 이후로 그 의심은 더욱 커졌지...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "각하께서는 이미 조선공의 변명을 들으셨지만, 그가 진실을 말했는지는 확신하지 못하고 계십니다. 누가, 왜 일을 방해하고 있는지 밝혀내야 합니다. 부두로 가서 주변을 살펴보고, 일꾼들에게 대체 왜 '알라칸타라'가 아직도 출항 준비가 안 됐는지 물어보십시오...\n";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "아무도 너를 의심하지 않을 거야. 어쩌면 담배 한 무더기도 챙길 수 있겠지. 나로 말하자면, 아무도 내게 아무 말도 안 할 거야. 내가 누구를 위해 일하는지 다들 아니까. 만약 쓸 만한 정보를 알아내면, 삼천 페소를 받게 될 거야. 적어도 한 달은 네 '일'을 접고 지낼 만큼 충분하지.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "삼천 페소라고요? 하지만, 존경하는 나리...";
			link.l1 = "나랑 흥정하는 거야, 뭐야? 그리고 이 모든 지연의 배후가 누군지 알아내면, 이천 더 줄게. 어때?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "알겠소, 나리. 그렇게 어렵진 않을 거요 - 내 옛 친구들 중 많은 이들이 요즘 부두에서 일하고 있거든. 이봐, 나도 한때는 선원이었소. 한... 십 년 전쯤이지만...";
			link.l1 = "네 인생 이야기는 나중에 들으면 되겠지. 밤 열한 시 이후에 부두에서 나를 만나. 이제 가.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			DialogExit();
			AddDialogExitQuestFunction("Trial_Poorman_DlgExit");
		break;
		
		case "trial_6":
			dialog.text = "좋은 저녁이오, 나리...";
			link.l1 = "그래서? 뭐 알아낸 거 있어?";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "했지, 나리, 했어. 당신이 말한 거랑 다 맞는지는 잘 모르겠는데... 돈 가져왔나? 오천 페소야.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "걱정 마. 여기 네 돈이야. 이제 말해 봐.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "정보가 먼저고, 그 다음이 돈이야. 어서, 내 시간 낭비하지 마!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "나한테 사기 치려는 거지, 나리! 돈 안 줄 거면 직접 가서 다른 사람한테 부탁해. 그리고 칼 뽑을 생각도 하지 마, 안 그러면 경비병 부를 거야!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Trial_FailPoormanInPort");
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "그러니까 이런 거야: 'Alcantara'는 오래전부터 출항 준비가 끝났지만, 총독 본인의 명령으로 일부러 짐을 싣지 않았다고 하더군. 뭐, 내가 들은 얘기가 그래. 그리고 지금은 목수들이 배 출항에 아무 영향도 없는 자잘한 일만 하고 있어.\n모두가 Cartagena에서 온 어떤 바크선을 기다리고 있지. 문제는 'Alcantara'에, 선장 생각으론, 화약이 충분하지 않다는 거야. 그래서 배는 며칠째 여기 머물면서 'Puebla'가 화약을 가져오길 기다리고 있지.\n하지만 다들 이런 기다림이 시간 낭비라고 생각해서, 만약 'Puebla'가 사흘 안에 안 오면, 'Alcantara'는 화약 없이 닻을 올릴 거래...";
			link.l1 = "그런가? 그걸 누가 말했지? 이름은?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "'알칸타라'의 선원 중 한 명인 펠리페 다비뉴... 하지만 그건 사실 전혀 비밀이 아니고, 총독 각하께서 직접 명령하신 일이오...";
			link.l1 = "알겠어. 예상했던 대로군. 프랑스 첩자들이 도시에 있는데, 이 멍청이들은 시장 아낙네들처럼 떠들어대고 있어, 믿기지 않는군! 아무 신참이나 각하의 계획에 대해 원하는 건 뭐든 알아낼 수 있겠어. 오, 그 펠리페 다빈요는 이제 정말 곤경에 처했군! '알라칸타라'의 보스웨인도 마찬가지야! 자기 선원들이 규율이 뭔지도 모르는 건 전적으로 저 자식 잘못이야!";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "오... 처음부터 알고 있었던 거야? 그런데 왜... 내 잘못이 아니야! 당신이 시키라고 했잖아!";
			link.l1 = "네 잘못이 아니니 걱정할 필요 없어, 아무도 너를 벌하지 않을 거야. 이제 'Alacantara' 선원들이 비밀로 해야 할 정보까지 적에게 아무렇지 않게 흘릴 수 있다는 걸 알게 됐지. 좋아, 이제 가도 된다. 도와줘서 고맙다. 가서 네 돈이나 써.";
			link.l1.go = "trial_11";
			link.l2 = "잘 가라. (죽여라)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddDialogExitQuestFunction("Trial_KillPoormanInPort");
		break;
		
		case "trial_11":
			DialogExit();
			AddDialogExitQuestFunction("Trial_PeacePoormanInPort");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "실례합니다, 나리... 어떤 낯선 사람과 주사위 게임을 하다가 이걸 땄습니다. 행운의 치유 부적이라 생각했는데, 착각이었어요... 병도 낫게 해주지 않고, 시장 상인들도 관심이 없더군요. 그런데 여기 계신 당신은 뱃사람이자 선장이며, 학식 있는 분이시니 한번 봐주시겠습니까? 혹시 쓸모가 있을지도 모릅니다.\n당신에게 이 몇 천 페소는 작은 돈이겠지만, 저에겐 한 달 동안 빵 한 조각과 럼 한 모금입니다. 보십시오, 나리...";
			link.l1 = "좋아, 보여 줘...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "여기...";
			link.l1 = "그저 그렇군... 흥미로운 물건이야, 동의하지. 분명 인디언 마을에서 훔친 거겠지. 좋아, 내가 사겠다. 여기 돈이다.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "감사합니다, 나리! 이것이 당신께 행운을 가져다주길 바랍니다! 주님께서 당신을 지켜주시길!";
			link.l1 = "행운을 빌어, 친구야. 선술집에서 돈 한 번에 다 써버리지 마라.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "에, "+GetAddress_Form(NPChar)+", 왜 오래된 장신구에 신경 쓰는 거지?";
			link.l1 = "내가 네 멍청한 머리를 내 부츠로 걷어차면, 내가 왜 신경 쓰는지 바로 알게 될 거다.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "이 펜던트는 베시 프라이스의 것이었어. 그런데 어디서 찾았지?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "등불이 있는 집 근처에 누워 있었어, "+GetAddress_Form(NPChar)+". 거친 사내의 부츠에 진흙 속에 짓밟혔지. 하지만 그 집엔 오래전부터 아무도 살지 않았으니, 나는 주인 없는 집이라 생각했어...";
			link.l1 = "흠...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "등불이 있는 집 근처에 놓여 있었어, "+GetAddress_Form(NPChar)+". 거친 사내의 장화에 진흙 속에 짓밟혀 있었지. 하지만 그 집에는 오랫동안 아무도 살지 않았으니, 나는 버려진 집이라 생각했어...";
			link.l1 = "흠...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
