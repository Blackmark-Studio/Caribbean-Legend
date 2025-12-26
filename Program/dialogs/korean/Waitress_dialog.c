// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "무엇을 원하십니까, 나리? 죄송합니다, 저는 그냥...'흑'... 아... 미안합니다.";
					link.l1 = "왜 이렇게 속상해하십니까, 아가씨? 이렇게 고운 얼굴에 눈물이라니요? 무슨 일이 있었습니까?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! "+UpperFirst(GetAddress_Form(NPChar))+", 도와줘! 살인이다!";
				link.l1 = "어? 누구를 죽였다고? 어디서? 이거 농담이지, 내 사랑?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! 다시 만나서 정말 반갑군요... 들러줘서 고맙소... 하지만 지금은 우리가 이야기 나누기에 좋은 때가 아닌 것 같소. 혼자일 때 다시 오시오. 그때 좀 더 개인적인 이야기를 나눌 수 있을 것이오.";
							link.l1 = "이야기 나누는 건 언제나 즐겁지만, 이제 가봐야겠어. 아마 다시 만날 수도 있겠지.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"... 우리 선술집 오는 길을 잊은 줄 알았잖아. 혼자가 아니라서 아쉽네. 단둘이 얘기 좀 하고 싶었거든.";
							link.l1 = "운명이 우리에게 아직 단둘이 이야기할 기회를 줄 거라고 생각해.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! 오래 기다리게 하지 않을 거란 걸 알았어. 더는 한 순간도 낭비하고 싶지 않아. 위층 방이 비어 있어... 우리 둘만을 위해서. 거절하지 않을 거지?";
							link.l1 = "나를 끌어들이는 법을 잘 아는군... 뭐, 거절할 이유도 없지. 갈까?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "오늘은 정말 중요한 일이 있어서 어쩔 수 없군. 하지만 다음에는 꼭 보답할게.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"! 기다리게 하는 걸 즐기는 줄 알았잖아. 거기서 동상처럼 서 있기만 할 건 아니지? 이 시간을 훨씬 더 잘 쓸 방법이 있는데.";
							link.l1 = "아무도 당신의 매력에 저항할 수 없지... 시간 낭비할 필요 없으니, 지금 바로 위층으로 올라갈게.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "넌 정말 유혹적이구나, 베시... 하지만 안타깝게도 지금은 다른 곳에 가야 해.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "질문 몇 가지 하고 싶소.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "위층으로 올라가라고 했잖아. 여기 있지 말고 괜히 눈에 띄지 마.";
					link.l1 = "알았어, 간다. 너 곤란하게 만들고 싶진 않으니까...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "나는 여기 온 지 얼마 안 됐으니, 제발 내 일에 방해하지 마. 아직도 익숙해지질 않아서...";
					link.l1 = "그 전에 여기서 일하던 여자 종업원은 어디 갔지? "+pchar.questTemp.different.FackWaitress.Name+", 내가 기억하기로는...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "또 오렴, 자기야. 우리 더 재미있게 놀 수도 있을 텐데. 시간이 좀만 더 있었으면 좋았을걸...";
					link.l1 = "물론이지, 너 정말 대단했어!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "난 너를 모르니까, 귀찮게 하지 마라...";
					link.l1 = "내 돈 어디 있어?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "미안해, "+GetSexPhrase("잘생긴","예쁜이")+", 지금은 너무 바빠. 술집에 가기엔 좋은 때지만, 얘기할 시간은 아니야!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "제발요, 선장님, 여기서 싸우지 마십시오! 이곳 청소하는 게 얼마나 힘든데요.";
					link.l1 = ""+GetSexPhrase("흠... 나도 그럴 생각 없었어.","내가 싸움이나 찾는 주정뱅이처럼 보여? 나도 너랑 똑같은 아가씨일 뿐이야, 걱정하지 마.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("오, 선장님! 오늘 밤 저와 함께 잠자리를 같이 하시겠어요? 자랑은 아니지만...","앉으시오, 선장. 당신 같은 진짜 바다늑대를 만나는 건 언제나 반갑소.")+"";
						link.l1 = "지금은 급해서 아쉽군. 다음에 보자!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "기꺼이, 자기야!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "앉으시오, 선장. 우리 럼주도 맛보고, 카드나 주사위 게임도 한 판 하시오. 집처럼 편하게 있으시오! 당신 같은 진짜 바다늑대를 만나는 건 언제나 즐거운 일이오.";
						link.l1 = "고맙다, 예쁜이.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "뭔가 주문하고 싶으면 주인한테 말해. 저기 바 뒤에 있어.";
					link.l1 = "조언 고마워.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "쉬고 건강을 회복하고 싶으면 방을 빌리시오.\n밤새 홀에 있어 봐야 별 도움이 안 될 거요.";
					link.l1 = "감사하오.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "몇 가지 질문을 하고 싶소.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "그럼 잘 들어. 여기 선술집에서 방을 빌려. 거기로 가서 나를 기다려. 내가 좀 있다가 몰래 들어갈 테니까...";
			link.l1 = "하! 내가 해낼게, 자기야! 기다리고 있을게!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "그녀는 더 이상 여기서 일하지 않아, 은퇴했어... 미안하지만, 나는 할 일이 있어.";
			link.l1 = "좋아...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "잘 들어, 이 음탕한 바보야. 네 돈이 어디 있는지 나는 몰라! 그리고 계속 들이대면 경비병을 부를 거고, 너는 감옥에 처박히게 될 거야!";
			link.l1 = "좋아, 경비는 필요 없어... 이런 바보 같은 놈...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "그래, 그런 바보지. 다음엔 좀 더 현명하고 점잖게 굴도록 해.";
			link.l1 = "해볼게... (속삭이며) 젠장할 창녀 같으니...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "내 말 들리나?";
			link.l1 = "으으...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "몸이 안 좋아? 머리 아파?";
			link.l1 = "젠장... 여기가 어디지?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "기억 안 나? 그놈들이 너를 털었잖아.";
			link.l1 = "뭐라고? 아... 머리가... 누가 감히 이런 짓을?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "내가 어떻게 알겠어? 놈들이 들이닥쳐서 죽이겠다고 협박하고, 네 주머니를 뒤지더니 그냥 가버렸지.";
			link.l2 = "알겠어... 젠장... 물 좀 마시고 싶다... 고마워.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "아니에요, 아무것도 아니에요, 나리... 친절에 감사드리지만, 저는... (울음)";
			link.l1 = "누가 너를 화나게 했어? 진정해, 이쁜이, 다 말해봐.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "아니요, 아니에요, 나리, 아무것도 아닙니다. 제 자제력을 잃은 점 용서해 주십시오, 그저... 제 동생 때문입니다. 사람들은 그가 죽었다고 하지만, 저는 믿지 않아요. 무엇을 믿어야 할지 모르겠지만, 제 마음속으로는 그가 큰 곤경에 처해 있다고 느껴집니다. 그리고 부모님이 돌아가신 후에는 안젤로밖에 남지 않았는데... (울음)";
			link.l1 = "알겠습니다만, 진정해 주시겠습니까? 무슨 일이 형제분에게 있었습니까?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "나리... 오해하지 마세요. 하지만 그런 훌륭한 선장님께서 왜 선술집의 평범하고 소박한 처녀 같은 저를 신경 쓰시는지요? 도와주셔도 제가 드릴 약속조차 없는데요... ";
			link.l1 = "사실, 네 말이 맞아. 이타심은 내 성격이 아니지. 그러니 강해져라, 우리 모두 가족을 잃게 마련이야. 프랑스에서는 이렇게 말하지... 세상사가 다 그런 거야...";
			link.l1.go = "exit";
			link.l2 = "여자는 언제나 남자에게 감사를 표할 방법을 찾지... 하하. 이제 그만 울고 네 문제나 말해봐.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "젊은 세뇨리타, 우리 교회가 서로 돕는 것을 가르친다는 걸 모르고 있소? 내가 할 수 있다면 물론 도와주겠소.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				Notification_Reputation(false, 36, "high");
				dialog.text = "그게 '힌트'였나? 실례했소, 당신과 말한 건 내 실수였군! 안녕히, '카바예로'...";
				link.l1 = "원하는 대로 해, 자기야.";
				link.l1.go = "exit";
			}
			else
			{
				Notification_Reputation(true, 36, "high");
				dialog.text = "그렇다면... 적어도 네 소망에는 솔직하군. 내가 약속하지, 만약 네가 안젤로를 찾거나 그에게 무슨 일이 있었는지 진실을 말해준다면, 네가 요구한 것을 얻게 될 거야...";
				link.l1 = "친애하는 세뇨리타, 당신과 거래하게 되어 기쁩니다... 이제 곧장 당신 오라버니 이야기를 시작하지요.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "장난하는 거야? 정말로 공짜로 나를 도와주고 싶다는 거야?";
			link.l1 = "우는 소녀를 돕지 않는 건 나쁜 놈뿐이지. 걱정 마, 정말로 널 도와주고 싶어. 도대체 안젤로에게 무슨 일이 있었던 거야?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "좋아요, 나리. 제 동생이... 아, 눈물을 참기가 쉽지 않네요, 정말 죄송합니다... 저 때문에, 아니면 제 일의 실패 때문인지... 우리가 정말 가난했거든요... 그래서 안젤로가 동네 밀수업자들과 일하기 시작했어요. 자기 작은 어선으로 세관을 피해서 뭔가를 실어나르면 더 많은 돈을 벌 수 있을 거라고 생각했죠.";
			link.l1 = "간단히 말해서, 네 형제가 범죄자가 된 거지?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "아니에요, 나리, 당신은 잘 모르시는군요... 그는 그런 사람이 아니에요! 저 때문에 그런 거예요! 여기서 몰래 돈 벌지 않게 저를 구하려고 한 거죠... 무슨 말인지 아시겠죠. 우리에게 빚이 있었고, 그는 제 명예와 영혼을 위해 그런 거예요. 그리고... 그는 잡혔어요. 큰 문제는 아니었어요, 저는 그를 풀어주려고 돈을 더 빌리기도 했어요... 그런데 그들이 그가 죽었다고 했어요.";
			link.l1 = "그들이 말했다고? 누가? 그리고 왜 그 말을 믿지 않는 거지? 감옥에서 죽었다고?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "그래. 내가 그의 석방금을 가져갔을 때, 사령관이 안젤로가 폐병으로 죽었다고 말했어. 생각해 봐! 그는 건강하게 그곳에 도착했는데, 이 주 만에 바로 그 감방에서 죽고 말았지. 그들은... 그들은 시신조차 보여주지 않았어. 전염병을 막기 위해 죄수들을 요새 근처 만가에 바로 묻는다고 하더군.";
			link.l1 = "전염병이라고? 꽤 그럴듯하게 들리네. 그냥 못 믿겠다는 건가, 아니면 더 심각한 이유라도 있는 건가?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "아니... 아니야! (울음) 바보 같게 들릴지 모르지만, 그가 죽었다면 분명히 알았을 거야. 알다시피, 안젤로는 항상 강했어. 진짜 선원이었지. 하지만 한 가지 더 있어\n내 할아버지는 내가 어렸을 때 결핵으로 돌아가셨어. 그리고 그분은 노인이었지만 수년간 그 병과 싸웠어! 내가 잘 알아. 결핵은 며칠 만에 사람을 죽이지 않아, 정말이야!";
			link.l1 = "흠... 너 때문에 나도 의심이 생겼어, 뭔가 정말 이상하군. 아무것도 약속할 수는 없지만, 더 알아보려고 해.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "단순한 약속조차도 내가 기대했던 것보다 훨씬 큰 은혜예요! 정말 친절하시군요, 나리! 여기서 기다릴게요!";
			link.l1 = "오, 젊음이여! 참으로 변덕스럽구나... 미인아, 내 손 좀 돌려주겠나, 아직 쓸 일이 남았으니, 하하... 좋아, 그럼 나는 주변을 좀 둘러보고 오겠네.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "아니, 농담 아니야! 위층이야! 건달 둘이 귀족을 죽이고 있어! 도와줘요, 선장님! 무기를 든 사람은 여기서 당신밖에 없어!";
			link.l1 = "밖으로 나가서 경비병을 불러! 나는 위층으로 올라갈게!";
			link.l1.go = "FMQP_1";
			link.l2 = "내 사랑, 나를 경비병으로 착각한 모양이군. 살인 사건이 나면 순찰대를 부르시오.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "아-악, 경비병들! 도와줘!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
