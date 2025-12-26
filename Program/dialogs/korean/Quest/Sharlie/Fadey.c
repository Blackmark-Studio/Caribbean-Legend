int iFadeyPseudoGlobal;

// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> LoyaltyPack
			if (GetDLCenabled(DLC_APPID_1))
			{
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "ready"))
				{
					link.l32 = "파데이, 알론소라는 남자를 아는가?";
					link.l32.go = "LoyaltyPack_Fadey_1";
				}
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "money") && PCharDublonsTotal() >= 1000)
				{
					link.l32 = "파데이, 네가 가진 거울 흉갑을 살 준비가 됐어.";
					link.l32.go = "LoyaltyPack_Fadey_1000";
				}
			}
			//<-- LoyaltyPack
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "무엇을 도와드릴까요, 나리? 저는 아는 사람 아니면 말을 섞지 않습니다. 수다나 떨러 오셨거나, 1640년에 스페인 은화 수송대가 마라카이보에 언제 도착하는지 묻고 싶으시다면, 실망시켜 드릴 수밖에 없겠군요. 쓸데없는 말로 시간 낭비하지 않습니다.";
					link.l1 = "좋은 오후입니다, 파데이 나리. 아직 저를 잘 모르실 수도 있지만, 제 형은 알고 계실 겁니다. 제 소개를 드리겠습니다 - 미셸 드 몽페르의 동생, 샤를 드 모르입니다.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "아하, 또 만났군, 샤를! 잘 지냈나? 이번엔 무슨 일이야?";
					link.l1 = "도둑을 맞았다고 했지... 범인들을 찾았나?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "그래서 샤를, 그 야만인에게 가서 이야기해 봤나?";
					link.l1 = "나는... 그래서 다시 당신에게 돌아온 거요.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "아, 또 만났군, 내 친애하는 친구! 자, 인디언의 몸값인 두블룅을 가져왔나?";
					if (CheckAttribute(npchar, "questTemp.Sharlie.Tichingitu_Skidka"))
					{
						if (PCharDublonsTotal() >= 35) // belamour legendary edition
						{
							link.l1 = "그래. 여기 네 35두블론이다.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "아니, 아직 충분히 모으지 못했어.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 40) // belamour legendary edition
						{
							link.l1 = "그래. 여기 40두블론이오.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "아니, 아직 충분히 모으지 못했어.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "하, 이게 누구야, 드 모르 나리 아니신가! 들어오라고 했잖아, 거기 서 있지 말고! 무슨 일로 내 집에 왔나?";
					link.l1 = TimeGreeting()+", 파데이, 형이 너한테 가보라고 했어. 일 좀 구하는 데 네가 도와줄 거라고 하더라.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "하, 너였군! 여기엔 무슨 일로 왔나, 드 모르 나리?";
					link.l1 = TimeGreeting()+", 파데이. 형이 이 일에 대해 너와 이야기하지 말라고 했지만, 도저히 참을 수가 없었어... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "아, 오랜 친구여! 들어오게, 들어오게, "+pchar.name+"! 잘 지내시오?";
					link.l1 = TimeGreeting()+", 파데이. 만나서 반갑군. 사실 중요한 이야기가 있어. 검은 황금 말이야.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "아, 또 만났군, 내 친애하는 친구! 전리품은 챙겼어? 두블룬은 충분히 찾았나?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "예, 파데이 나리! 여기 금화가 있습니다.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "아니, 그냥 지나가는 길이야. 아직 적당한 양을 찾고 있는 중이야.";
						link.l1.go = "exit";
					}
					
					link.l2 = "파데이, 방금 좋은 생각이 떠올랐어. 이제 노예들은 더 이상 필요 없어. 미안하지만, 이만 가볼게. 나중에 보자!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "아, 내 오랜 친구여! 들어오게, 들어오게, "+pchar.name+"! 잘 지내시오?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", 다시 한 번 당신의 도움이 필요하오.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", 파데이. 만나서 반갑군. 너와 볼일이 있어.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "아, 또 만났군, 내 친애하는 친구! 자, 돈은 찾았나?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "받으십시오, 파데이 나리! 여기 75두블룬이오.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "받으십시오, Fadey 나리! 여기 4만 페소가 있소.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "아니, 그냥 둘러보는 중이야. 아직 적당한 금액을 찾고 있어.";
						link.l3.go = "exit";
					}
					link.l4 = "실례하지만, 파데이, 나는 그럴 여유가 없어. 내가 알아서 해볼게. 또 보자!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "들어오시오, 들어오시오, "+pchar.name+"! 네 눈을 보니 내 성공담을 듣고 싶어 하는구나.";
					link.l1 = "정확해, 파데이. 내가 원하는 걸 가져왔겠지.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "아, 또 만났군, 내 친애하는 친구! 자, 돈은 찾았나?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "75두블룬을 가져가. 선원들에게 이 상자를 내 배로 옮기라고 시키겠어. 아, 파데이, 네가 없었으면 어쩔 뻔했겠냐?! 네가 나한테 얼마나 큰 도움을 줬는지 모를 거야!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "4만 페소를 가져가. 선원들에게 이 상자를 내 배로 옮기라고 시키겠어. 아, 파데이, 네가 없었으면 어쩔 뻔했나?! 네가 얼마나 큰 도움을 줬는지 모를 거야!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "아니, 그냥 지나가는 길이야. 아직 충분히 모으려고 애쓰는 중이거든.";
						link.l3.go = "exit";
					}
					link.l4 = "실례하네, 파데이. 나 완전히 빈털터리야. 보증금은 그냥 가지게. 이번 거래에 드는 비용을 충당하기에 충분하길 바라네. 나는 알아서 해볼 테니. 또 보세!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				//--> Дикая Роза
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey"))
				{
					dialog.text = "아, 여기 있었군, 좋은 사람이여! 자네 배가 우리 항구에 닻을 내렸다는 소식을 듣고, 혹시 나를 찾아올까 기대했네.";
					link.l1 = "안녕하세요, "+npchar.name+". 긴 이야기는 하지 않겠소. 내 동료 메리와 나는 그녀의 아버지를 찾고 있소, 그분은 이십 년 전에 흔적도 없이 사라지셨지...";
					link.l1.go = "WildRose_Fadey_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2")) 
				{
					link.l31 = "메리의 아버지에 관해서라면...";
					link.l31.go = "WildRose_Fadey_return";
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3"))
				{
					dialog.text = "이봐, 이게 누구야, "+pchar.name+"!";
					link.l1 = "정말 빛이 나는군, "+npchar.name+". 그러니 말해 보게—뭔가 알아낸 것이 있나?";
					link.l1.go = "WildRose_Fadey_16";
					break;
				}
				//<-- Дикая Роза
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "아, 표시된 자여—아니, 내 말은\n "+pchar.name+"! 자, 어서 내게 뭐가 있는지 말해 봐!";
					link.l1 = TimeGreeting()+", 파데이. 만나서 반갑소. 사업 이야기를 하러 왔소.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". 내 영혼을 찾는 신부와의 대화 결과가 궁금하지?";
					link.l1 = "물론이지! 어떻게 됐어?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "아, 용서하시오, 당신 주머니에서 나는 짤랑거림에 정신이 팔려 있었소!";
					link.l1 = "이렇게 탐욕스럽다니, 파데이! 여기 네 금이다.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "아하, 내 오랜 친구! 들어와, 들어와, "+pchar.name+"! 그래서, 새로운 소식이라도 있나?";
					link.l1 = "안녕, 파데이. 다시 한 번 네 도움을 부탁하러 왔어.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "뭐야, 동상이라도 된 거야? 할 말 있으면 털어놔. 아니면 꺼져. "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "한번 봐, 파데이. 이게 페르시아 샴시르인 것 같은데, 네 소장품에서 도난당한 것 중 하나 아니야?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "좋은 소식이 있소. 여기 또 다른 페르시아 샴쉬르가 있소.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "세 번째 페르시아 샴쉬르가 있소. 부탁하신 대로 최대한 빨리 가져왔소.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "우리가 얘기했던 경갑옷 때문에 왔소.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "파데이, 네가 유명한 밧줄을 좀 사고 싶군.";
					link.l3.go = "ropes";
				}
				link.l1 = "파데이, 네 도움이 필요해.";
				link.l1.go = "help";
 				link.l9 = "아니, 지금은 아무것도 없어.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "무엇을 도와드릴까요, 나리? 저는 아는 사람 아니면 말하지 않습니다.";
				link.l1 = "아, 그냥 여기 누가 사는지 보러 잠깐 들렀을 뿐이오.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "아, 그럼 당신이 미셸 그 친구의 막내 동생이구만! 그거라면 얘기가 달라지지! 어서 들어오시오, 들어오시오, 나리, 자리에 앉으시오. 우리 만남을 축하하며 보드카 한잔 올릴 생각 없소? 아직 몇 병 남아 있으니, 좋은 친구의 동생과 함께 나누면 참 기쁠 것 같구려, 다!";
			link.l1 = "용서하십시오, Fadey 나리, 하지만 오늘 밤은 술자리를 가질 생각이 없습니다. 곧장 본론으로 들어가고 싶군요.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "뭐라고 하는 거야! 이 동네 럼은 러시아 보드카에 비하면 맹물이나 다름없지! 네가 뭘 놓치고 있는지 모르는구나, 내가 거짓말이면 바다가 날 삼켜도 좋아! 좋아, 이제 본론으로 들어가자. 듣고 있네, 샤를.";
			link.l1 = "나리, 지금부터 드릴 말씀이 매우 불쾌하실 것 같으나, 유감스럽게도 제 의무이기에 말씀드려야 하겠습니다! 미셸이 그러는데, 당신께서 그와 도박을 하다가 꽤 큰 돈을 빚졌다고 하더군요. 그리고 그 돈을 저에게 넘기라고도 했습니다. 제 형이... 지금은 직접 당신을 찾아올 수 없는 처지라서 그렇답니다.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "오, 젊은이! 물론이지, 나는 모든 걸 기억하고 네 형에게 빚이 있다는 것도 인정하네. 도박빚은 신성한 법, 그 의무를 지키는 것만이 우리를 치명적인 무질서와 위험한 도적 떼로부터 구해주지! 하지만 제발, 내 처지를 좀 이해해주게! 최근에 아주 불쾌한 일이 있었네—누군가 나를 정말 뻔뻔하게 털어갔지!\n저주받을 도둑놈들이 가져갈 수 있는 건 다 가져갔어, 내가 수년간 힘들게 모은 돈과 무가치할 수 없는 내 소장품까지! 지금 당장은 빚을 갚을 수가 없어, 정말이야\n하지만, 드 모르 나리, 나는 내 의무를 포기하지 않네! 단지 자네에게 반쯤만 양보해달라는 것일 뿐이야. 어차피 지금 내 손에 동전 한 닢도 없으니, 이 훌륭하고 희귀한 단검을 내놓겠네. 한번 보게!\n이건 진짜 강철의 걸작, 내 도난당한 소장품의 자랑이었지. 게다가 인디언 주술사들이 마법을 걸어서 강력한 숨겨진 힘이 있다네! 인디언들은 이것을 추장의 발톱이라 불렀지\n사실 이 단검을 내놓을 생각은 전혀 없었네, 내가 이 빚보다 훨씬 많은 돈을 주고 샀으니까. 하지만 이런 상황과 자네 형님과의 관계를 생각해서, 자네에게 주겠네. 받아두게, 정말 좋은 거래라네!";
			link.l1 = "나는 칼보다는 돈이 훨씬 더 좋겠어...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "하지만 나는 돈이 없고, 대신 이 희귀한 마법 유물을 가지고 있지! 정말로 그렇게 생각하나, 드루그 모이, 내가 이런 멋진 마법 단검을 아무 쓸모 없는 은화 몇 닢 대신에 다른 상황에서 내놓을 거라고? 페소 따위야 길바닥에도 널렸지! 솔직히 말해서, 지금 꽤 곤란한 처지란 말이야. 이 놀라운 장인의 작품과 헤어진다는 생각만 해도 가슴이 찢어진다네, 하지만 도박빚은 명예의 빚이니 자네에게만 주겠네. 내게는 아주 소중하지만, 자네가 진정한 명예의 사나이이자 진정한 친구이기 때문이야.";
			link.l1 = "좋아, 돈이 정말 없다고 맹세하니 네 이 마법 단검을 가져가겠다. 잘만 하면 비싼 값에 팔 수 있겠지...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'팔라고'!? 나가, 도둑... 아니, 샤를! 이런, 내 귀를 의심하겠군! 내가 내 가장 소중한 보물을 그냥 내주고 있는데, 유럽에선 최소 열 배는 더 받을 수 있는 건데, 너는 뻔뻔하게 그걸 전당포에 맡기겠다고!? 이 단검이, 젊은이, 한 남자의 목숨을 구한 물건이야! 내가 이야기 좀 해주지-\n";
			link.l1 = "그리고 그대가 말한 그 숨겨진 힘이란 무엇이오?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "오, 호호호! 자, 샤를, 나는 선량한 그리스도인일세. 인디언 주술사가 아니란 말이지. 이 검에 숨겨진 모든 비밀을 내가 알 방법은 없어. 하지만 분명히 뭔가 있지! 이 단검을 손에 쥐어 보게. 그러면 그 힘을 직접 느낄 수 있을 걸세! 자, 받아, 받아! 어때? 뭔가 느껴지나?";
			link.l1 = "흠... 아무런 감각도 없군. 그래도 손에 쥐기는 편하네.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "아하! 바로 그거요! 하지만 그건 이 단검의 가장 하찮은 특징일 뿐이오. 전투에서 이 단검을 휘두르면, 분명 여러 극적인 방식으로 그 힘을 보여줄 것이오! 자, 그럼 가져가시겠소?";
			link.l1 = "글쎄, 내가 선택권이 있나? 네가 돈이 없으니 내가 받아들이지.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "고마워, 샤를. 절대 후회하지 않을 거야, 정말이지! 여기 있어. 그리고 꼭 미셸에게 내 안부 전해 줘! 기회가 되면 언제든 들르라고 해 줘.";
			link.l1 = "아, 내가 그에게 말할게...";
			link.l1.go = "exit";
			link.l2 = "도둑을 맞았다고 했지... 범인들을 찾았나?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "문제는, 내가 그렇지 않다는 거요. 그 불한당들이 집안을 몽땅 털어가 버렸소. 은, 금, 내가 수년간 뼈 빠지게 일해서 모은 저축까지 다 가져갔지. 뭐, 보통 때라면 그런 건 신경도 안 썼을 거요. 결국 진정한 신사라면 가진 걸 모두 잃더라도 감정 하나 내비치지 않아야 하니까! 돈이란 신사에게 너무 하찮은 것이어서 굳이 신경 쓸 가치조차 없지. 하지만 가장 괴로운 건, 그놈들이 내 자랑스러운 페르시아 샴시르 컬렉션까지 몽땅 쓸어갔다는 거요! 신세계든 구세계든 이런 컬렉션은 어디에도 없소. 정말로 놀라운 페르시아 기병도였는데...\n";
			link.l1 = "페르시아 검이라고? 꽤 흥미로운데. 그럼, 자네 수집가인가?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "음, 나는 희귀한 물건을 모으는 걸 좋아하지... 있잖아, 샤를, 혹시 이 일에 네가 좀 도와줄 수 있을까...";
			link.l1 = "도움? 하지만 어떻게? 도둑들을 잡으라는 말인가?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "아니. 도둑놈들에는 별로 관심 없어. 내 페르시아 기병도만 돌려받고 싶을 뿐이야. 만약 찾아주면, 반드시 보답하겠다고 약속하지.";
			link.l1 = "흠. 그런데 대체 어디서 그들을 찾아야 하지? 카리브 해 일대인가? 아니면 전 세계를 돌아다녀야 하나?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "음, 어쩌면 섬의 노상 상인들한테서 그놈들을 볼 수도 있겠지; 그 악당들은 저 기병도 검의 가치를 전혀 모르는 놈들이라 고철값에 팔아버릴 거야. 그러니 페르시아 검을 어디서든 보거든 나한테 가져오게. 알아볼 수 있겠나?";
			link.l1 = "그래야겠군. 좋아, 내가 두 눈 부릅뜨고 있을 테니, 설명에 맞는 특이한 검을 보면 꼭 가져다주지.";
			link.l1.go = "Sharlie_12";
			link.l2 = "있지, 나는 고급 무기에 대해선 전문가가 아니야. 미안하지만 도와줄 수 없을 것 같아. 괜히 헛된 희망을 주는 건 정직하지 못하겠지.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "좋아! 네가 운이 좋아서 그 유물들을 찾길 바란다, 그리고 그 보상은 확실히 해주지. 사냥 잘 하라고, 스토커— 아니, 선장! 자, 샤를, 상상이나 해봐, 나 또 강도 당할 뻔했어!\n며칠 전에 어떤 도둑이 내 집에 침입하려고 했거든\n정말 너무하더라! 하지만 이번엔 도망 못 쳤지, 내가 놈을 잡아서 실컷 두들겨 패고, 마을 감옥에 있는 경비병들한테 넘겼어. 빨리 교수형에 처했으면 좋겠다!";
			link.l1 = "그자가 네 샴시르를 훔쳐간 도둑 중 하나라고 생각하나?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "안타깝지만, 이미 엎질러진 물이지. 그래, 샤를, 상상이나 해 봐. 최근에 또 한 번 도둑이 들려고 했어!\n며칠 전에 어떤 도둑놈이 내 집에 침입하려 했지\n정말 너무하더군! 그래도 그놈을 놓치진 않았어. 내가 직접 잡아서 실컷 두들겨 패고, 현지 감옥에 쳐넣었지. 남의 불행 위에 행복을 쌓을 순 없는 법이야. 곧 교수형에 처해지길 바란다!";
			link.l1 = "그 자가 네 샴시르를 훔쳐 간 도둑 중 하나라고 생각하나?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "아니, 나는 그렇게 생각하지 않아. 그 자는 돈을 노렸지. 내 방에서 내 궤짝을 뒤지는 걸 붙잡았거든\n스페인령 본토의 깊은 정글에서 온 인디언이야. 이 근처의 현지인들과는 전혀 다르게 생겼고, 우스꽝스럽게 보이지. 온몸에 전쟁 화장을 하고 알록달록한 옷을 입었더군... 네가 원한다면 지하 감옥에 가서 그 어릿광대를 직접 보는 것도 괜찮을 거야, 아직 살아 있을 때 말이지.";
			link.l1 = "흠... 한번 들러서 그를 볼까.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "어서 해봐, 괴짜 구경이나 실컷 해라... 좋아, 샤를, 즐거운 대화였어. 마르티니크로 돌아가는 길에 순풍이 불길 바라!\n";
			link.l1 = "행운을 빌어, 파데이.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("Tichingitu_SetTichingituJail");
			SetFunctionTimerCondition("Tichingitu_FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "흥미롭군! 듣고 있네.";
			link.l1 = "파데이, 그 인디언과 얘기했어. 그래서 너한테 그를 빼내는 걸 도와달라고 온 거야. 불쌍한 녀석은 그냥 먹을 것 좀 먹고 싶었던 것뿐이야...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "하하하, 그 이야기를 믿었단 말이오? 요즘 젊은이들은 참 순진하구나...";
			link.l1 = "파데이, 내가 너보다 어리긴 해도, 누가 진실을 말하는지 거짓말을 하는지는 나도 알 수 있어. 그리고, 그런 죄에 교수형이 적절한 벌이라고 정말 생각하나? 너무 과한 것 같은데. 우리 고향에서는 재범이어도 채찍질 몇 대나 낙인 정도면 끝나지.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "지나치다고!? 그 놈이 내 집에 침입했어! 저 야만인은 애초에 여기 오지 말았어야 했지! 네가 내 입장이었다면 어쨌겠냐? 분명 네 손으로 그놈의 창자를 꺼내서 벌레밥으로 만들었을 거 아냐, 안 그래!?";
			link.l1 = "아니, 안 그럴 거야, 파데이. 네가 아직도 도둑맞은 샴쉬르 컬렉션 때문에 화가 나 있잖아. 그 일이 없었으면, 이 멍청한 붉은놈을 제대로 두들겨 패고 엉덩이에 발길질이라도 했을 거 아냐, 내가 틀렸어?\n";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "아아, 샤를... 너도 네 형과 똑같구나... 좋아. 우리 신사답게 사업가처럼 해결하자. 네가 이 인디언을 그토록 원한다면, 그가 내게 끼친 정신적 고통과 재산 피해를 보상해라. 그러면 나도 사령관에게 더 이상 고소하지 않겠다고 말하지. 어때?";
			link.l1 = "얼마야?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "하, 벌써 카리브의 방식을 배우기 시작했구나, 샤를. 백오십 금화 두블론이야, 코페크 하나도 깎아줄 수 없어.";
			link.l1 = "파데이, 신의 자비를...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "좋아, 좋아, 40골드 두블룬이야. 하지만 그게 최종 가격이야. 그리고 두블룬으로, 페소 말고. 우리 전당포 주인한테 분명히 좀 있을 거야.";
			if(PCharDublonsTotal() >= 40) // belamour legendary edition
			{
				link.l1 = "지금 필요한 금액이 있소. 자, 여기 40두블룬을 가져가시오.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(믿을 만한) 파데이, 들어봐... 네가 답답한 건 이해하지만, 이 불편에 대해 진짜 돈으로 보상해줄 사람은 나뿐이야.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "좋아요, 내가 가서 필요한 걸 가져올게.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "오, 자네라면 크게 성공하겠군, 친구. 설득당했네! 35골드, 한 푼도 깎아줄 수 없어!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			npchar.questTemp.Sharlie.Tichingitu_Skidka = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "그리고 서둘러라, 샤를! 그가 처형되기까지 열흘밖에 남지 않았다.";
			link.l1 = "명심하겠소. 안녕히 가시오!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka"))
			{
				RemoveDublonsFromPCharTotal(35);
				DeleteAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka");
			}
			else RemoveDublonsFromPCharTotal(40); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "아주 좋소. 지금 바로 문서를 작성하고 인장을 찍겠소, 잠깐만 기다리시오... 자, 여기 있소. 이걸 사령관에게 주면 인디언을 데려갈 수 있소. 왜 그렇게 그를 걱정하는지는 잘 모르겠지만, 그건 자네 문제지. 뭐 할 건가, 가면무도회에 전시라도 하겠다는 건가? 하하, 별 생각을 다 하네!";
			link.l1 = "신은 모든 것을 보고 계시네, 파데이. 사람의 생명을 구하는 일은 고귀한 행위지.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "첫 번째 말씀에는 동의하오, 하지만 두 번째는 논쟁의 여지가 있소, 샤를. 만약 그 밧줄 끝에서 정의를 기다리는 살인자나 강간범을 구해 준다면 어찌 되겠소? 에이, 뭐, 이제 내 일이 아니니 상관 없소. 신의 가호가 있기를. 빨리 사령관에게 가시오, 자네의 붉은 피부 친구가 목에 밧줄이 감겨 창백해지기 전에...";
			link.l1 = "가는 중이야. 이따 보자, 파데이.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "표정이 어둡군, 친구! 혹시 나한테 안 좋은 소식을 전하려는 거지?";
			link.l1 = "그게 전부야, 맞아. 솔직히 말할게, 파데이. 미셸이 그러더군, 네가 이 '족장의 발톱'이라는 헛소리로 나를 속였다고. 이건 유물이 아니라 아무 거리 상인한테 몇 백 페소면 살 수 있는 물건이라고 했어. 그래서 금속 잡화 파는 거리 상인들한테 물어봤지. 딱 그 가격을 부르더라.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "오, 드 모르 나리... 나는 상처를 입었소! 네 형에게 정말 놀랐구나. 거리의 얼간이 장사치들이야 뭐든 떠들 수 있지만, 그분이! 말해보게, 샤를, 만약 누군가가 샤를마뉴 시대의 오래된 양손 기사 검을 가져와서 자네에게 팔겠다고 한다면, 자네는 그걸 얼마에 사겠나?\n";
			link.l1 = "양손검이라고? 지금 나랑 장난하냐, 파데이? 녹슨 사형집행인의 칼 따위가 나한테 무슨 소용이 있겠어? 지금이 우리 주 예수 그리스도의 17세기라고! 그딴 거에 페소 한 푼도 안 주겠다!";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "아, 이제야 네 근시안적인 태도가 보이는구나, 친구! 그런 마음가짐으론 아무 데도 못 갈 거야. 만약 네가 그런 유물을 나에게 가져왔다면, 나는 삼백 두블론을 주고 샀을 거다. 왜냐고 묻겠지? 그것은 골동품이자, 역사적인 보물이며, 요즘 세상에선 구하기 힘든 것이기 때문이지! 넌 이해하지도 못하면서 판단만 하잖아! 하느님과 성모 마리아를 증인 삼아 말하건대, 추장의 발톱은 걸작 단검이야—내 소식통에 따르면 코르테스 본인이 소유했던 물건이란다. 바로 그 에르난 코르테스! 테노치티틀란을 함락시키고 아즈텍 황제를 사로잡은 전설적인 정복자 말이야! 그런데 넌 비웃으면서 그게 흔한 쓰레기라고 하잖아! 게다가 내가 이미 말했듯이, 그건 아무 단검이 아니야—마법이 깃든 단검이라고! 아직도 카리브 해의 온갖 경이로움을 다 못 봤단 말이냐? 주문과 마법, 의식과 저주 말이다! 샤를, 여기는 신세계야, 마야와 아즈텍의 고향이지. 그들은 우리 그리스도인들로선 상상도 못 할 악마적 예술의 경지에 도달했었지! 이 단검에는 숨겨진 힘이 있어. 안타깝게도 아직 그 힘이 뭔지는 아무도 몰라. 네가 직접 그 능력을 알아낼 수 있는 유일무이하고 놀라운 기회가 있는데도, 넌 여전히 그걸 ‘쓰레기 조각’이라 부르고, 네 불쌍한 옛 친구 파데이가 널 속이려 했다고 생각하는구나! 내가 네 형에게 진 빚만 갚을 돈이 있었다면, 당장이라도 그 단검을 네 더러운 동전과 다시 바꿔갔을 거다... 이건 정말 값진 물건이고, 그 가치는 돈만으로 따질 수 있는 게 아니야, 다!";
			link.l1 = "좋아, 좋아, 진정해, 파데이. 나는 네 말을 믿어. 네 주장은 꽤 설득력 있고, 네가 보여주는 그 불타는 열정은 네 진심의 증거이거나 아니면 비할 데 없는 교활함의 증거겠지.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "고맙소! 기분 상하지 않고 곧장 내게 설명을 들으러 온 것은 잘한 일이오, 샤를. 이제 이 문제는 해결된 것이오?";
			link.l1 = "예, 파데이 나리. 완전히 그렇습니다. 이제, 부디, 실례를 무릅쓰고 물러가겠습니다...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "멈춰, 샤를! 솔직히 말해서, 난 네 스타일이 마음에 들어. 언젠가 우리 둘이 절친이 될 수도 있지 않겠어? 그 우정의 첫걸음을 지금 내딛는 건 어때? 지하 저장고에 훌륭한 러시아 보드카 두 병을 얼음처럼 차가운 샘물에 식혀두었지. 어때, 네 형의 건강을 위해 한 병 따볼까?\n";
			link.l1 = "흠. 미안하오, Fadey 나리, 하지만 이제 출항할 시간이 되었소. 내가 좀 급해서 그러오.";
			link.l1.go = "vodka_no";
			link.l2 = "지난번에 네가 제안했을 때 내가 거절했지... 두 번 거절하는 건 예의가 아니겠군. 좋아, 파데이. 나도 끼겠어!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "안타깝군. 보드카에 비하면 럼은 그냥 물이나 다름없지, 싸구려 밍밍한 술일 뿐이야. 하지만 급하다니 더 붙잡진 않겠네. 사냥 잘 하게, 샤를!";
			link.l1 = "그대도 마찬가지요, Fadey 나리...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "바로 그 말이 듣고 싶었소! 훌륭하군! 앉아서 편히 쉬시오! 부디, 나리, 집처럼 편하게 계시게. 내가 보드카를 가져오리다. 아, 친구들과의 이런 오후 모임이 얼마나 그리웠던지! 자, 보드카가 아주 시원하니 분명히 마음에 들 거요, 나즈도로비야! 피클과 훈제 햄도 내어드리겠소.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "우와... 그러니까, 파데이, 그게 어떻게 된 거냐고? 히끅! 우리... 보드카 두 병이나 마셨잖아... 그런데 말이지! 너는 멀쩡해 보이는데 나는... 완전 만취야. 이게 어떻게 된 거냐, 응?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "샤를, 친구야, 진정해. 이 모든 일에 스컹크가 무슨 상관이 있겠어? 우리 방금 훌륭한 보드카를 마셨잖아. 좀 자고 일어나면 눈도 반짝이고 기운도 넘칠 거야. 숙취도 없이 머리까지 맑아질 거라고. 곧 알게 될 거야.";
			link.l1 = "으-응, 보드카... 이거... 이 보드카 정말 끝내주네. 이런 건 처음 마셔봐.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "하! 맞는 말이야! 그런 보드카는 비밀 레시피로 만들어서 내 조국 러시아에서 들여온 거지. 거기서도 아무나 제대로 만들 줄 아는 게 아니야. 난 최고만 사지! 너랑 내가 지금 맛본 이 술처럼 말이야.";
			link.l1 = "그, 그런데 말이야, 파데이. 어, 어떻게 그렇게 술을 많이 마셔도 안 취하는 거지? 그, 그 비결이 뭐야, 응? 나한테도 좀 알려줘. 나중에 쓸모가 있을지도 모르잖아... 히끅!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "하! 그래, 너 따위가 나랑 비교될 줄 아냐, 어린 샤를! 너 좀 봐라, 채찍처럼 말랐잖아. 게다가, 진짜 술 마시는 것도 익숙하지 않지, 안 그래! 하지만 우리가 진짜 친구니까, 술 마시고도 오줌 지리지 않는 비법 몇 가지 알려주마.";
			link.l1 = "부, 부탁이야... 힉!";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "자, 제대로 마시고 바로 뻗지 않으려면 몇 가지 중요한 규칙을 따라야 해. 가장 중요한 건, 빈속에 술을 마시지 않는 거야. 술자리가 시작되기 전에 든든하게 뭔가를 먹어야 해\n둘째, 잔을 비울 때마다 꼭 뭔가를 먹는 걸 잊지 마. 고기나 생선처럼 짭짤한 게 최고지. 셋째, 보드카로 입을 헹구지 말고 한 번에 삼켜\n그리고 식사 전에 소량, 즉 반 파인트를 넘지 않는 정도로 한 잔을 마시면 몸이 본격적인 알코올 흡수에 대비할 수 있어. 이 애피타이저를 너무 많이 마시면 오히려 반대 효과가 나서 출항도 전에 망가질 수 있으니 조심하고\n마지막으로, 규칙적인 훈련이 중요해. 럼주나 다른 술을 적당히 자주 마시는 습관을 들이면 점점 더 잘 버틸 수 있게 될 거야.";
			link.l1 = "흠-음... 그-그래서 이렇게 하는 거구나! 나, 분-명히... 힉!.. 네가 알려준 거 다 기-억할게, 파데이. 고-마워. 그리고 이-제 나 좀 자는 게 좋을 것 같아, 지금은 몸이 영 안 좋아서.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "쉬게, 샤를. 오늘 밤 즐거웠어, 너랑 나! 사냥 잘 하길 바라!";
			link.l1 = "다, 다, 다스비다니야, 파데이! 난 이제, 딸꾹! 소원을 들어주는 자에게 간다!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "뭐라고, 그가 내가 너를 도와줄 거라고 정말 말했다고?";
			link.l1 = "뭐, 거의 그렇지. 오랜 친구의 동생에게 한 번 도와줄 생각 있나? 거지처럼 동냥을 달라는 게 아니야. 돈 좀 벌 기회를 달라는 거지.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "오, 샤를! 늦었구나. 좀 더 일찍 왔더라면 네게 맞는 일을 찾아줬을 텐데, 지금은... 미안하구나. \n걱정 말고, 도시를 돌아다니며 사람들과 이야기해 보아라. 카리브에는 할 일이 아주 많으니.";
			link.l1 = "알겠소, 유감이오. 안녕히 가시오!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "흠. 아니, 물론 거절하지는 않겠소. 사람을 먹여 살리고 싶다면, 물고기를 주는 게 아니라 낚싯대를 주라는 말이 있지 않소, 드 모르 나리? 일자리가 필요하다 이거군... 그리 어렵지 않지. 내가 아는 사람과 얘기해보고, 그에게 자네를 추천해 주겠소. 그 다음은 자네가 일을 얼마나 잘하느냐에 달려 있네.";
			link.l1 = "훌륭하군. 누구와 이야기해야 하지?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "내일 가게로 오게. 제라르 르크루아라는 이름의 남자가 그곳에서 자네를 기다릴 걸세.\n그가 자네에게 일을 줄 것이니, 내일까지 이 식민지에만 머물 거야.\n서둘러 그를 만나고, 일을 제대로 처리하게.\n나를 곤란하게 만들지 말게.";
			link.l1 = "거래 성사됐네. 고마워, 파데이!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "아, 어떻게 도와줄까, 친구?";
			link.l1 = "파데이, 들어봐. 밀수업자들에게서 노예 50명을 꼭 사야 해. 문제는 내가 그들에게 전혀 알려지지 않은 사람이란 거야. 네가 나를 소개해 줘야 해. 네 도움이 없으면 그 자들이 내 말은 들으려 하지도 않을 거야. 이건 아주 중요한 사람의 생사가 달린 일이야.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "오호! 사업을 확장하는군, 보이네! 참으로 수익성 있겠어! 내가 도와주지, 친구. 하지만 알다시피, 나는 공짜로 일하지 않아. 네가 선의로 흑인들을 사려 한다는 걸 판매자에게 납득시키려면 금화 150더블룬이 필요하고, 물론 내 수고에 대한 약간의 보너스도 있어야겠지...\n";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "나는 그 정도는 당연히 기대했소, Fadey 나리! 여기 금화요.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "나는 지금 당장 고리대금업자에게 갈 거야! 잠깐만 기다려, 파데이 나리, 금방 돌아올게!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "파데이, 뭔가 생각이 떠올라서 이제 흑인들은 필요 없어. 미안해. 또 보자!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "훌륭하군, 친구. 하지만 이 구매가 정말 필요한 척 나를 속이려 하거나 네 의도가 하찮다면, 나는 몹시 화가 날 거다. 그러길 바라지 않을 거야. 내일 열 시, 해질 무렵, 캡스터 해변에서 네게 만남을 주선하겠다. 실망시키지 마라.";
			link.l1 = "걱정할 것 없어, 내가 물건 가지러 다시 올 테니까.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "안녕, 안녕! 이봐, 좋은 친구, 내 소박한 집에 무슨 일로 왔는지 말해 보게나?";
			link.l1 = "무기가 필요하오. 이곳 상인들은 내가 원하는 만큼의 수량을 구하지 못하지만, 자네라면 도와줄 수 있을 것 같군.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "우선, 친애하는 친구여, 무엇이 필요한지 정확히 말해 주게. 그 다음에 내가 도울 수 있는지 말해 주겠네.";
			link.l1 = "병사용 권총 30정, 화승총 2정, 그에 맞는 탄약 70발, 그리고 치료 물약 90개가 필요하다.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", 너 때문에 겁나잖아. 처음엔 흑인 노예 쉰 명, 그 다음엔 무기라니. 설마 노예 반란이라도 일으키려는 거야, 친구?";
					link.l1 = "눈치가 빠르군, 파데이. 아까도 말했듯이, 이 모든 건 아주 중요한 한 사람을 구하기 위해서 필요하네. 걱정 마, 그 사람은 스페인 놈들 손아귀에서 반드시 구해낼 테니 자네 평판에는 아무런 해가 가지 않을 걸세.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "그거 다행이군. 내가 도와줄 수 있소.";
			link.l1 = "그 말을 들으니 기쁘군. 얼마지?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "자네가 설명해 줘서 기쁘군. 그리고 이 일이 정말 스페인 놈들과 관련된 거라면 내가 도와주지. 하지만 나를 속인 거라면, 아주 화가 날 거다.";
			link.l1 = "나를 좀 믿어 봐, 파데이. 얼마나 필요한데?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "좋아, 그러니까... 권총 몇 자루와 머스킷 두어 자루, 그리고 각각에 쓸 화약과 탄환이지... 그래서 말인데... 네가 요구한 걸 전부 다 구해준다고는 장담 못 하겠지만, 내가 할 수 있는 건 다 해볼게. 그동안 보증금으로 4만 페소, 아니면 원하면 75 두블룬을 내야 해.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "두블론을 가져가, 파데이. 마침 지금 가지고 있거든.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "내 두블룬은 다 없어졌으니, 페소나 받아라, 파데이.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "내 은행가와 얘기 좀 해야겠어. 금방 돌아올게!";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "실례하지만, 파데이, 나는 그럴 여유가 없어. 내가 알아서 해볼게. 또 보자!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "내일 오시오, "+pchar.name+", 그리고 네가 필요한 재료도 내가 준비할게.";
			link.l1 = "그럼 방해하지 않겠소. 내일 보세!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "내일 오시오, "+pchar.name+", 그리고 네가 필요한 재료도 내가 준비할게.";
			link.l1 = "그럼 방해하지 않을게. 내일 보자!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "음, 자네, 이렇게 촉박한 시간에 자네가 부탁한 걸 전부 구할 수 있었던 건 정말 운이 좋았지. 고마워해야 할 거야! 이제 마지막 결제다. 계약금으로 준 만큼 똑같이 더 내게 주고, 무기를 가져가게.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "75두블룬을 가져가. 내 부하들이 무기를 내 배로 옮길 거야. 너 없었으면 어쩔 뻔했냐, 파데이? 네가 나한테 얼마나 큰 도움을 줬는지 모를 거야!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "4만 페소를 가져가게. 내 부하들에게 무기를 내 배로 옮기라고 하겠네.\n자네 없었으면 어쩔 뻔했나, 파데이? 자네가 얼마나 큰 도움을 줬는지 모를 걸세!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "젠장, 내가 돈을 잊다니! 곧 돌아올게.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "실례하네, 파데이. 나 지금 빈털터리야. 보증금은 그냥 가지게. 이번 거래에 드는 비용을 충당하기에 충분하길 바라네. 나는 내 힘으로 어떻게든 해볼게. 또 보자!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "도움이 필요한 이들을 돕는 것은 명예요, 돈을 주는 이들을 돕는 것은 즐거움이지. 다음에 바스테르에 오거든 꼭 들러 인사하게나.";
			link.l1 = "말도 안 돼 – 바스테르에 있으면서 내 친구 파데이를 안 본다고! 다음에 또 보자!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "도움이 필요한 이를 돕는 것은 영광이지. 돈을 주는 이를 돕는 것은 즐거움이고. 다음에 바스테르에 오거든 꼭 들러 인사나 하게나.";
			link.l1 = "말도 안 돼 – 바스테르에 있으면서 내 친구 파데이를 안 본다고! 다음에 또 보자!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition
		
		//--> Дикая Роза
		case "WildRose_Fadey_4":
			dialog.text = "참 대단한 계략을 꾸몄구나, "+pchar.name+"! 그 뜻은 분명 고귀하나, 과연 실현 가능하겠소? 이십 년이면 사람을 완전히 바꿔놓을 수도 있지...";
			link.l1 = "맞아, 파데이. 하지만 우리는 많은 시간과 노력을 들였고, 먼 길을 왔지 — 이제 거의 목표에 도달했어. 우리는 그에 대해 거의 모든 것을 알아냈다네: 그의 이름, 폐하의 왕립 해군에서의 복무, 그가 탔던 배의 이름... 그리고 그의 생애에 관한 몇 가지 다른 세부사항도 말이야. 흔적은 1638년 6월 카토체 곶 앞바다에서 일어난 난파선에서 끊기네.";
			link.l1.go = "WildRose_Fadey_5";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey");
		break;

		case "WildRose_Fadey_5":
			dialog.text = "카토슈? 오호, 친구, 나는 막대기로 쫓겨도 그쪽으론 안 간다네 — 저기엔 저주받은 야만인 무리들이 돌아다니거든. 그가 거기까지 갔다가 바다에서 죽지 않았다면, 하느님도 아실 일, 분명히 그 망할 원주민들이 그를 잡아먹었을 게야...\n";
			link.l1 = "이 자가 난파에서 살아남아 이후 쿠바까지 간 증거가 있소. 어쩌면 그곳에서 죽었을 수도 있지만, 우리가 들은 바로는 — 그는 종교재판관들의 손아귀를 피해갈 만큼 교활한 자였소. 쿠바에 머물렀을 가능성은 적고 — 차라리 군도의 어느 정착지에 자리를 잡았을 가능성이 더 크오...\n";
			link.l1.go = "WildRose_Fadey_6";
		break;

		case "WildRose_Fadey_6":
			dialog.text = "이 세상에는 많은 기이한 일이 일어나네, 친구여, 뭐든 가능하지. 하지만 자네가 왜 내게 이 모든 이야기를 했는지는 아직 모르겠군.";
			link.l1 = ""+npchar.name+", 너는 어떤 총독들보다도 더 많은 인맥이 있군. 네 곁에는 간단한 일쯤은 거뜬히 해낼 수 있는 유능한 놈들이 분명 있을 거야...";
			link.l1.go = "WildRose_Fadey_7_1";
			link.l2 = ""+npchar.name+", 당신은 존경받고 영향력 있는 분이오. 상류층에서 활동하며 인맥도 넓지. 사업 이익도 과연 과들루프를 훨씬 넘어설 것이오. 이런 모든 일을 혼자 할 수는 없으니, 분명 신뢰할 만한 대리인들과 머리 좋은 이들을 써서 그리 복잡하지 않은 임무들을 맡기고 있을 터...";
			link.l2.go = "WildRose_Fadey_7_2";
		break;

		case "WildRose_Fadey_7_1":
			dialog.text = "그대는 영리하고 통찰력 있는 사람이오, "+pchar.name+". 그래, 그 말은 이미 들었소. 내게는 유능하고 아는 이들이 있지, 그대 말이 맞소. 하지만 솔직히 말해 보시오 — 그들에게 무엇을 시키고 싶은 것이오.";
			link.l1 = "그들을 군도 여러 식민지로 보내 우리가 찾는 남자에 대해 뭔가 알아오게 해 주었으면 하오. 어쩌면 누군가 그에 대해 들었거나, 심지어 직접 알았을 수도 있지. 비용은 전부 내가 부담하겠소, 물론. "+npchar.name+", 이것은 메리에게 매우 중요한 일이오, 그리고 우리는 더 이상 의지할 곳이 없소.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Fadey_7_2":
			dialog.text = "그대는 영리하고 통찰력 있는 사람이오, "+pchar.name+". 그래, 그 말은 이미 들었소. 내게 유능하고 아는 이들이 있다는 것도 사실이오. 하지만 솔직히 말해 보시오 — 그들에게 무엇을 시키고 싶은 것이오.";
			link.l1 = "그들을 군도의 여러 식민지로 보내 우리가 찾는 남자에 대해 뭔가 알아오라고 부탁하고 싶소. 어쩌면 누군가는 그의 소문을 들었거나, 심지어 직접 알았을 수도 있지. 물론 비용은 내가 전액 부담하겠소. "+npchar.name+", 이 일은 메리에게 매우 중요하고, 우리는 더 이상 의지할 곳이 없소.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Fadey_8":
			dialog.text = "그렇게 좋은 친구인 너를 내가 거절할 수 있겠어, "+pchar.name+"? 특히나 그대가 이 신성한 일에 기꺼이 돈을 쓸 준비가 되어 있으니 말이오. 그러니 찾고자 하는 자의 이름을 말해 주시오.";
			link.l1 = "이름에 관해서는 확실하지 않지만, 루퍼트 캐스퍼나 조슈아 노스우드라고 불렸던 것 같아.";
			link.l1.go = "WildRose_Fadey_9";
		break;

		case "WildRose_Fadey_9":
			dialog.text = "좋소, 그 자가 당신이 말한 이름으로 다녔다면 우리가 찾아내겠소...";
			link.l1 = "훌륭하군, "+npchar.name+". 당신의 보수에 대해 이야기해 볼까요?";
			link.l1.go = "WildRose_Fadey_10";
		break;

		case "WildRose_Fadey_10":
			dialog.text = "불쾌한 일이지만, 유감스럽게도 필요하군.";
			link.l1 = "그럼 시작하지. 그자가 스페인 놈들이나 네덜란드 놈들 사이로 들어갈 만큼 위험을 감수하진 않을 거야. 녀석은 앤티가에서 문제를 일으키고 떠났으니, 거기서 찾을 필요도 없고, 아마 바베이도스에서도 아닐 거야. 서인도 본토나, 스페인 놈들이 쫓겨난 뒤의 자메이카, 프랑스 식민지, 어쩌면 해적 정착지에 자리 잡았을 수도 있지.";
			link.l1.go = "WildRose_Fadey_11";
		break;
		
				case "WildRose_Fadey_11":
			dialog.text = "솔직히 말할게, 친구야. 내가 바스테르에서 살아온 동안 그 두 이름을 가진 신사는 한 번도 들어본 적 없어. 그러니 여기서 찾을 필요는 없지. 마르티니크와 세인트 크리스토퍼에는 내가 아는 영국 신사들이 있지만, 그 사람도 거기엔 없어.";
			link.l1 = "그렇다면 수색 범위가 상당히 좁아지는군.";
			link.l1.go = "WildRose_Fadey_12";
		break;

		case "WildRose_Fadey_12":
			dialog.text = "토르투가도 반드시 확인해야 하오 — 그리고 같은 자를 라 베가, 푸에르토 프린시페, 포르토프랭스에도 보내겠소. 유능한 부하들을 벨리즈와 블루벨트, 자메이카와 이슬라 테소로에도 파견하겠소.";
			link.l1 = "이 모든 게 나에게 얼마가 들겠소?";
			link.l1.go = "WildRose_Fadey_13";
		break;

		case "WildRose_Fadey_13":
			dialog.text = "이 자들은 박식하고 근면한 사람들이니, 각자에게 백오십 두블룬씩 지불해야 하오. 내가 토르투가와 히스파니올라, 그리고 쿠바에 파견하는 사절에게는 추가 보상이 필요하니 — 금화 오십 닢을 더 주시오. 결국 네 개의 정착지는 하나가 아니지 않소.";
			link.l1 = "그러면 800두블룬이군... 이제 계산을 마무리할까요?";
			link.l1.go = "WildRose_Fadey_14";
		break;

		case "WildRose_Fadey_14":
			dialog.text = "그래, 시간 낭비할 필요 없지. 필요한 금액을 가지고 있나, 이보게?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "물론이지. 자, 받아.";
				link.l1.go = "WildRose_Fadey_14_pay";
			}
			else
			{
				link.l1 = "흠... 지금 전액을 가지고 있진 않소.";
				link.l1.go = "WildRose_Fadey_14_nopay";
			}
		break;

		case "WildRose_Fadey_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "훌륭하오, 나의 친애하는 친구여! 곧바로 내 부하들에게 서면 명령을 보내겠소, 그러면 그들이 곧바로 일을 시작할 것이오. 그쪽으로 향하는 배를 찾아야 하니 시간이 좀 걸릴 것이오. 항해 자체도 바람의 세기에 달려 있으니, 그것은 우리 주님의 뜻에 달린 일이오. 하지만 내 사람들이 한 달 안에는 돌아올 것이라 알고 있소.";
			link.l1 = "그럼 한 달 뒤에 만나겠군, "+npchar.name+". 다시 한 번 감사하오. 정말 큰 도움이 되었소. 그때까지 안녕히!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2");
		break;

		case "WildRose_Fadey_14_nopay":
			dialog.text = "알겠습니다, "+pchar.name+", 금액이 상당하오. 그 돈을 마련하면 내 집에서 기다리겠소.";
			link.l1 = "곧 돌아오겠소.";
			link.l1.go = "exit";
			pchar.questTemp.WildRose_Etap5_Fadey_2 = true;
		break;

		case "WildRose_Fadey_return":
			dialog.text = "그대 일은 기억하고 있네, 친애하는 친구여. 여덟백 두블론을 모아왔겠지?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l21 = "여기 있습니다, Fadey 나리! 약속한 대로 금화입니다.";
				link.l21.go = "WildRose_Fadey_14_pay";
			}
			link.l31 = "아직 필요한 금액을 모으고 있지만, 걱정 마시오 — 오래 지체하지 않을 것이오.";
			link.l31.go = "exit";
		break;

		case "WildRose_Fadey_16":
			dialog.text = "성공했네, 친구여 — 오, 대성공이었지! 내 부하들은 모두 단 한 가지를 가지고 돌아왔네. 내가 벨리즈로 보낸 제롬 소베르니에는 돌아오지 않았지만, 소식을 보내왔어. 자네에게 좋은 소식이지.";
			link.l1 = "그가 너에게 편지를 보냈다고? 우리도 읽어봐도 되겠나?";
			link.l1.go = "WildRose_Fadey_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Fadey_17":
			dialog.text = "물론이지, "+pchar.name+". 네가 읽고 싶어할 것 같아서 특별히 남겨뒀어. 부탁이야, 친구.";
			link.l1 = "감사합니다, 지금 읽어보겠습니다.";
			link.l1.go = "WildRose_Fadey_18";
			AddQuestRecordInfo("WildRose_Records_6", "1");
		break;

		case "WildRose_Fadey_18":
			dialog.text = "오랜만에 자네 얼굴에서 그런 미소를 보네, 좋은 사람이여!";
			link.l1 = "어쩐지, "+npchar.name+"! 우리가 이렇게 오래 기다렸어! 하지만 있잖아, 우리는 성공을 믿었지! 네가 이렇게 중요한 역할을 해줘서 어떻게 감사해야 할지 모르겠어.";
			link.l1.go = "WildRose_Fadey_19";
		break;

		case "WildRose_Fadey_19":
			dialog.text = "아, 그만하게, 용감한 친구! 자네는 내 친구이니, 친구끼리는 서로 도와야 하네. 곧 다시 돌아오게 — 제롬 나리도 금방 회복해서 첫 배에 오를 걸세...";
			link.l1 = "우리가 직접 나서서 일을 좀 더 빠르게 진행하지. 우리가 직접 벨리즈로 가서 당신의 대리인과 이야기하겠소. 다시 한 번 감사하오, "+npchar.name+". 당신이 우리에게 얼마나 큰 도움을 줬는지 상상도 못할 거예요! 다시 만날 때까지!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_5");
		break;
		//<-- Дикая Роза
		
		//--> LoyaltyPack
		case "LoyaltyPack_Fadey_1":
			dialog.text = "내 소중한 친구 알론소 피멘텔이 그대 배에서 일한다는 말인가? 하! 물론이지. 그 친구는 그대 배가 항구에 들어올 때마다 꼭 들러 한잔하더군. 내게 남은 친구가 몇 안 되네,\n "+pchar.name+". 나는 그 하나하나를 소중히 여겨.";
			link.l1 = "알론소가 당신의 전쟁 모험에 대해 놀라운 이야기들을 들려줬어요. 심지어 당신의 탄약띠도 저에게 주었답니다.";
			link.l1.go = "LoyaltyPack_Fadey_2";
			DelLandQuestMark(npchar);
		break;

		case "LoyaltyPack_Fadey_2":
			dialog.text = "그가 가장 놀라운 것들은 자기만 간직했으리라 믿고 있소. 하지만 알론소가 우리 우정을 자네와 나눴으니, 나 역시 자네에게 궁금한 것이 있구려. 자, 보시오!";
			link.l1 = "저게... 갑옷인가?";
			link.l1.go = "LoyaltyPack_Fadey_3";
		break;

		case "LoyaltyPack_Fadey_3":
			dialog.text = "아, 친구여. 이것이 저주받은 전쟁 때 내가 입었던 내 거울 갑옷의 남은 전부라네. 그리고 나중에, 스몰렌스크 근처에서 나는\n"+
			" 그렇다 해도, 이런 상태에서도 정말 훌륭해 보이고, 보호도 더 잘해 주지. 그리고 이제는 나한테 전혀 맞지 않아!";
			link.l1 = "이곳에서도 이국적으로 보이네... 정말 훌륭한 선물이야, 파데이. 고마워.";
			link.l1.go = "LoyaltyPack_Fadey_4";
		break;
		
		case "LoyaltyPack_Fadey_4":
			dialog.text = "자네니까, 친구, 겨우 천 두블룬만 받지.";
			if (PCharDublonsTotal() >= 600)
			{
				if (GetSummonSkillFromName(pchar, SKILL_Commerce) >= 60)
				{
					link.l1 = "정정하게 해 주게, 친애하는 파데이. 천 두블룬이면 갑옷 한 벌 값이지. 하지만 흉갑 하나만이라면?";
					link.l1.go = "LoyaltyPack_Fadey_5";
					Notification_Skill(true, 60, SKILL_COMMERCE);
				}
				else if (PCharDublonsTotal() >= 1000)
				{
					link.l1 = "너랑 알론소가 잘 지내는 것도 당연하지. 여기 네 금화다.";
					link.l1.go = "LoyaltyPack_Fadey_1000";
					Notification_Skill(false, 60, SKILL_COMMERCE);
				}
			}
			link.l2 = "하! 방금은 네 꾀에 넘어갈 뻔했군, 파데이! 아마 다음 기회에나 가능하겠지.";
			link.l2.go = "LoyaltyPack_Fadey_MoneyLater";
		break;
		
		case "LoyaltyPack_Fadey_MoneyLater":
			dialog.text = "물론이지, 서두를 필요 없어. 내 거울 갑옷은 언제나 널 기다릴 테니까.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LoyaltyPack.Fadey = "money";
		break;
		
		case "LoyaltyPack_Fadey_5":
			dialog.text = "오, 눈치가 빠르군! 좋아, 그럼 육백 금화에 넘기지.";
			link.l1 = "너랑 알론소가 잘 지내는 것도 당연하지. 자, 네 금화다.";
			link.l1.go = "LoyaltyPack_Fadey_600";
		break;
		
		case "LoyaltyPack_Fadey_1000":
			dialog.text = "좋은 거래로군. 고맙소, 내 거울 갑옷을 믿을 만한 이에게 맡기겠소. 그리고 알론소를 잘 부탁하오, 선장.";
			link.l1 = "여기서 누가 누구를 돌보고 있는 거지...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(1000);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_600":
			dialog.text = "좋은 거래로군. 고맙소, 그리고 내 거울 갑옷을 믿을 만한 손에 맡기겠소. 그리고 알론소도 잘 부탁하오, 선장.";
			link.l1 = "여기서 누가 누구를 돌보고 있는 거지...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(600);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_end":
			DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_Fadey_DlgExit");
		break;
		//<-- LoyaltyPack

		case "guardoftruth":
			dialog.text = "그래, 네가 일 때문에 왔다는 걸 누가 의심하겠어, 친구! 안타깝게도 지금 줄 보드카가 없어, 내가 다 마셔버렸거든. 자, 이번엔 무슨 곤경에 빠진 거야.";
			link.l1 = "어떤 사략선장이 자신의 죄를 용서받기 위해 금으로 된 청금석 목걸이 십자가를 지역 교구에 바쳤소. 아주 희귀하고 값진 물건이오. 문제는 이 십자가가 다른 교구에서 도난당한 것이라는 점이오.\n게다가 강도질 중에 신부 한 명이 살해당했소.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "오, 흠 없는 성모 마리아여! 그럴 수가!";
			link.l1 = "그래. 나는 약탈당한 신도들을 대표해서 십자가를 원래 주인에게 돌려주려고 하고 있네.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "고귀한 행동이군, 그리고 참으로 경건하지. 전능하신 분의 환심을 사려는 건가?";
			link.l1 = "하지만 그 신부는 내가 아무리 말해도 돌려주기를 거부하네. 이해가 안 돼. 어떻게 도둑맞은 십자가를, 그것도 죄 없는 이의 피로 물든 것을, 아무렇지 않게 하느님의 집에 둘 수 있지? 그건 신성모독이야!\n";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "음, 사실 모든 축성된 성배에는 무고한 그리스도의 피가 담겨 있지... 하지만 딴소리였군. 내 도움이 필요한 거요?";
			link.l1 = "그렇소! 당신은 바스테르에서 꽤 영향력이 있지. 존경도 받고 있으니, 아마 신부도 당신의 충고를 귀담아들을 것이오.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", 우리 신부님께 이 도난당한 십자가의 내막을 정확히 말씀드렸소?";
			link.l1 = "물론이지! 나는 그의 신앙심에도, 그리스도인으로서의 연대감에도, 젠장할 양심에도 하느님을 걸고 호소했지만, 그는 귀를 닫아버렸어.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "흠... 그를 설득하려고 다른 방법도 써 봤소?";
			link.l1 = "그 사람을 매수하라는 거야? 나는 신부를 매수하지 않아. 만약 그가 은행가나 상인, 아니면 심지어 총독이라면 그런 식으로 문제를 해결하려고 했겠지만, 신부는 아니야!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "나의 순진한 친구여, 만약 신부의 귀가 정말로 양심의 외침에 닫혀 있다면, 그의 손은 분명 금에는 열려 있을 것이오... 아니면 반대일 수도 있겠지. 내가 도와주겠소; 이렇게 더럽혀진 보물을 여기에 두는 건 앞으로 더 큰 화를 부를 것 같으니 말이오. 하지만, 약간의 비용이 들 것이오.";
			link.l1 ="왜 놀랍지도 않지? 이번엔 얼마야?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "내일 들르시오, "+pchar.name+", 아직 값을 말씀드릴 수는 없소. 하지만 그 도난당한 십자가는 반드시 돌려드리겠소, 안심하시오.";
			link.l1 = "좋아, 파데이, 더 이상 귀찮게 하지 않겠네. 내일 보세!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "약속대로 십자가를 가져왔소. 세부 사항은... 아, 잊으시오... 우리 소중한 구세주의 흘리신 피로 모든 허물은 용서받았으니";
			link.l1 = "내가 너에게 얼마나 빚졌지?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "이백오십 두블룬. 내 경비를 충당하려는 거고, 물론 내 정당한 도움에 대해 약간의 보너스도 고맙게 받겠소...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "알겠소, Fadey 나리. 여기 금이 있소.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "내 선실에서 금을 가져와야겠어. 금방 돌아올게.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "좋아. 여기 훔친 십자가가 있다.";
			link.l1 = "고맙네, 파데이. 자네가 내게 얼마나 큰 도움을 줬는지 상상도 못할 걸세!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "나는 언제나 친절하고, 더 중요한 건 후한 친구를 돕는 게 기쁘지. 자주 들르시게. 본국에서 보드카가 도착하면 한잔할 수도 있겠군.";
			link.l1 = "기꺼이!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "오, 아직 바다에 잡아먹히진 않았군! 자, 말해 보시오. 이번엔 무슨 불운이 그대가 내 문을 두드리게 만들었소?";
			link.l1 = "이걸 불운이라고 해야 할지 잘 모르겠지만, 어쨌든 나는 여기 있어. 파데이, 우리가 처음 만난 날 네가 나에게 희귀한 단검, 족장의 발톱을 줬지. 이제 와서 알게 됐는데, 그게 원래 아치볼드 칼훈이라는 남자의 것이었더군. 제발, 이 사람에 대해 아는 걸 말해줘.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "당신에게는 아무것도 숨길 수 없군, "+pchar.name+". 너도 네 형처럼 모든 걸 꿰뚫어보는구나. 그래, 이 단검은 칼훈이라는 놈한테 주사위 내기로 땄지. 그가 누구냐고? 나도 전혀 몰라. 우연히 선술집에서 만났고, 이런저런 얘기를 나누다가 술도 몇 잔 마셨지. 그러다 자기 과거의 죄에 대해 털어놓기 시작하더군...\n";
			link.l1 = "너 뭐야, 그의 고해신부라도 되나? 무슨 죄를 말하는 거지?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "아치볼드는 자신 때문에 종교재판소에서 고문당해 죽은 남자와, 그가 죽인 다른 무고한 영혼들의 기억에 시달렸소. 그는 계속 자신을 유다라고 부르며, 신이 자신의 죄를 벌하고 있고 종교재판소가 자신을 쫓고 있다고 했지. 스페인 종교재판관 빈센토가 직접 자신을 죽이려 하고, 용병들을 카리브 해 전역에 보내 쫓고 있다고도 했소. 그러다 술에 취해 결국 우리 둘은 이 낡은 단검을 걸고 내기를 했지.";
			link.l1 = "그게 전부요? 다시는 그를 본 적 없소?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "당연히 아니지, 그는 이제 죽었어. 한 무리의 비참한 해적들이 그의 플루이트선을 데이비 존스의 금고로 보내고, 선원 전부를 미클란테쿠틀리에게 보냈지. 사실 소문에 따르면, 그들은 해적 복장을 한 전문가들에게 습격당했다더군... 종교재판소의 첩자들이지. 빈첸토 신부는 항상 목표를 잡는다더라.";
			link.l1 = "아치볼드 칼훈은 살아 있어. 얼마 전에 그를 봤지, 어떤 윌리엄 패터슨이라는 자와 함께였어. 칼훈은 그 자의 일등항해사로 일하고 있더군.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "오호, 이거 뜻밖인데! 아치볼드는 최소한 패터슨 선장 밑에서 한숨 돌릴 수 있겠군. 괜찮은 사람들과 함께 있네. 스페인 놈들은 패터슨을 역병처럼 두려워하지. 패터슨의 보호 아래 있는 동안은 아치볼드에게 감히 음모를 꾸미지 못할 거야.";
			link.l1 = "패터슨을 아나?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "윌리엄 패터슨을 모르는 사람이 어디 있겠소!? 그도 자네처럼 카리브에 새로 온 인물이오. 그리고 자네처럼 이미 명성을 쌓았지. 패터슨 나리는 폭스 대령과 가장 가까운 친구이며, 카리브의 모든 영국 식민지의 총독인 윈저 경과도 막역한 사이요. 자주 자메이카 포트 로열에 있는 총독 궁전을 방문하오.";
			link.l1 = "알겠어. 정보 고마워, 파데이!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "아, 별말을 다 하네, 친구. 언제 한 번 놀러 와! 사냥 잘 하라고!";
			link.l1 = "틀림없지!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "한번 보자, "+pchar.name+"... 그래! 이거야, 바로 그놈이야! 잘했다, 내 아들, 오늘 하루가 즐겁구나! 어디서 찾았느냐?";
			link.l1 = "상관없어. 중요한 건 그것이 다시 네게 돌아왔다는 거야.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "철저히 조사해 주면 충분한 보수를 주겠소. 삼백 금화 두블론이면 수고에 대한 보상으로 충분할 것이오...";
			link.l1 = "전에 내게서 쥐어짠 두블룬으로 나에게 지불하는 건가? 뭐, 물론 거절하진 않지. 여기 네 샴쉬르다.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "고마워, 친구! 검과 너의 냉소적인 말에 감사하지. 네 나이보다 훨씬 현명하구나, "+pchar.name+", 하지만 인간 사이의 우정은 금보다 더 소중하지. 금 이야기가 나와서 말인데, 네 몫을 전부 주겠네. 자, 이 두블룬을 받아라.";
			link.l1 = "감사합니다.";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "그리고 우정의 인연, 특히 그대와 나 사이의 인연을 말하자면, "+pchar.name+". 당신이 매우 흥미로워할 만한 것이 있소.";
			link.l1 = "짐작컨대, 또 보드카인가?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "하! 보드카도 좋지만, 우리 나라가 그것만으로 유명한 건 아니지. 러시아만이 생산하는 특별한 재료가 있어. 나는 고향의 연락책을 통해 이 재료를 여기로 들여와서 거래하지. 모든 선장이 탐내는 물건이야, 어떤 배든 성능을 높여주거든. 내가 말하는 건 삼줄이야\n습기와 바닷물에도 끄떡없는 밧줄이지. 장비용으론 최고라더군\n매달 레발에서 일정량을 받아. 보통 매달 중순쯤이면 내 창고에 몇백 타래씩 쌓여 있지. 그러니, "+pchar.name+", 나는 당신에게 밧줄 50타 한 묶음을 팔려고 하오. 한 타에 두블론 열 개요\n조건은 두 가지뿐이오. 첫째, 매달 20일까지 밧줄을 내가 보관하겠소. 둘째, 전량 일괄 구매만 가능하오. 50타에 500두블론이오. 비밀로 말하자면, "+pchar.name+", 어떤 장소에서는 그 밧줄을 훨씬 비싼 값에 되팔 수 있다고들 하더군, 하지만 내가 뭘 알겠나!\n나는 지금 내 사업이 충분히 만족스러워서 굳이 직접 되팔이를 찾을 필요는 없어. 만약 좋은 상인을 찾는다면, 꽤 짭짤한 이익을 남길 수 있을 거야.";
			link.l1 = "알겠어. 정말 좋은 제안이군, 파데이! 네가 준 기회를 잘 활용해야겠어. 그러니까, 매달 이십 일에 오백 두블룬에 오십 개씩 맞지?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "그래. 네가 산 물건을 가져가게. 하지만, 잠깐만, 잠깐만, 자네! 자네가 진심으로 선의에서 내게 돌려준 이 샴시르 외에도 두 자루가 더 있었네. 제발, 부탁하네. 혹시라도 그 두 자루를 찾게 되면 내게 다시 가져다주게. 그러면 정당한 값보다 더 후하게 보상하겠네.";
			link.l1 = "틀림없이, 파데이. 내가 그들을 찾으면 데려오겠네.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "좋은 소식이 있소. 페르시아 샴시르 한 자루를 또 구했소.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "오, 내 좋은 친구여! 네가 내 눈물을 닦아 주었구나! 어디 좀 보자... 아! 이거야, 내 소중한 샴시르! 자, 약속대로 이것에 대한 보상으로 삼백 두블룬을 주겠네.";
			link.l1 = "스파시바!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "저의 감사와 더불어 소박하지만 매우 유용한 선물을 받아주십시오. 저에게는 필요 없지만, 당신이나 배의 목수가 분명히 요긴하게 쓸 수 있을 겁니다\n여기, 이 멋진 반지를 보십시오! 이제 당신의 것입니다. 하지만 이건 평범한 반지가 아니라 마법이 깃든 반지입니다. 목공과 선박 수리에 도움이 되지요. 많은 장인들이 갖고 싶어 했지만, 저는 특별한 때를 위해 아껴두었습니다. 받아주시오, 친구여. 당신의 짐이 조금이나마 덜어지길 바랍니다!";
			link.l1 = "정말 흥미로운 유물들을 많이 가지고 있군. 고마워, 파데이!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "내가 잃어버린 컬렉션 중에 남은 샴시르는 단 하나뿐이야. 너만 믿고 있다, "+pchar.name+", 그리고 당신의 운에도 달려 있소. 만약 그것을 찾게 되면, 주저하지 말고 곧장 내게 돌아오시오.";
			link.l1 = "틀림없이! 곧 보자...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "내가 왜 서둘러야 하지? 검은 내 곁에 있는데.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "아, 당신에게 도움을 청하길 정말 다행이야, "+pchar.name+". 자네는 기적의 사나이구나, 친구! 그걸 내게 보여줘... 오호! 이, 이게 바로 그녀야. 내 사랑! 크라사비차! 고맙네, 훌륭한 친구여, 내가 자네에게 경의를 표하네! 자, 여기 돈이네. 네백 두블론, 한 푼도 깎지 않겠네! 인색하게 굴지 않을 테니.";
			link.l1 = "고맙네, Fadey. 도울 수 있어 기쁘군.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "내 샴시르 컬렉션이 다시 모두 모였네! 이제는 아무도 내 것을 훔칠 엄두도 못 낼 것이야, 내가 확실히 지킬 테니! 자네에게 아주 특별한 보상이 있네, 좋은 사람이여. 2주 후면 상인이 유럽에서 훌륭한 펜싱 갑옷 한 벌을 가져올 걸세. 귀족이 주문한 것으로, 아주 독특한 갑옷이지\n그러니, 원한다면 단 700골드 두블룬에 살 수 있네. 귀족에게는 운송 중에 분실되었다고 말해주지.";
			link.l1 = "이 갑옷이 뭐가 그렇게 좋은데?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "아주 편안하고 튼튼하지만, 철제 흉갑만큼 성능도 좋아요. 게다가 멋지게 생겼죠! 몇 주 후에 다시 와서 한번 보세요. 하지만 한 달 이상 걸리면 원래 손님에게 팔아버릴 거예요.";
			link.l1 = "좋아. 2주 후에 네 집에 들르지.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "네, 이미 전달되었고 당신을 기다리고 있습니다. 돈은 가져왔습니까?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "그래. 여기 700두블론이네.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "젠장. 돈을 배에 두고 왔네. 금방 가져올게!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "그래, 자네 참 좋은 사람이군! 자, 받아. 이 등나무 갑옷은 분명 자네에게 큰 도움이 될 거라 장담하네. 이런 건 카리브 해 어디에도 없지!";
			link.l1 = "그래, 보이네. 고마워! 얼른 입어보고 싶어...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "왜 기다려야 하지? 어서 해 봐. 얼마나 잘 맞는지 보자.";
			link.l1 = "알겠습니다. 나중에 봅시다, Fadey 나리!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "들어오시오, 친애하는 친구여. 상품이 준비되어 있소. 이백오십 개에 이천백이십오 두블룬이오.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "모두 약속한 대로야. 돈 가져가.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "내 선실에서 동전만 좀 가져올게.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "들어오시오, 내 친애하는 친구여. 물건은 이미 준비되어 있소. 오십 개에 오백 두블룬이오.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "모두 약속한 대로야. 돈 가져가.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "내 선실에서 동전만 좀 가져올게.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "파데이, 우리 거래 규모를 좀 더 늘릴 수 있을까? 자네한테서 다섯 배나 더 많은 물건을 살 준비가 되어 있네! 이게 우리 둘 다에게 이득이 될 거라 생각하네. 어떻게 생각하나?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "파데이, 돈 가져왔어! 약속대로 금화 3,000 더블룬이야.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "당신과 거래해서 즐거웠소, "+pchar.name+". 내 부하들에게 밧줄을 당신 배로 가져오라고 명령하겠소.";
			link.l1 = "감사합니다!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "아직 밧줄이 더 필요하면 한 달 후에 다시 오시오.";
			link.l1 = "좋아, 파데이. 나중에 보자!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "무엇을 도와줄까, 내 친애하는 친구여?";
				link.l1 = "그대는 영향력 있는 인물이오, 파데이. 총독의 친구이기도 하고, 소문에 따르면 궁정에도 연줄이 있다지. 내가 법에 걸려 곤란해지면, 당국에 탄원 좀 해줄 수 있겠소?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "무엇을 도와줄까, 친구야?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "나는 영국 당국과 문제가 있소.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "프랑스 당국과 문제가 생겼어.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "밀수업자들 때문에 심각한 문제가 있소.";
				Link.l5.go = "contraband";
            }
			link.l9 = "미안하지만, 내가 알아서 할 수 있을 것 같아.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "오호호, 이보게, 누가 그런 말을 했나? 세상 사람들 다 거짓말하지. 하지만 자네가 미셸의 동생이자 내 좋은 친구이니, 내가 좀 도와줄 수 있을지도 모르지. 내가 힘써줄 수 있는 건 영국과 프랑스 당국뿐이네, 내 인맥에도 한계가 있으니까. 나는 스페인이나 네덜란드와는 거래하지 않아\n또한 내 영향력으로 구해줄 수 있는 건 사소한 위반 정도뿐이라는 점도 경고하네. 경미한 잘못을 저질렀을 때 그들의 태도를 다시 생각해보게 하거나, 약간의 분노를 누그러뜨릴 수는 있지. 하지만 자네가 전쟁이라도 일으켜 놓고 내가 다 해결해주길 바란다면, 그건 무리야!\n게다가 한 번에 한 나라만 달랠 수 있어. 프랑스 아니면 영국, 둘 다는 안 되네. 내가 몸이 둘이 아닌 이상 동시에 두 일을 할 순 없지. 물론 뇌물을 쓰려면 돈도 필요할 거야. 내 조건이 괜찮다고 생각되면 언제든 찾아와 도움을 청하게.";
			link.l1 = "고맙네, 파데이. 명심하겠네.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.FadeyNation));
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", false);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "물론이지. 자네의 모험담, 아니면 사고담쯤은 분명히 들었네. 자네의 작은 문제쯤은 내가 처리할 수 있지. 적당한 금화만 있으면 못 고칠 일이 없으니. " + sTemp + " 그리고 내가 널 솥에서 꺼내줄게.";
				if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
				{
					link.l1 = "좋아! 여기 금이야.";
					link.l1.go = "agree";
				}
				link.l2 = "그럼 내가 가서 동전을 가져올 딱 좋은 때군.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "물론이지. 자네의 모험담, 아니면 사고뭉치 짓도 익히 들었네. 자네의 작은 문제쯤이야 내가 해결해 줄 수 있지. 적당한 금화만 있으면 못 고칠 일이 없거든. " + sTemp + " 그리고 내가 널 솥에서 꺼내 줄게.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "좋아! 여기 금화다.";
						link.l1.go = "agree";
					}
					link.l2 = "그럼 내가 가서 동전들을 가져올 딱 좋은 때군.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "그래, 자네 꽤나 곤란한 처지에 있군! 이 상황을 완전히 해결해 줄 수는 없네. 하지만 곧 자네의 죄 많은 머리 위로 떨어질 천둥벌거숭이 같은 일격은 좀 누그러뜨려 줄 수 있지. 그리고 나중에, 언제든 돈과 의지만 있다면 다시 뇌물을 건넬 수도 있네. " + sTemp + " 그러면 내가 당신의 문제를 해결해 줄 수 있소.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "해적 사냥꾼들이 나를 쫓아다니는 것도 이제 지겹다. 자, 금화다.";
						link.l1.go = "agree";
					}
					link.l2 = "그럼 내가 가서 동전을 가져올 딱 좋은 때군.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "좋소, 열흘에서 보름쯤 시간만 주시오. 그동안 내가 이것저것 준비하고 처리하겠소. 대략 이 주일이면 모두 끝날 것이오. ";
			link.l1 = "고마워, 파데이! 기다리고 있을게...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.FadeyNation));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", true);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			dialog.Text = "왜 그들을 괜히 화나게 했소, 내 좋은 사람? 밀수꾼들은 이 동네에서 제일 나쁜 놈들도 아니고, 잘만 하면 이익도 챙길 수 있소. 좋아, 내가 도와주겠소. 내가 그 녀석들 비위를 맞추는 법을 아니까... 그럼 " + sTemp + ", 흥정은 없어.";
			if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
			{
				Link.l1 = "좋아, 파데이, 동의하네. 금을 가져가게.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "지금은 그만한 금화가 없어. 나중에 다시 올게!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "좋아, 내가 싸움을 잘 수습할 테니 걱정 마. 예전처럼 다시 너랑 거래할 거야.";
			Link.l1 = "감사합니다!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "호호, 장사가 잘 되고 식욕도 커지는구먼! 맞아, 우리 물건은 훌륭하고 값도 그리 비싸지 않아. 하지만 말이지, 투자도 필요하다는 걸 명심하게! 이런 사업은 모든 걸 완벽하게 하려면 진지한 접근이 필요하네.";
			link.l1 = "내가 예비로 몇백 두블론쯤은 챙겨두지 않고 이런 제안을 하러 너한테 오겠어?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "네 상자에 동전이 들어 있다는 건 알아, 그리고 몇 개가 아니라, 오십 개쯤은 거뜬히 들어가겠지! 하지만 우리 거래는 평범하지 않아 – 단순히 물건을 옮기는 게 아니라, 음... 은밀한 방법을 찾아야 해. 이 정도 규모라면 단순히 돈을 내는 게 아니라, 제대로 수익을 내려면 크게 투자해야 해! 그리고 네 돈이 허공으로 사라지지 않게 보장해야지. 만약 삼천 금 더블룬을 기꺼이 내놓을 준비가 됐다면, 내 말을 믿어도 좋아. 좋은 친구로서 모든 걸 제대로 처리해 줄 테니, 가격에서도 손해 보게 하진 않을 거야.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "삼천 두블론! 음, 인정해야겠군, 이렇게 후한 제안은 가장 번성한 상인들에게조차, 가장 기상천외한 이야기 속에서도 좀처럼 들을 수 없는 일이오! 이렇게 아낌없이 투자하려는 자는 드물지. 하지만 다행히도, 나는 그들 중 한 사람이오. 여기 돈이 있소, 파데이 나리.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "삼천 금화 두블룬이라니! 그런 큰돈은 준비가 안 됐네, 파데이. 유감이야. 나중에 다시 올게.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "삼천이라고? 흠... 사실 그런 금액은 네 야망에 경의를 표하게 만드는군. 하지만 솔직히 말해, 내겐 맞지 않는 일이야.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "이런 반전이군! 제안을 들고 오더니, 곧바로 물러서다니! 실망스럽다는 건 인정하겠소, 하지만 이 일로 우리의 우정을 망치진 않을 것이오. 예전처럼 하도록 합시다. 이전 약속은 그대로 유지하겠소 - 매달 20일에 코일 50개, 개당 10더블룬씩이오.";
			link.l1 = "내 말을 이해해줘서 다행이야, 파데이. 마음을 바꾸고 싶지만, 그런 지출은 내 능력을 벗어나네. 유감스럽게도, 이 일에 있어 내 수단은 한정되어 있네.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "그래, 그게 자네의 결정이라면 더 이상 할 말은 없군. 우리의 우정에는 아무 영향도 없을 걸세. 꼭 들르게나, "+GetSexPhrase("좋은 나리","고운 아가씨")+".";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "이제야 말이 통하는군! 쓸데없는 말은 안 하고 행동으로 보여주는 사람이군. 당신 같은 장사꾼에게는 언제나 할인이 있지! 앞으로 모든 선적에 15퍼센트 할인이다! 우리 거래 조건은 이렇다네: 매달 삼백오십 코일의 삼베 밧줄을 준비해두겠네. 예전처럼 20일에 와서 가져가면 되네. 전부 합쳐 2125두블룬만 내게. 잔돈은 필요 없네.";
			link.l1 = "완벽하군, 파데이! 자네와 거래하는 건 정말 쉬워. 분명히 성공이 우리를 기다리고 있을 거야. 다음에 또 보자!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}