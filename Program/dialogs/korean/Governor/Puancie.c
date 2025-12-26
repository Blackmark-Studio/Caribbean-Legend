// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "안녕하시오, "+pchar.name+". 들어오시오; 이미 보고를 받았소.";
				link.l1 = "알려드렸다고요? 무슨 착오가 있는 것 같소, 각하. 저는 임무를 성공적으로 완수했다는 보고를 드리러 왔는데, 기분이 그리 좋아 보이지 않으시군요.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "다시 만나 반갑소, "+pchar.name+". 자네의 업적에 대해 보고를 받았네. 그리고 무엇보다, 임무를 성공적으로 완수했구려! 자네는 훌륭한 모습을 보여주었고, 내가 자네를 믿은 것이 틀리지 않았음을 기쁘게 생각하네.";
				link.l1 = "이제 제 형을 석방하라는 서면 명령을 받을 수 있겠습니까?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "다시 만나 반갑소, "+pchar.name+". 자네의 업적에 대해 들었고, 무엇보다 임무를 완수했구려! 다만 정면 돌파보다 더 영리한 방책을 기대했었는데, 그 점은 아쉽군. 죽은 프랑스 병사들도 안타깝고.\n허나 전쟁이란 늘 희생이 따르는 법이지. 자네는 맡은 바를 다했으니, 내가 자네를 믿은 것이 옳았음을 기쁘게 생각하오.";
				link.l1 = "지금 제 형을 석방하라는 서면 명령을 받을 수 있겠습니까?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "만나서 반갑소, 샤를. 우선, 생피에르 식민지를 스페인 침입자들로부터 훌륭하게 지켜낸 복잡한 임무를 성공적으로 완수한 것을 축하하오. 정말 훌륭한 일이었소, 내 친구!";
					link.l1 = "감사합니다, 슈발리에 나리.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "만나서 반갑소, 샤를. 우선, 생피에르 식민지를 스페인 침입자들로부터 성공적으로 지켜낸 복잡한 임무를 완수한 것을 축하하오. 훌륭한 일이었소, 친구! 해군과 다시 협력할 기회를 주겠소. 프랑스에는 자네 같은 장교가 절실히 필요하오. 이번에는 좀 더 현명하게 행동해 주길 바라오... 특허장을 받으시오, 샤를 드 모르 선장!";
					link.l1 = "감사합니다, 푸앙시 나리. 조국을 도울 수 있어 기쁘고, 앞으로도 계속 충성하고 싶습니다!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "샤를, 너는 나를 실망시키는구나. 너의 경솔한 행동으로 인해 왕립 해군의 특허와 계급을 모두 잃었네. 더 이상 협력의 여지는 없소. 물러가도록.";
					link.l1 = "흠...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "반갑소, 샤를. 보고하시오!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "일은 끝났고, 산호세 식민지에서 몸값도 받았소. 하지만 나쁜 소식이 있소: 요새와의 전투에서 '에클라탕'이 침몰했소. 내가 선장에게 조심하라고 경고했지만, 내 말을 듣지 않았고, 그리고...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "일을 끝냈소, 산호세 식민지에서 몸값을 받았소.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "나리, 오늘부터는 반드시 격식에 맞는 복장으로 내 집무실에 들어오시오!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "남작님, 선장님! 뵙게 되어 반갑습니다!";
					link.l1 = "임무를 완료했습니다, 푸앙시 나리.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", 선장. 무슨 소식을 가져왔소?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "스페인 놈들이 포르토프랭스 공격을 계획했었소. 에스파뇰라 서쪽 끝에서 강력한 적 함대를 마주쳤지. 완전히 격파했소. 하지만 '에클라탕'은 침몰했네.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "스페인 놈들이 포르토프랭스 공격을 계획했었소. 에스파뇰라 서쪽 끝에서 강력한 적 함대를 마주쳤지. 완전히 격파했소.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", 샤를. 스타이베산트 나리는 잘 지내는가?";
					link.l1 = "모든 것이 잘 되었습니다, 푸앙시 나리. 전달은 성공적으로 마쳤고, 여기 당신의 편지에 대한 답장이 있습니다.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "샤를 나리, 남작... 벌써 돌아왔는가?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "네 인상, 샤를, 마음에 들지 않는군. 스타이베산트가 뭐라고 했는가? 보고하라!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "말 그대로 그는 이렇게 말했소. '슈발리에에게 전하시오. 이제 그는 신트마르턴을 더 이상 관할하지 않는다. 그만하면 됐다. 그리고 본국의 시찰에 관해서는, 알아서 대책을 세우라고 하시오. 드 푸앵시가 모든 걸 뒤집는 건 결코 어려운 일이 아니었으니까.' 이 말을 전한 뒤, 마인헤르는 나를 관저에서 쫓아냈소. 우리의 협상은 그렇게 끝났소.";
					else link.l1 = "글쎄, 그가 이렇게 말했소. '네 주군이 요즘 신트마르턴에서 지나치게 탐욕을 부리니, 이제 그 끝없는 욕망을 좀 누그러뜨릴 때가 되었군.' 그 뒤로 그는 나를 체포하려 했소. 나는 칼을 들고 배까지 싸우며 나와야 했지. 네덜란드식 외교란 게 이 정도로군.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "선장님, 기다리고 있었습니다. 현재 상황을 남작 나리께 설명드렸고, 제 결정을 전적으로 지지하셨습니다. 네덜란드 놈들은 그 오만함에 반드시 대가를 치르게 될 것입니다.";
					link.l1 = "전쟁이오, 그럼?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "그러면, 친구여, 자네가 동인도 상선을 화물과 함께 포획했다는 것을 보았네. 훌륭하군!";
						link.l1 = "배를 그대에게 맡기겠소, 항만 관리들에게 명령을 내리시오, 푸앙시 나리.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "질문이 있소, Charles?";
						link.l1 = "지금은 아닙니다, 나리. 그럼 이만 가보겠습니다...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "마침내 도착했군, 선장! 세인트 크리스토퍼에 비상이 있소!";
					link.l1 = "적 함대인가?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "우리의 커리어 루거를 맡을 준비가 되었소?";
					link.l1 = "그렇소.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "드 모르 선장, 도일리 나리! 뵙게 되어 반갑소! 우리 식민지를 탐낸 스페인-네덜란드 악당들에게 본때를 보여주던 모습을 온 도시가 지켜봤소!";
					link.l1 = "제 의무였을 뿐입니다, 푸앵시 나리.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. 시작하세나?";
					link.l1 = "물론이지요, 푸앙시 나리. 그래서 제가 여기 온 것입니다.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "프랑스 왕립 해군의 부제독을 내 집무실에 맞이하게 되어 기쁘오! 그래, 친구여, 자네가 잘못 들은 게 아니네. 내가 직접 자네 임명 명령서에 서명했지. 공식적으로는 프랑스에서 최종 승인을 받아야 하지만, 그건 반드시 이루어질 것이니 걱정 말게. 축하하네!";
					link.l1 = "나는 내 조국을 위해 봉사하오!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "will be ready soon and"; // в зависимости от времени сколько добирался
					else sTemp = "is ready and";
					dialog.text = "노력한 일에서 성과를 거두었소? 도일리 대령은 만족했는가?";
					link.l1 = "모든 일이 완벽하게 진행되었습니다, 푸앙시 나리. 스토이베산트의 호송대는 포획되었고, 모든 노예들은 자메이카로 옮겨졌으며, 대령의 전대는\n "+sTemp+" 퀴라소로 가는 길에.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "승자들에게 영광을! 축하하네, 축하하네, 내 친구! 자네는 정말 늘 나를 놀라게 하는군.";
					link.l1 = "감사합니다, 슈발리에 나리. 스토이베상트는 처벌을 받았고 배상금 지급을 준비 중이며, 평화가 회복되었고 생마르탱은 이제 오직 프랑스의 소유가 되었소.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "그래, 친구여, 다시 보게 되어 반갑소. 잘 쉬었는가?";
					link.l1 = "예, 슈발리에 나리. 정말 필요한 휴식이었습니다... 민감한 일에 대해 말씀하셨지요?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "친구여, 자네는 마법사인가! 정말 대단한 일을 해냈군! 이제 우리 남작께서 더 이상 이곳에 무역 회사를 세우려 하지 않으신다네.";
					link.l1 = "지금 그가 바라는 것은 오직 파리로 돌아가는 것뿐이오.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "샤를, 자네 남작 소식 들었나? 해적들에게 잡혀갔다네...";
					link.l1 = "예, 슈발리에 나리. 유감스럽게도 남작은 죽었습니다. 그것만은 확실히 알고 있습니다.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "샤를, 진척은 어떠한가? 남작이 자네 배에 올랐다는 소식을 들었네...";
					link.l1 = "예, 슈발리에 나리. 그는 배에 있었고, 제가 돌보고 있었으나... 열병으로 죽었습니다.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "샤를, 진척은 어떠한가? 남작이 자네 배에 올랐다는 말을 들었네...";
					link.l1 = "예, 슈발리에 나리. 그는 배에 있었고, 제가 돌보고 있었으나... 전투 중에 죽었습니다.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "친구여, 자네는 마법사임이 틀림없구려! 정말 대단한 일을 해냈구만! 이제 우리 남작께서 이곳에 무역 회사를 세우려는 생각을 접으셨네.";
					link.l1 = "아마 지금쯤 파리로 향하고 있을 거요.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "샤를, 궁금한 점이 있소?";
				link.l1 = "지금은 아닙니다, 나리. 그럼 이만 가보겠습니다...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "무엇을 원하시오, 나리?";
			link.l1 = "별일 아니오, 그냥 예의상 들른 것뿐이오. 이제 가보겠소...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "안녕하시오, Charles. 내 소개를 하겠소: 나는 Philippe de Poincy요, 그리고 나는...";
			link.l1 = "도대체 왜 나를 감옥에 가둔 것이오? 이게 말이 되오? 나는 프랑스 귀족이오, 그리고...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "좋은... 오후입니까? 농담이군요, 나리. 어떻게 내가 누군지 아십니까?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "젊은이, 내 말 끊지 말게! 자네는 지금 카리브 제도 프랑스 식민지의 총독과 이야기하고 있네! 자네의 무례한 태도는 자네가 내 앞에 누가 서 있는지 몰랐기 때문에 이번 한 번만 용서하겠네. 하지만 앞으로는 좀 더 신중하게 행동하길 권하네.";
			link.l1 = "흠... 죄송하옵니다, 나리.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "내 말 잘 들으시오, 젊은이. 그리고 내 말 끊지 마시오! 지금 그대는 카리브 제도에 있는 프랑스 식민지의 총독과 이야기하고 있소! 그대가 누구에게 말하고 있는지 몰랐던 무지함을 감안하여 이번만은 그대의 무례한 태도를 용서하겠소. 하지만 앞으로는 언행을 삼가길 권하오.";
			link.l1 = "흠... 용서해 주십시오, 각하.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "더 좋아졌군. 이제 네가 아까 했던 질문에 대해 말하자면 – 너는 스페인 첩자로 오해받아 신분이 확인될 때까지 구금되었던 것이오. 요즘 저주할 카스티야 놈들이 더 활발해져서, 나는 모든 수상한 자들을 체포하라고 명령했지. 하지만 이제 우리는 네가 누구인지 알고 있소 – 너는 진정 미셸 드 몽페르의 동생, 샤를 드 모르임이 분명하오. 그래서 내가 직접 여기까지 내려와 너를 풀어주러 온 것이오. 그런데 네가 어린아이처럼 내게 소리를 지르고 있구나!";
			link.l1 = "다시 한 번 실례합니다, 각하. 이제 떠나도 되겠습니까?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "그래, 맞네. 하지만 하사관이 자네 감방을 열기 전에 따로 이야기하고 싶군. 자네 형이 몰타 기사단에서 가장 훌륭한 전사 중 한 명인데, 체포되어 감시를 받고 있다는 사실을 알고 있나?";
			link.l1 = "나는 내 형제가 곤경에 처해 있고 도움이 필요하다는 것만 알았소. 그래서 파리에서 여기까지 온 것이오.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "그 말을 들으니 기쁘구나. 알아두게, 몽페르 나리는 심각한 곤경에 처해 있네. 나는 그가 권한 남용, 재산 횡령, 위증을 저질렀다고 의심할 만한 충분한 이유가 있네. 하지만 자네가 그를 도울 수 있지.";
			link.l1 = "나리, 더 말씀해 주시겠습니까? 이해가 되지 않습니다. 미셸은 기사단의 자랑이었고...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "나도 그렇게 생각했소. 우리 모두 그랬지! 하지만 그의 최근 행동 때문에... 기사단에 대한 충성심이 의심스러워졌고, 그래서 그를 체포했소. 자세한 내용은 미셸이 직접 말해줄 것이오. 그가 어떻게 자네가 이 누명을 벗고 불명예를 피할 수 있도록 도울 수 있는지 설명해줄 것이오.";
			link.l1 = "지금 내 형은 어디에 있소? 감옥에 있다고 하셨지만, 나는 그를 본 적이 없는데...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "내가 감금했다고 했던가, 젊은이? 듣고 있기는 한가?! 나는 그가 체포되어 있다고 했소! 그건 감금과는 다르오. 미셸 드 몽페르는 몰타 기사단 소유의 생피에르 지하 기지에 연금되어 있소.\n나는 그 기지에 아무런 제한 없이 출입할 수 있도록 허락하겠소. 그리고 네가 필요하다고 생각하는 만큼 네 형제와 대화할 수 있게 하겠소. 기사단의 장교들과 병사들은 내 지시를 알고 있으니, 그들이 너를 막지 않을 것이오.";
			link.l1 = "그 지하 기지는 어디에 있소?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "여기, 생피에르에 있지, 물론이오. 현지 감옥을 찾아가서 기사단의 상징이 표시된 문으로 들어가시오.\n지하 2층의 카스마트로 내려가면 될 것이오. 몽페르 나리가 거기 있을 것이오. 하지만 걱정 마시오. 감옥을 나서면 누군가가 당신을 맞이해 형님께로 안내할 것이오 – 모든 준비는 내가 해두었소...\n이상일세. 다시 만날 수 있기를 바라오, 샤를. 병장!";
			link.l1 = "잠시만 기다려 주십시오, 각하! 제... 소지품은 어떻게 됩니까? 제 검과 나머지 것들은요?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "당신의 소지품은 형님의 빚을 갚기 위해 압수되었소. 안녕히 가시오, 드 모르 나리.";
			link.l1 = "이런 젠장...";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "아하, 샤를 드 모르 자네가 직접 왔군! 만나서 반갑네. 자네, 오늘 여기 온 이유가 동생의 운명에 대해 나와 이야기하려는 것일세?";
			link.l1 = "저는 미셸 드 몽페르가 기사단과 당신께 진 빚을 갚을 준비가 되어 있습니다.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "흠... 그런데 돈은 어디 있지? 자네 유머 감각이 참 이상하구나, 젊은이. 나는 전혀 모르겠네.";
			link.l1 = "실례합니다, 푸앵시 나리. 돈을 배에 있는 내 사물함에 두고 왔습니다. 곧 돌아오겠습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "돈을 가져왔는가, Charles?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "물론이오! 이 금액이면 그대의 모든 비용을 충분히 충당할 수 있기를 바라오.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "아직 아니오...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "훌륭하오! 내가 그것들을 받아가겠소. 이번에 자네가 진가를 보여주었구려, 샤를!";
			link.l1 = "미셸 드 몽페르의 석방 명령은 언제 받을 수 있습니까?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "서두르지 마시오, 젊은이. 자신의 목숨을 걸고 빚을 갚으며 가족을 지키려는 그대의 행동은 존경할 만하오. 요즘은 드문 고귀함이지... 하지만 이 슬픈 이야기의 핵심은 돈이 아니오. 그대의 형제가 그렇게 큰 금액을 받은 것은 아주 민감한 임무를 수행한다는 조건이었소.\n미셸 드 몽페르는 충실한 가톨릭 신자로서, 한 건방진 이단자를 응징하고 그가 어긴 정의를 회복하여 기사단과 성스러운 교회의 영광을 위해 방법을 찾겠다고 성경에 맹세했소...";
			link.l1 = "하지만 그가 감금된 상태에선 약속을 지킬 수 없소! 그를 풀어주면, 나 혼자 하는 것보다 우리 둘이서 훨씬 더 빨리 임무를 완수할 수 있을 것이오.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "보게, 친구여, 그대의 형제가 내게 그의 품행을 신뢰하지 못할 강한 이유를 주었네. 그가 도망치거나 맹세를 어길 것이라는 보장이 없소. 그러니 그에게 모든 혐의를 벗겨 주고 싶다면, 그대가 직접 맹세를 하시오. 자세한 내용은 몽페르 나리가 설명해 줄 것이오.";
			link.l1 = "흠... 그럴 줄은 몰랐소. 하지만 자네가 내게 선택의 여지를 남기지 않는군. 내 마지막 결정은 형제와 상의한 후에 내리겠소.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "이제 정말로 자네가 마음에 드는군, 샤를. 언젠가 우리도 친구가 될 수 있을지도 모르지. 아무튼, 이번이 자네 형을 풀어주는 마지막이네. 자네가 형이 하지 못한 일을 해낸다면, 자네 가문의 명예는 더럽혀지지 않을 거라고 내 약속하네.\n그리고 앞으로 내 우정도 기대해도 좋을 것이네.";
			link.l1 = "완전히 이해하였소. 안녕히 가시오!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "걱정 마시오, "+pchar.name+", 약속을 지키겠소. 그대의 형제는 석방될 것이며 모든 혐의도 철회될 것이오. 이제 그대 가문의 명예는 안전하오. 이 모든 것은 오직 그대의 노력 덕분이라 말할 수 있겠구려. 그대 부친께서 이런 아들을 두신 것을 자랑스러워하실 것이오.";
			link.l1 = "친절한 말씀 감사합니다, 푸앵시 나리. 바로 마르티니크로 출발해도 되겠습니까?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "잠깐 기다리시오, 친구. 내가 그대를 친구라 불러도 되겠소? 직접 감사를 표하고 싶었소. 그대가 이곳에 온 이후로 나는 계속 그대의 행보를 지켜보고 있었고, 대부분의 업적도 알고 있소. 그대는 카리브 해에서 상당한 명성을 쌓았으며, 의심할 여지 없이 특정 계층에서 널리 알려지고 존경받는 인물이 되었소. 프랑스에는 그대와 같은 인재가 필요하오\n선장 "+GetFullName(pchar)+"! 프랑스 국왕 폐하께서 내리신 권한으로, 나는 그대에게 왕립 해군의 선장 임관을 제안하는 영광을 누리며, 프랑스 해군 소속 경프리깃함 '그리퐁도르'를 그대의 지휘 하에 두고자 하오!\n이 배의 전임 선장 드 퐁트노는 그대 덕분에 토르투가의 총독이 될 것이며, 카리브에서 가장 뛰어난 경프리깃함에는 마땅히 훌륭한 선장이 필요하오. 이 제안을 받아들이겠소?";
			link.l1 = "흥미롭군. 그럼 대가로 무엇을 원하는가?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "조금만 내게 주면 되오. 네가 잡은 것의 10분의 1, 그리고 가끔은 민감한 임무를 완수해 주면 되지. 자네의 결정을 기다리고 있겠소.";
			link.l1 = "그런 제안을 거절할 사람은 없을 것이옵니다, 각하! 조국을 위해 봉사하는 것은 큰 영광이옵니다!";
			link.l1.go = "serve_3";
			link.l2 = "제가 건방지게 들릴 수도 있겠으나, 지금은 나리의 제안을 사양해야 하겠습니다. 집안일로 인해 즉시 본국으로 돌아가야 할지도 모르기 때문입니다.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "유감이오. 그대가 동의해 주길 바랐건만... 하지만 어쩔 수 없이 한 가지 부탁을 더 해야겠소. 사실 그대에게도 이익이 되는 일이오. 마르티니크가 공격받고 있소. 항구와 도시 안에서 치열한 전투가 벌어지고 있지.\n안타깝게도, 내가 그곳 주둔군을 돕기 위해 보낼 수 있는 사람은 그대뿐이오. 조국의 애국자로서, 어떤 수단을 써서라도 그 공격을 막아 주길 바라오. 그대에게 그럴 만한 자원이 충분하길 바라오.\n게다가, 그대의 형제도 아직 그곳에 있소. 그대가 그의 목숨을 구할 수 있을 것이오.";
			link.l1 = "내 형제가 위험에 처했다고? 지금 바로 가겠어!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "이 얼마나 고귀한 말씀이오! 진정한 군인, 그리고 조국에 충성하는 아들의 말이로군! 축하하오, 나리 "+GetFullName(pchar)+". 그대는 프랑스 해군 사령관 계급을 수여받았소. 이 제복을 내게서 받으시오. 자랑스럽게 입고 그에 걸맞은 사람이 되시오!";
			link.l1 = "나는 내 조국을 위해 봉사하오!";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "중형 코르벳 '그리퐁도르'가 이제 그대의 지휘 아래 있소. 지금 이 순간부터 이 훌륭한 배는 그대의 것이오. 이 배의 뛰어난 성능을 폐하의 영광과 카리브 제도에서 프랑스의 영향력 강화를 위해 활용하시오!";
			link.l1 = "즉시!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "하지만 자네 함대가 이미 너무 크니, 배 한 척을 처분하고 나서 '그리퐁도르'를 받으러 오시오.";
				link.l1 = "좋소. 그렇게 하겠소.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "배와 함께 임시 선장과 선원들도 받게 될 것이오. 원한다면 그를 계속 지휘하셔도 되고, 배에서 내리게 하면 우리가 다른 자리를 찾아줄 것이오.";
				link.l1 = "알겠습니다!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "하지만 나쁜 소식이 있소, 선장. 방금 마르티니크가 공격받고 있다는 보고를 받았소. 항구와 도시 안에서 치열한 전투가 벌어지고 있소.\n안타깝게도, 주둔군을 도울 사람은 그대밖에 없구려. 이것이 그대의 첫 임무요:\n생피에르를 지키시오! 게다가, 그대의 형제가 아직 그곳에 있으니, 그의 목숨도 구할 수 있을 것이오.";
			link.l1 = "내 형제가 위험에 처했다니? 지금 바로 가겠어!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "'그리퐁도르'를 지휘할 준비가 되었소?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "아직 아닙니다, 지금 함대 내에서 제 함선들을 재배치하고 있습니다...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "그렇소.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "훌륭하오! 배와 함께 임시 선장과 선원들도 받게 될 것이오.\n원한다면 그를 계속 지휘하셔도 되고, 배에서 내리게 하면 우리가 다른 자리를 찾아주겠소.";
			link.l1 = "알겠습니다!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			DelCharleePrince("");
			dialog.text = "이것은 시작에 불과하오, 나리! 그대의 군사적 재능이라면 반드시 크게 성공할 것이라 확신하오! 그리고 이미 훌륭한 해군 장교에게 맡길 또 다른 임무가 있소. 그대라면 역시 잘 해낼 것이라 믿어 의심치 않소. 게다가 이번 임무는 이전 임무와 직접적으로 연관되어 있소.";
			link.l1 = "듣고 있소, 나리";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "하지만 먼저 내 집무실에 들어온 분을 소개하겠소. 이분은 프랑스 서인도 무역회사의 명예 회원, 노엘 포르게 남작이오. 남작께서는 우리 군도를 방문하여 식민지들을 시찰하고, 사탕수수와 기타 작물 재배 조직을 확장하며, 이 지역의 무역 관계 발전 가능성도 모색할 예정이오. 파리에서 남작께 가능한 모든 지원과 협조를 제공하라는 명령이 내려왔으니, 우리는 당연히 그렇게 할 것이오. 남작 나리, 이분은 프랑스 해군에서 가장 유능한 선장 중 한 명인 샤를 드 모르 나리이오...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "그러면, 샤를, 남작과 내가 생크리스토프를 시찰하는 동안 그대에게 임무를 내리겠소. 프랑스 식민지를 공격하고도 무사할 수는 없는 법이오. 스페인 놈들은 이미 마르티니크에서의 침략으로 본때를 보았지만, 그들의 죄는 금전으로라도 반드시 대가를 치러야 하며, 식민지에 입힌 피해를 보상해야 하오.\n프랑스 남작과 함께 강력한 함대가 도착했는데, 그 중에는 위엄 있는 66문 함포의 '에클라탕' 호도 있소. 그 배의 선장은 노련한 항해사지만, 카리브 해는 처음이니 그대의 지휘를 받게 될 것이오. '에클라탕'과 함께 스페인령 트리니다드 섬 해안으로 항해하여, 생피에르 공격에 대한 배상금으로 삼십만 페소를 스페인 놈들에게 요구하시오.";
			link.l1 = "푸앵시 나리, 정말로 스페인 놈들이 동의할 거라 생각하십니까?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "확신하오. '에클라탕'과 그대의 전대가 산호세 요새를 박살내고 나면, 상륙 부대를 투입해 도시를 점령하거나 병사를 잃을 필요는 없을 것이오. 경고 없이 공격해 요새를 파괴한 뒤, 사령관에게 조건을 제시하겠다는 신호를 보내시오. 이런 상황에서는 스페인 놈들이 달아날 곳이 없으니, 차라리 돈을 내는 쪽을 택할 것이오. 만약 그대가 아무런 방어도 없는 도시의 총독이라면 어떻게 하겠소?";
			link.l1 = "흠, 그럴듯하군요, 푸앙시 나리.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "무엇을 해야 하는지 알겠소?";
			link.l1 = "예, 폐하.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = " 그럼 바로 시작하게. 여기 '에클라탕' 선장에게 주는 서신이니, 그대의 권한을 확인해 줄 것이오.\n이 훌륭한 배와 잘 훈련된 선원들이 이제 그대의 지휘 아래 있소.\n샤를, 이제 그대는 프랑스를 위해 복무한다는 것을 잊지 말게. 그리고 나 같은 관리들과 제대로 소통하려면 제복을 입는 것이 좋소. 그대에게 아주 잘 어울리니 말이오.\n행운을 비네, 드 모르 선장!";
			}
			else
			{
				dialog.text = " 그럼 바로 시작하게. 여기 '에클라탕' 선장에게 주는 권한 확인서가 있네. 이 훌륭한 배와 잘 훈련된 선원들이 이제 자네의 지휘 아래 있지. 그리고, 샤를: 선장 제복을 입도록! 내가 명령하네! 첫째, 프랑스 왕립 해군 장교가 상인이나 사략선처럼 보이는 건 부끄러운 일이네. 둘째, 자네는 제복이 아주 잘 어울리니 말이야. 내 명령을 즉시 이행하게, 드 모르 선장!\n";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "'에클라탕'이 침몰했다니? 샤를, 이건 참사요! 이제 장관께서 뭐라 하시겠소? 나를 실망시켰구려, 샤를! 나는 자네의 경험을 믿었건만, 자네는... 유감이오, 이 일에 대한 책임은 자네가 져야 하오. 내가 보고서를 올릴 테니, 당분간 자취를 감추는 게 좋겠구려. 자네의 왕립 해군 복무는 여기서 끝이오.";
			link.l1 = "흠... 미안하오, 나리. 장관의 분노가 가라앉을 때까지 한두 달쯤 사라져 있는 게 정말 나을 것 같소. 안녕히 계시오, 그리고 다시 한 번, 실망시켜 드려 정말 죄송하오.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "완벽하오!";
				link.l1 = "여기, 이 삼십만을 받아 주시오.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "완벽하오, 그런데 돈은 어디 있소, Charles?";
				link.l1 = "흥, 배에 있는 상자 안에 있소. 곧 가져다주겠소!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "그래서, 샤를, 트리니다드에서 몸값을 가져왔는가?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "예, 나리. 여기 있습니다.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "곧 가져오겠습니다!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "나는 자네가 마음에 드는군, 샤를. 자네는 결코 실망시키지 않지. 이번 임무는 쉽지 않았으나, 보상으로 상환금 중 5만 페소를 하사하겠네. 받아가게, 전부 자네 것이네.";
			link.l1 = "감사합니다, 푸앙시 나리.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "이미 새로운 임무가 있소. 포르게 나리가 생크리스토프에서 조사를 마쳤고, 이제 우리 북부 식민지들을 방문하고 싶어 하오. 자네가 남작을 토르투가와 히스파니올라로 모시고 가서, 그의 업무를 모든 면에서 도와주고 요청을 충실히 이행해 주길 바라오. 이해했소, 샤를?";
			link.l1 = "물론이지, 슈발리에.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "남작께서 시간이 촉박하시니, 다른 일에 한눈팔지 말고 여정이 두 달 이상 지연되지 않도록 해주시오.";
			link.l1 = "물론이오, 나리. 섬들 사이의 항해는 그리 오래 걸리지 않소, 다만 포르게 나리의 식민지 업무가 오래 걸리지 않는다면 말이오.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "완벽하오. 그러면 남작께서 그대의 배로 이동할 것이니, 가장 좋은 선실을 내어드리시오.";
			link.l1 = "물론입니다, 슈발리에 나리!";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "그리고 한 가지 더 있소, 샤를: 또다시 장교 제복을 입지 않았구려! 이번이 마지막 경고요. 지금 이 순간부터, 나를 찾아올 때는 반드시 제복을 입고 오시오. 그렇지 않으면 당신의 말을 듣지 않겠소. 당신은 근무 중이며, 규율이란 모든 것의 기본이오. 특히 해군 장교의 외모에서는 더더욱 그렇지!\n";
			link.l1 = "용서해 주십시오, 푸앙시 나리. 이런 일은 다시 없을 것입니다.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "그대의 여정이 성공할 것이라 의심하지 않았소. 토르투가나 포르토프랭스에서 온 소식은 없소?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "예, 푸앵시 나리, 소식을 가져왔으나 그리 유쾌한 내용은 아닙니다. 우선, 포르토프랭스의 총독은 스페인인들이 식민지 공격을 준비 중이라고 확신하고 있으며, 이를 위해... 음, 뭐였더라... 산티아고, 맞습니다, 산티아고에서 군함 편대를 모으고 있다고 합니다. 그리고 이건 단순한 소문이 아닌 듯합니다. 이 문제를 그냥 넘길 수는 없다고 생각합니다. 특히 포르토프랭스의 플랜테이션은 제가 본 것 중 최고 수준이었으니까요.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "스페인 놈들이 포르토프랭스를 공격할 준비를 하고 있단 말이오? 흠... 좋소. 이 일은 자네에게 맡기겠네, 샤를 드 모르 선장. '에클라탕'은 막 수리와 장비를 마치고 출항 준비가 되어 있네...\n";
			link.l1 = "그리고 한 가지 더 있소, 나리: 파리에서는 이곳 북쪽에 위치한 생마르탱 섬을 프랑스 식민지로 여기고 있소. 하지만 샤를 드 모르 선장이 네덜란드인들이 그곳을 장악하고 있다고 내게 말했소. 사실이오, 푸앙시 기사 나리?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "흠... 어느 정도는 맞는 말이오. 생마르탱은 프랑스 식민지이긴 하오. 하지만, 남작 나리, 경제적 관점에서 보면 이 섬은 전혀 쓸모가 없소 - 면적도 작고, 토양은 척박하며, 식수도 부족하오. 우물에 있는 물도 얼마 되지 않고, 탁하고 쓰다고 들었소. 심지어 그곳에서는 빗물을 받아 마신다고 하더군.\n그래서 생마르탱은 네덜란드 서인도 무역회사에 장기 임대로 넘겨졌소. 그 회사는 이 섬을 본국과 이 지역을 오가는 선박들의 북부 중계지로 사용하고 있지. 네덜란드인들은 그곳에 필립스버그 정착지를 확장하고, 요새와 항구를 지었소. 그러니 이 군도에 비교적 최근에 도착한 샤를 드 모르 선장처럼, 생마르탱이 네덜란드 식민지로 보일 수도 있겠지.";
			link.l1 = "하지만 법적으로 그 섬은 우리 소유가 아니오?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "물론이오. 하지만 내가 말했듯이, 그 희귀한 자원을 사용하는 것보다 임대료로 돈을 버는 것이 더 이익이 되오.";
			link.l1 = "이 섬은 프랑스 서인도 무역회사가 카리브 해에 진출할 때 매우 유용할 것 같소. 그대가 방금 말한 의미, 즉 유럽으로 가는 길목의 북쪽 전초기지라는 점도 그렇고. 나는 이 식민지를 방문해야 하오, 그리고 이 섬을 네덜란드인에게 임대하는 일도 곧 중단될 가능성이 매우 높소.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "우선, 윌렘스타드에 네덜란드 서인도 무역회사 이사이자 피터 스토이베산트 나리의 조폐국으로 조회를 보내야 하오. 그가 섬 조사 허가를 내려야 하네. 어차피 네덜란드인들이 오랫동안 그곳에 있었으니 말이오.";
			link.l1 = "그렇다면 윌렘스타드로 급사를 보내야겠군.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "문제는, 스토이베산트 나리는 윌렘스타트에 거의 머무르지 않고, 항상 여행을 다니며 자신의 갤리온에서 동인도 회사의 일들을 처리하고 있다는 것이오...";
			link.l1 = "그래도 가끔은 거기에 있겠지요? 어쨌든 네덜란드인들은 섬의 정당한 소유주가 점검할 수 있도록 보장해야 할 의무가 있소. 필립스버그 총독에게 서한을 보내는 것이 어떻겠소?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "마르틴 토마스 나리는 아무리 존경받는다 해도 그저 평범한 직원일 뿐이오. 실제로 경영을 하는 것은 회사요. 남작 나리, 이 문제는 내가 해결하겠소, 걱정 마시오. 시간이 좀 걸릴 것이오.";
			link.l1 = "음, 나는 시간이 충분하오. 어차피 우리는 남부 식민지들, 과들루프와 마르티니크에도 들러야 하니 말이오.\n이번에는 샤를 드 모르 선장이 나와 함께하지 못해 아쉽소 – 그는 또다시 히스파니올라로 가야 하니까...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "그래, 그래, 우리 지루한 이야기로 우리 소중한 선장을 붙잡고 있군! 샤를, '에클라탕'을 전대에 합류시키고, 히스파니올라로 진격하여 스페인 놈들이 포르토프랭스에 실질적인 위협을 가할 만한 움직임이 있는지 알아보게. 만약 있다면, 직접 처리하게. 하지만 내가 가르칠 필요는 없겠지, 자네가 나보다 더 잘 알 테니. 아무것도 발견하지 못하면 시간 낭비하지 말고, 나는 자네가 여기 있어야 하네. 한 달 이내로 보고를 기다리겠네. 행운을 비네, 친구!";
			link.l1 = "감사합니다, 푸앙시 나리. 즉시 출항하겠습니다.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "그리고 한 가지 더 있소, 샤를: 네가 네덜란드 당국과 문제가 있다고 들었네? 부디 이 문제를 최대한 빨리 해결하게. 가까운 시일 내에 그들의 식민지에 방문해야 할 테니 말이오. 알다시피, 요새의 포격을 받으면서는 그게 불가능할 것이니.";
			link.l1 = "알겠습니다, 나리. 그렇게 하겠습니다.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "그리고 한 가지 더 있소, 샤를: 경고하겠소, 네덜란드인들과의 충돌은 피하시오. 가까운 시일 내에 그들의 식민지에 들러야 할 것이오. 알다시피, 요새에서 포격을 받는 상황에서는 그건 불가능하오...\n";
			link.l1 = "좋소, 나리. 네덜란드인들과는 다툴 생각 없소.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "'Eclatant'가 침몰했다니? 샤를, 이건 참사요! 이제 장관께서 뭐라고 하시겠소? 나를 실망시켰구려, 샤를! 나는 자네의 경험을 믿었건만, 자네는... 유감이오, 이 일에 대한 책임을 져야 할 것이오. 내가 보고서를 올릴 테니, 한동안 자취를 감추는 게 좋겠구려. 자네의 왕립 해군 복무는 여기서 끝이오.";
			link.l1 = "흠... 미안하오, 나리. 장관의 분노가 가라앉을 때까지 한두 달쯤 내가 사라지는 게 정말 낫겠구려. 그럼 이만, 그리고 다시 한 번, 실망시켜 드려 정말 죄송하오.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "훌륭하오! 그대와 같은 선장들이 우리 해군에 있는 한, 카스티야 놈들의 계략도 두렵지 않소. 내일 나는 전령을 포르토프랭스로 보내 프랑스에서 온 공문과 서신을 전달할 것이며, 동시에 제레미 데샹 뒤 뮈사카 나리에게 개인 편지로 그대의 공로에 감사하는 것이 마땅하다는 암시도 줄 것이오. 그러니 장담하건대, 샤를, 그대는 마땅히 받아야 할 보상을 받게 될 것이오.\n이제 다음 임무로 넘어가도록 하세. 그래, 친구여, 그대에게 새로운 임무가 있소. 하지만 이번에는 군사적 임무가 아니라 아주 미묘한 문제이니, 그대가 직접 처리해 주었으면 하오.";
			link.l1 = "듣고 있소, 푸앙시 나리.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "내가 포르게 나리와 생마르탱에 대해 논의했던 것을 기억하리라 생각하오? 우리는 남작에게 식민지가 점검되었다는 확신을 주어야 하오. 그러니 그대는 퀴라소, 빌렘스타트로 가서 컴퍼니의 이사인 피터 스타이브선트에게 가야 하오. 그는 지금 그곳에 있으며 앞으로 3주 더 머무를 것이오. 또한, 컴퍼니의 물자가 실린 플라이트선을 호위하여 퀴라소까지 보내고, 스타이브선트 나리에게 내 편지를 전해야 하오.";
			link.l1 = "이게 전부인 임무들인가?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "예, 선장님. 스타이베산트 나리의 답변을 알려주십시오.\n포르게 나리가 마르티니크와 과들루프에서 돌아오기 전에 우리가 딱 맞춰 도착할 수 있을 것이오. 그러면 오랫동안 가보고 싶어 했던 생마르탱을 마침내 방문할 수 있을 것이오.";
			link.l1 = "좋소. 이제 가도 되겠소?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "가도 되네, Charles. 너무 오래 걸리지 마라, 남작께서는 기다리는 걸 싫어하시니. 그리고 Peter Stuyvesant를 방문할 때는 반드시 제복을 입도록 하게! 무슨 뜻인지 알겠지? 모든 것이 공식적으로 보여야 하네.";
			link.l1 = "물론이지요, 슈발리에 나리. 안녕히 계십시오!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "감사하오, 선장. 내게 주시오... (읽는다)... 그렇다면, 훌륭하군! 피터 스타이베산트가 바롱 포르게가 생마르탱을 시찰하러 방문할 수 있을 것이며, 필립스버그의 총독에게 통보되어 협조할 것이라고 하였소. 내 생각에, 방문 후에 바롱께서 올바른 결정을 내릴 것이오. 즉, 그 섬을 네덜란드인에게 임대하도록 남겨두는 것이오.\n그리고 이제, 가장 기쁜 소식이 있소, 선장! 자네에게 전할 말이 두 가지 있네. 첫째: 자네의 모든 군사적 공적을 고려하여, 자네를 '준장' 계급으로 승진시키기로 하였네. 축하하오, 나리!";
			link.l1 = "나는 프랑스를 위해 봉사하오!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "그리고 두 번째로: 포르토프랭스의 총독이 당신을 위해 상품으로 가득 찬 무역선을 보냈소. 커피 500대 자루와 코코아 500대 자루가 실려 있지. 이 모두가 히스파니올라의 플랜테이션에서 수확된 것들이며, 당신이 스페인 약탈로부터 지켜낸 농장들이오. 또한, 특별히 귀중한 화물도 있었는데, 바로 리그넘 바이테 50단위요. 이것이 무엇인지 굳이 설명할 필요는 없을 것이오. 당신의 물품들은 캡스터빌의 상점 창고에 보관되어 있으니, 언제든 상인에게 가서 찾아가면 되오.";
			link.l1 = "감사합니다, 슈발리에! 정말 환상적인 소식이군요!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "그리고 이제 다음 임무에 대해 말하겠소. 포르게 나리께서 머지않아 생크리스토프에 돌아오실 것이오. 자네는 그분을 생마르탱까지 호위하고, 안전하게 보호해야 하오. 또한, 말하자면 필립스버그에서 무슨 일이 벌어지는지 면밀히 살펴보고 내게 보고하시오. 바론이 도착하는 즉시 도시를 떠나지 말도록 하시오, 선장. 내 하인이 자네를 찾아와서 보고할 것이오.";
			link.l1 = "모든 것이 분명합니다. 가도 되겠습니까?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "허락하오. 며칠 육지에서 쉬는 것이 그대에게 좋고 유익할 것이오.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "예, 푸앵시 나리, 벌써 돌아왔습니다! 생마르탱 근처에서 네덜란드 친구들이 성의 대포로 우리를 맞이하고, 세 척의 함대로 공격해 왔습니다. 샤를 드 모르 선장과 그의 선원들의 솜씨 덕분에 겨우 빠져나올 수 있었지요! 필립스버그에서 프랑스 국왕의 사절을 만나고 싶지 않은 것이 피터 스타이베선트 나리의 진심인 듯합니다. 어떻게 생각하십니까, 푸앵시 나리?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "뭐라고?! 여기 슈타이베산트가 직접 서명한 편지가 있소, 그가 보증한다는 내용이...";
			link.l1 = "하지만 필립스버그 요새의 사령관은 분명히 스타이베산트가 보낸 전혀 다른 편지를 받았소, 우리를 향해 마음껏 사격하고 함대까지 동원해 매복하라고 말이오! 그게 우연이었소, 푸앵시 나리?! 아니오! 그들은 분명히 우리를 거기서 기다리고 있었소! 대포알과 산탄을 준비하고 말이오!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "바론 나리, 간청하옵니다... 이 일은 제가 처리하겠나이다. 즉시 우리 소중한 선장 샤를 드 모르를 다시 큐라소로 보내 스튀베상트와 만나게 하겠나이다. 이 선장은 민감한 사안을 처리한 경험이 많사옵니다... 그리고 지금 하인들에게 목욕과 훌륭한 점심을 준비하라 명하겠나이다.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "샤를, 내 친구여, 윌렘스타트로 서둘러 가야 하오. 어쩌면 스튀베상트가 아직 그곳에 있을지도 모르지. 만약 없다면, 그가 어디에 있는지 알아내서 반드시 찾아내시오. 회동 중에는 그 사건에 대해 말하고 해명을 요구하시오. 나는 자네의 경험과 권위를 믿고, 이번 협상을 자네에게 맡기겠소. 그리고 단 1분도 허비하지 말고 곧바로 돌아와 회동 결과를 내게 보고하시오.";
			link.l1 = "임무는 명확합니다, 푸앵시 나리. 즉시 배를 준비하여 출항하겠습니다.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "이럴 수가...";
			link.l1 = "게다가 돌아오는 길에 네덜란드 해군 함대에게 공격을 받았습니다. 부디 설명해 주시지요, 푸앙시 나리, 도대체 여기서 무슨 일이 벌어지고 있는 겁니까?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "친구여, 그대가 얼마나 통찰력 있는지 내가 잘 알기에 아무것도 숨기지 않겠소. 다만 한 가지 부탁이 있소. 여기서 들은 이야기는 이 방을 절대 나가선 안 되오. 약속할 수 있겠소?";
			link.l1 = "물론이지, 푸앙시 나리.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "좋소. 프랑스 해군에서 훌륭한 경력이 당신을 기다리고 있을 것이오. 물론 내 도움만 있다면, 부제독 자리까지 오를 수도 있겠지! 하지만 이야기가 샜군... 이제 네덜란드와 생마르탱에 대해 말하겠소.\n당신이 생마르탱에 오기 훨씬 전부터, 그곳에서 대규모 소금 매장지가 발견되었소. 처음엔 아무도 신경 쓰지 않았지만, 곧 쿠바와 에스파뇰라의 스페인인들이 큰 관심을 보였지—소의 사체를 절이기 위해서 말이오. 당신도 알다시피, 우리는 스페인과 직접 거래할 수 없으니, 따라서...";
			link.l1 = "...네덜란드 서인도 회사라는 '협상가'를 만들어냈군...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "정확하오! 생각이 빠르고 정확하구나, 샤를! 이제 파리에서 온 감사단 소식을 알게 된 스타이베상트가 대담하게 소금 사업을 완전히 자기 손에 쥐려 하고 있소. 우리가 스페인인들과 맺은 거래를 모두에게 알리고 싶지 않을 거라 생각한 것이지. 하지만 그게 그의 실수였소. 프랑스 총독의 손에서 감히 빼앗으려는 자는 누구든 벌을 피할 수 없다는 걸 보여주겠소! 우리가 그 사실을 똑똑히 보여줄 것이오.";
			link.l1 = "내가 알기로는, 포르게 나리께서는 이 일에 대해 알아서는 안 되오...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "친구여, 자네 말이 절대적으로 옳소. 남작이 세부 사항까지 알 필요는 없지. 이미 충분히 많은 일이 일어났소. 프랑스 국왕 대리인에 대한 암살 시도, 외교 사절단의 배들에 대한 공격, 즉 자네에 대한 공격, 그리고 가장 중요한 것은 생마르탱 섬의 사실상 합병이오! 이것만으로도 네덜란드에 대한 군사 행동을 정당화하기에 충분하오.";
			link.l1 = "전쟁?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "정확하오! 내 친구, 자네라면 부제독 자리도 머지않았다네, 이해하겠나? 루브르에서 제독 제복을 입고 회담에 참석하는 자네 모습을 상상해 보게. 루이 14세 폐하께서도 그런 귀한 손님을 맞이하실 테지... 네덜란드 놈들에게 본때를 보여줘야 하오! 스튀베상트가 자기 짓을 후회하게 만들 것이네. 동의하나?";
			link.l1 = "동의하오, 푸앙시 나리. 네덜란드인들은 그들의 파렴치하고 비열한 행위에 반드시 대가를 치러야 하오.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "훌륭하오. 우리의 결정을 바로 남작께 알리고 프랑스 식민지들에 급사를 즉시 보내겠소! 그리고 자네는 긴 여정 끝에 쉬도록 하시오, 내 친구. 내일 아침 아홉 시 이후에 나를 찾아주기 바라오. 전투 임무를 준비해두겠소.";
			link.l1 = "알겠소, 나리. 잠시 실례하겠소.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "나는 이것을 전쟁이라고 부르지 않겠소, 오히려 평화를 강요하는 셈이지. 그리고 슈타이베산트가 마음을 바꾼다면 우리로서는 더할 나위 없이 기쁠 것이오. 그렇기에 지금 우리가 그에게 보여줘야 하오, 생마르탱 섬을 차지하려 든다면 얻는 것보다 잃는 것이 훨씬 크다는 사실을 말이오. 바로 그 역할을 네가 맡게 되는 것이오, 샤를.";
			link.l1 = "듣고 있소.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "생마르탱은 유럽으로 향하는 네덜란드 선박들의 환적 기지요. 회사의 배들은 필립스버그 만에 정기적으로 정박하오. 지금까지 그 수역은 그들에게 꽤 안전했지. 지금까지 말이오, 선장!.. 자네는 생마르탱 해안으로 출항해 그곳을 순찰하고, 회사의 상선들을 나포해야 하오.\n귀중한 화물을 운송할 때 회사는 동인도 상선을 사용하오—튼튼하고 무장도 잘 되어 있으며, 큰 화물칸을 가진 배들이지. 그것들이 자네의 목표요. 그런 배 다섯 척을 화물과 함께 나포해 캐스터빌로 가져오시오. 그 후에야 우리는 스토이베상트와 협상을 계속할 것이고, 어쩌면 손실을 따져본 뒤에 그의 생각이 바뀔 수도 있겠지.";
			link.l1 = "임무는 분명하오. 가도 되겠소?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "나리, 부득이하게 여쭙습니다만, 이 작전에 자금을 지원해 주실 수 있겠습니까. 몇 달간 항해하며 끊임없는 수리와 손실이 따를 것입니다...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "우리의 예산이 바닥났네, Charles. Ecliaton의 유지비와 전투로 이미 프랑스 식민지 반년치 예산을 써버렸지. 이제 이것이 자네에게 줄 수 있는 전부일세. 앞으로의 보상을 생각하게, Charles! 자네에겐 위대한 미래가 기다리고 있네!";
			link.l1 = "예, 나리!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "가게, 친구여, 행운이 그대의 모든 발걸음을 따르길 바라오.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "임무를 완수했군, 선장. 훌륭한 활약에 감사하오! 전리품 판매 수익 중 일부를 받을 자격이 있소—이십만 페소요.";
				link.l1 = "기쁘게 들리는구려, 나리!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "그래서, 너에게 남은 것은 "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" 네덜란드 배들을 우리 항구로 끌고 오기만 하면 된다.";
				link.l1 = "예, 푸앙시 나리!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "그리고 그게 전부가 아니오. 며칠 전에 생각해보았소... 샤를, 그대는 정말 프랑스를 위해 많은 일을 했구려. 솔직히 말해, 반역자 르바쇠르를 제거한 일, 스페인의 배신적인 공격으로부터 생피에르를 방어한 일, 산호세 식민지의 요새를 성공적으로 점령한 일, 그리고 스페인 놈들의 대담한 속임수에 대한 처벌로 배상금을 받아낸 일까지... 그 후에는 유럽에서 온 프랑스 왕실의 대표를 직접 호위했고, 필립스버그 근해에서 네덜란드의 매복을 피해 그의 목숨까지 구했지 않소!";
			link.l1 = "나리, 정말이지, 저를 부끄럽게 만드시는군요... 저는 그저 제 임무를 다할 뿐입니다.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "자네는 여전히 변함없이 겸손하군, 친구여. 그리고 최근 임무인 네덜란드에 평화를 강요하는 일까지 훌륭히 완수했으니, 또 한 번 내 기대를 저버리지 않았네. 과장 없이 말하자면, 자네는 진정한 국가의 영웅이야! 나는 이 제도에 있는 프랑스 식민지의 총독으로서 프랑스 최고의 훈장 몇 개를 가지고 있지... 그런데, 그건 그렇고, 이 문서를 읽어보게나.";
			link.l1 = "프랑스를 위한 탁월한 공로에 대해... 프랑스 국왕 폐하의 이름으로... 프랑스 해군에 복무하는 장교, 앙리 드 몽프의 아들 샤를 드 모르 선장에게 수여하노라... 슈발리에, 농담하시는 겁니까?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "전혀 아니네, 친구여. 자네가 마땅히 받을 보상을 주는 것이 내 영광이네. 프랑스 최고의 훈장, 생루이 훈장을 수여하겠네! 우리 나라의 모든 국민이 영웅을 알아야 하지 않겠는가! 그리고 생피에르도 자네에게 큰 빚을 졌네! 이 훈장은 자네가 받을 자격이 있네, 샤를.";
			link.l1 = "정말로, 무슨 말을 해야 할지 모르겠습니다... 감사합니다, 총독 나리! 프랑스를 위해 자부심을 갖고 계속 충성하겠다고 맹세합니다. 적 앞에서 결코 물러서지 않겠습니다!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("You've received the Order of Saint Louis! You are the hero of the nation!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "진정한 장교의 말이로군! 정말 자랑스럽네, 샤를. 이제 조금 쉬게. 그럴 자격이 있네. 그동안 나는 스토이베상트와의 협상에 나서겠네. 아마 그도 이제 우리와 적대하는 것보다 친구가 되는 편이 훨씬 이익이라는 걸 깨달았을 걸세. 도시를 떠나지 말게, 이틀 후 자네가 필요하네.";
			link.l1 = "알겠소, 나리. 추가 지시를 기다리겠소.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "예. 스타이베산트가 스페인과 동맹을 맺고 군사 행동에 나선 것 같소. 네덜란드-스페인 연합 함대가 생크리스토프를 포위했소. 보초 요새들이 그들의 모든 움직임을 매시간 내게 보고하고 있소.";
			link.l1 = "포위 공격인가?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "명백하오. 저들은 정면 공격을 택하지 않았으니, 오히려 다행이오. 적이 섬 전체를 봉쇄하기 전에 신속히 움직여야 하오, 선장.";
			link.l1 = "우리가 무엇을 해야 하오?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "세인트존, 앤티가에는 도일리 대령이 이끄는 영국 해군 전대가 주둔하고 있소. 지금 그는 조나단 폭스 나리를 방문 중이오. 적 함대를 피해 앤티가에 도착해야 하오. 그곳에서 대령을 만나 내 편지를 전하고, 도움을 요청하시오.";
			link.l1 = "대령 나리께서 우리를 도와주실 거라 생각하시오?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "그러길 바라오. 그 편지가 그에게 보상이 상당할 것임을 납득시켜 줄 것이오... 그리고 우리는 현재 과들루프 해안 근처에 있는 '에클라탕' 호의 선장에게도 편지를 보내야 하오. 그는 반드시 생크리스토프르로 서둘러야 하오. '에클라탕'의 화력이 전투에서 우리에게 큰 도움이 될 것이오. 자네가 동시에 두 곳에 있을 수는 없으니, 우리 사환 루거선이 자네의 함대에 합류할 것이오. 자네는 그 배를 적들의 포위망을 뚫고 무사히 통과시켜야 하며, 그러면 그 배는 '에클라탕'이 남쪽으로 향하기 전에 과들루프로 출항할 것이오...\n";
			link.l1 = "알겠소. 포위를 뚫고, 연락선 루거를 호위한 뒤, 서둘러 생조네로 가서 도일리 대령에게 편지를 전하시오.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "정확하오. 함대에 또 다른 함선을 받아들일 준비가 되었소?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "배 한 척을 처분하고 다시 오겠소.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "예.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "훌륭하오. 이 편지를 받아 두시오, 러거선은 준비되어 당신의 명령만 기다리고 있소.";
			link.l1 = "망설일 필요 없소, 푸앙시 나리!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "그래, 그래, 친구여, 자네의 겸손함은 내가 다 알고 있지. 자네는 진정한 장교라네! 그리고 보상도 받을 걸세, 내가 보장하지. 그렇게 치열한 전투를 치렀으니, 휴식이 필요할 테지? 자네에겐 일주일이 주어지네. 7일 뒤 내 방으로 와서 이야기하게나 – 도시가 영웅에게 줄 보상을 준비할 것이네.";
			link.l1 = "예, 나리. 가도 되겠습니까?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "가서 푹 쉬도록 하시오. 나중에 우리가 중대한 문제들을 다루어야 할 것이오 - 보다시피, 지금 네덜란드인들과의 평화는 불가능하오. 지금은 대령과 내가 중요한 사안들을 논의할 것이오.";
			link.l1 = "그럼 일주일 후에 다시 뵙겠소, 푸앙시 나리.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "도일리 대령과 논의했더니, 그가 나를 돕기로 했소. 영국이 우리를 도와 네덜란드와의 전쟁에서 지원할 것이오. 자네와 나는 반드시 반격해 정의를 바로 세워야 하오. 생마르탱 섬은 반드시 프랑스로 돌아와야 하네. 나는 이 임무를 최고의 해군 선장, 즉 자네, 샤를 드 모르에게 맡기겠소! 적들은 아직 그들의 함대 패배에서 회복하지 못했으니, 우리는 필립스버그를 공격해 점령할 것이오.\n전투가 쉽지 않을 것이네. 먼저 요새를 파괴하고, 주둔군의 방어선을 돌파해야 하오... (속삭이며) 그리고 자네는 내가 말한 소금 광산까지 정글을 강행군해 그곳에 진을 친 적들을 처치해야 하네...";
			link.l1 = "임무가 상당히 어렵습니다, 푸앙시 나리...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "자네 말은 완벽히 이해하네, 친구여. 자네의 함대는 증강될 것이오. 바스테르와 생피에르의 총독들이 각각 이미 함선을 준비했을 것이니—프리깃함이오. 자네는 과들루프와 마르티니크에 들러 이 프리깃함들을 직접 지휘하겠다고 하면 되오. 물론 자네가 원한다면 말이오—함선 선택은 강요하지 않겠소. 또한 기함의 식량과 장비를 구입하라고 2만 페소의 보조금도 주겠소. 자, 받아가시오...\n";
			link.l1 = "그러하오, 나리.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "또한, 언제나 그렇듯 '에클라탕' 호도 그대의 지휘하에 있소. 이미 수리와 장비가 완료되어 정박지에서 대기 중이니, 선장과 이야기만 하면 언제든지 인수할 수 있소.";
			link.l1 = "훌륭하오!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "시간을 허비할 수 없소, 선장. 내 첩자들이 네덜란드인들이 생마르탱의 위험을 인지하고 방어를 강화하려 한다고 알려왔소. 하지만 아직 두 달의 시간이 있소. 반드시 그때까지 임무를 완수해야 하오!\n";
			link.l1 = "제가 하겠습니다... (속삭이며) 생마르탱의 소금 광산은 어디에 있소? 섬의 어떤 지도에도 표시되어 있지 않던데...\n";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(속삭이며) 도시를 공격할 때 필립스버그의 총독 마르틴 토마스 나리에게 심문해 보시오, 그가 말해 줄 것이오. 그 네덜란드인은 겁쟁이라 절대 저항하지 않을 것이니 내가 보장하오.";
			link.l1 = "알겠소. 그럼 물러가도 되겠소?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "잠깐 기다리게, Charles. 자네는 아직 생크리스토퍼를 구한 보상을 받지 않았네. 이 금화 상자들을 도시 사람들로부터 받게나, 그리고 어떤 돈으로도 표현할 수 없는 우리의 진심 어린 감사도 함께 전하네!";
			link.l1 = "감사합니다, 나리!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "이제 가도 되오. 행운을 빌겠소, 선장! 모두가 그대의 승리를 기다리고 있소!";
			link.l1 = "안녕히 계십시오, 슈발리에 나리.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "The warship 'Eclatant' will also be under my command.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "불과 1년 전만 해도 자네가 부제독까지 승진할 줄 누가 알았겠는가, 내 친구? 이 소식이 프랑스에 전해지면 자네 아버지께서 얼마나 자랑스러워하실지 짐작만 할 뿐이네!";
			link.l1 = "저희 아버지께서 무척 기뻐하실 것입니다.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "자네는 함대에서 자신의 자리를 스스로 쟁취했네! 생마르탱은 프랑스에 되돌아왔고, 스토이베상트는 뼈아픈 교훈을 얻었지. 정말 대승이었네! 하지만 멈춰선 안 되네, 네덜란드 놈들에게 한순간도 쉴 틈을 줘선 안 되지. 그 배신에 반드시 대가를 치르게 할 것이네! 도일리 대령이 지금 포트 로열에 있으니, 해군 전대를 준비 중일세: 우리는 퀴라소를 타격해 적의 척추를 꺾을 것이네. 하지만 그건 나중 일이고, 지금은 일석이조를 노려야 하네, 샤를.\n컴퍼니가 그 엄청난 부를 모두 무역으로만 쌓은 것은 아니네. 이 지역에서 네덜란드의 주요 수입원은 바로 그들의 플랜테이션에서의 노예 노동이네. 혹시 모르고 있다면 말해두지, 샤를: 홀란드는 최대의 노예 소유국이자 노예 무역국일세. '흑상아'를 실은 동인도회사선들이 서아프리카에서 퀴라소로 정기적으로 오고 있지. 그리고 내가 그에 대해 아는 것이 있네, 스토이베상트에겐 불행히도 말일세.\n지금 이 순간, 두 척의 네덜란드 동인도회사선이 기니에서 카리브해로 향하고 있네. 선창에는 흑인 포로들이 가득하지. 열흘쯤 후면, 그 호송대는 트리니다드 섬 근처를 돌아 퀴라소로 향할 걸세. 자네 임무는 그 호송대를 찾아 두 척의 동인도회사선과 그 화물을 포획하는 것이네. 호위함들은 반드시 격침시키고, 노예들은 자메이카에 있는 우리의 동맹 도일리 대령에게 인도해야 하네. 매우 중요한 일이네, 샤를, 그래야 그의 신뢰를 얻을 수 있을 것이니... 이해하겠지.\n쉴 틈조차 주지 못해 미안하네만, 이 임무는 중요하고 민감하니 자네에게만 맡길 수밖에 없네.";
			link.l1 = "봉사는 달콤한 일이 아니지요, 푸앙시 나리. 그 누구보다 제가 잘 압니다. 제 배를 준비해서 가능한 한 빨리 출항하겠습니다.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "좋은 바람과 안전한 항해를 기원하오, 부제독 나리. \n그리고 그대가 생크리스토프에 돌아오면, 우리의 공통된 친구 노엘 포르게 나리가 필립스버그 조사를 마칠 것이며, 네덜란드인들에게서 빼앗은 전리품 중 일부가 반드시 그대에게 직접 돌아가도록 내가 조치하겠소.";
			link.l1 = "정말 감사하겠습니다, 푸앵시 나리. 가도 되겠습니까?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "가게. 행운을 빌겠네, 내 친구!";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "훌륭하오! 자네는 '불가능'이란 말을 모르는구려, Charles. 예전엔 자네 형이 카리브 최고의 해군 장교라 생각했지만, 이런 거친 비교를 용서한다면, 그도 자네에게서 배울 점이 많소. 이제 누가 우리 소중한 대령에게 가서 Willemstad 공격에 참여할지 이미 알고 있겠지.";
			link.l1 = "절대 아닙니다, 나리! 제가 어떻게 알겠습니까!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "아, 자네의 그 유명한 유머 감각이로군, 내 친애하는 친구! 하하! 물론 자네가 될 것이네, 부제독. 누구보다도 가장 자격이 있지. 준비되었나?";
			link.l1 = "물론입니다, 슈발리에 나리. 수리와 장비만 조금 있으면 바로 출발할 수 있습니다.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "'에클라탕'을 지휘하러 가는 것, 잊지 마시오. 이미 수리와 장비를 마쳤으니, 부두에서 그대를 기다리고 있소. 위대한 후베르 다시에 후작께서도 벌써 조급해하시며, 그대와 함께 또 한 번의 전투에 나서길 손꼽아 기다리고 있소.";
			link.l1 = "좋소. 장거리 컬버린을 장착한 강력한 배가야말로 내가 요새를 포격하는 데 꼭 필요한 것이오.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "잠깐 기다리게, 샤를. 우리의 친구 포르제 남작이 생마르탱에서 자네에게 소식을 가져왔네.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "파리에서 온 소식이 있소. 나리의 부제독 임명장이 국왕의 서명을 받았소. 관련 서류도 곧 받게 될 것이오. 그러니, 축하하오!";
			link.l1 = "감사합니다, 나리! 프랑스와 국왕을 위해 기꺼이 봉사하겠습니다!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "그리고 나는 언제나 그렇듯 자네에게서 이런 말을 들으니 무척 기쁘네. 샤를, 혹시 나와 함께 와인 한잔 나누고 싶지 않은가? 파리에서 직접 들여온 것이니, 이 근방에서는 하루를 돌아다녀도 이런 와인은 못 구할 걸세!";
			link.l1 = "감사합니다, 슈발리에 나리, 하지만 사양하겠습니다. 나중에 배로 돌아가야 하고, 프랑스 부제독이 갑판 위에서 취해 서 있는 건 어울리지 않으니까요.";
			link.l1.go = "patria_coat_01";
			link.l2 = "글쎄, 왜 안 되겠소? 총독 나리와 직접 술을 나눌 기회가 매일 오는 것도 아니니 말이오!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "음, 잠시 쉬어도 되네. 굳이 바로 배로 돌아갈 필요는 없지. 하지만 선택은 자네 몫이니 존중하겠네. 좋아, 그럼 바로 본론으로 들어가세.";
			link.l1 = "경청하고 있소.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "그리고 모든 총독이 자신의 부제독을 최고의 해군 장교이자 친구로 두고, 먼 고향에서 가져온 와인을 함께 마시며 같은 식탁에 앉을 수 있는 행운을 누리는 것은 아니오!";
			link.l1 = "프랑스를 위하여!";
			link.l1.go = "patria_coat_03";
			link.l2 = "건강을 위하여, 슈발리에 나리!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "그리고 국왕을 위하여!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "그리고 자네에게도, 샤를!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "흠, 훌륭한 와인이오! 동의하지 않소?";
			link.l1 = "그래, 당신 말이 맞소. 고향 가스코뉴에서 만들던 와인이 생각나는군...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "조금 틀렸소, 친구여 - 보르도라네. 그래도 가스코뉴 와인도 충분히 훌륭할 거라 믿소!";
			link.l1 = "그 맛이 점점 기억나지 않는군... 내가 프랑스를 떠난 지 얼마나 지났지? 1년? 2년?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "아, 샤를, 우리가 만난 게 마치 엊그제 같은데... 그리 유쾌한 상황도 아니었지. 이런 이야기를 꺼내 미안하오만, 그때 누군가 내게 감옥 안에 서 있던 그 사내가 훗날 프랑스 식민지에서 내 오른팔이 될 거라 말했다면, 아마 크게 웃어넘겼을 것이오.";
			link.l1 = "주님의 길은 헤아릴 수 없도다.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "실례하오, 방금 뭐라고 하셨소?";
			link.l1 = "라틴어입니다, 푸앵시 나리. 주님의 뜻은 헤아릴 수 없지요. 인생이 우리에게 무엇을 준비했는지는 아무도 모릅니다.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "정말 놀랍구나, Charles. 자네를 보니, 라틴어도 할 줄 아는 줄은 몰랐네. 하지만 한편으론, 어느 정도 우리 운명은 우리가 스스로 만들어 가는 것 아니겠는가?";
			link.l1 = "둘 다 진실이라고 생각하오. 앞으로 우리에게 무엇이 기다리고 있는지는 오직 주님만이 아시지. 하지만 주님께서는 끈질긴 자에게 보답하시오.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "더할 나위 없이 동의하오. 예를 들어, 내가 자네에게 해군 장교 임명장을 주고 그 제복을 건넸던 것도 기억하오. 그런데 지금 내 앞에 서 있는 이는 다름 아닌 부제독이 되었구려!";
			link.l1 = "세월이 참 빠르군요, 나리.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "정말이군... 자네 제복에도 도검 자국이 보이는구만; 몇몇 상처는 꿰맨 흔적이 있고, 어떤 것은 아직도 선명하게 새로워. 이건 바로잡아야 하네.";
			link.l1 = "총독 나리, 무슨 생각이 있으십니까?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "카리브 제도에 있는 프랑스 함대의 부제독이라는 새로운 직책 외에도, 자네에게 줄 선물이 하나 더 있네.";
			link.l1 = "저를 부끄럽게 만드시는군요, 슈발리에 나리. 무슨 선물 말씀이십니까?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "내가 내 전속 재단사와 이미 얘기해 두었네. 프랑스 식민지에서 제일가는 솜씨지! 자네의 계급에 걸맞은 제복을 맞추도록 했으니, 비용은 걱정 말게. 내가 모두 처리했네.";
			link.l1 = "정말 감사해요! 꼭 당신의 재단사를 찾아가 볼게요. 어디에서 만날 수 있죠?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "지금쯤 그는 항구 사무실에 있을 것이오 - 본토에서 새 사신선이 막 도착해서 작은 소포들이 왔소. 우리 재단사는 이곳에서 구하기 힘든 재료들을 항상 주문하거든.";
			link.l1 = "그럼 항구 사무소로 가겠소. 다시 한 번 고맙소, 나리!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "이제는 푹 쉬어야 할 것이오. 한 달의 시간을 주겠으니, 현명하게 보내도록 하시오. 일도, 걱정도 하지 말고 모든 일은 장교들에게 맡기고 충분히 쉬시오. 내 관저의 방을 마음껏 사용해도 되오. 하인들이 편히 모실 것이니 걱정 말고 쉬시오. 한 달 후에 다시 만나겠소 – 그때 자네와 논의할 중요한 일이 있소.";
			link.l1 = "알겠소, 푸앙시 나리. 안녕히 계십시오!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "그래, 샤를. 처음엔 내가 직접 처리할 수 있을 거라 생각했지만... 유감스럽게도 다시 한 번 자네의 재능을 빌려야겠군. 하지만 먼저 줄 것이 있네: 30만 페소와 두블룬 다섯 상자일세. 이건 슈타이베상트가 약속대로 내게 지불한 기여금의 상당 부분이네. 자네가 대부분의 일을 했으니 이 모든 걸 받을 자격이 있다고 생각하네. 받아두게. 만족하는가, 친구여?";
			link.l1 = "돈이란 누구에게도 해가 된 적이 없소, 나리. 나는 그 교훈을 뼈저리게 배웠지.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "아, 부제독 나리, 과거에 있었던 일로 기분이 상하신 건 아니겠지요?.. 이제 당신은 조국의 영웅이오, 알고 있었소? 이 새로운 지위에서 기분이 어떤가? 기억하시오: 수많은 유능한 장교들이 수십 년을 계급을 오르며 보냈지만, 노련한 손길이 없으면... 그저 지휘관 자리에 머무를 뿐이오. 하지만 그대는, 내 친구여, 언제나 불가능을 이뤄내는 특별한 능력이 있지! 그리고 높은 곳에 친구이자 수호자가 있으니, 앞으로 무슨 문제가 생겨도 내가 도와줄 것이오.";
			link.l1 = "이렇게 친절한 말씀을 해주셔서 감사합니다, 각하. 이 지역에서 거의 모든 것을 이룬 듯한 기분이 듭니다. 물론 각하의 도움이 있었기에 가능했지요. 이제는 제 일에 좀 더 평온하게 집중해도 되겠습니까? 가족을 생각해야 하니 말입니다.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "결혼하고 싶나, 샤를? 아하하! 파리의 아름다운 여인 아무나 가리키기만 하면 곧바로 네 것이 될 텐데! 하지만, 유감스럽게도 그건 잠시 미뤄야 하네. 지금은 자네가 여기 있어야 하네, 내 친구여, 적어도 당분간은.";
			link.l1 = "지금 프랑스가 군도에서 그 어느 때보다 강해진 것 같소. 영국과의 동맹, 컴퍼니와의 휴전. 더 이상 골칫거리인... '르바쇠르' 같은 자들도 남아 있지. 그렇지 않소?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "국가란, 사람과 마찬가지로 아무리 가져도 항상 더 원하지... 그리고 우리는 정말로 새로운 '르바쇠르'를 얻게 되었소, 부제독 나리...";
			link.l1 = "정말인가? 그런데 그게 누구지?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "우리의 오랜 지인, 노엘 포르게 남작이오. 그가 왜 여기 왔는지 기억하시오?";
			link.l1 = "흠... 자네가 서인도 무역회사에 대해 언급했었지. 파리에서 네덜란드인들처럼 똑같은 조직을 만들기로 결정했단 말이오?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "정확하오. 네덜란드 동인도 회사와 비슷하지. 하지만 아무 기반 없이 회사를 세우는 것은 매우 어렵소. 보시다시피, 스토이베산트는 여러 대륙과의 무역 경험이 수십 년에 달하고, 잘 구축된 대리인 네트워크와 강력한 상선 함대를 가졌소. 프랑스에는 그런 것이 없고, 혹시 몰랐다면 말이오, 샤를, 지금 국왕께서는 심각한 재정난을 겪고 계시오. 그들은 무역을 이곳으로 유도하여 본국의 재정 상황을 개선하려 하지만, 우리가 무엇을 마주하게 될지 제대로 이해하지 못하고 있소.\n영국과 네덜란드 모두와의 경쟁, 스페인의 영토 야욕, 그 어느 때보다 기승을 부리는 해적질. 모든 무역 플라이트선은 반드시 해군 함선의 호위를 받아야 하오, 아니면 목적지에 도달하지 못할 위험이 크오. 우리는 네덜란드 동인도 회사처럼 강력한 함대도, 스페인의 위대한 갈레온도 없소.";
			link.l1 = "하지만 이 모든 것을 남작에게 설명했소? 해적들에 대해서도 말이오?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "물론 했지. 그리고 자네가 르바쇠르를 제거하라는 임무를 수행한 뒤 토르투가에서 해적들을 추방한 일에 대해서도 말이오. 해적들은 그 일을 잊지 않았고, 영원히 우리에게 원한을 품을 것이오. 나는 여러 사람들과 만남을 주선하여 내 우려를 확인받았지만, 유감스럽게도 남작에게는 아무런 영향도 없었지. 그는 장관들에 의해 이곳에 파견되었고, 그들에게 빚을 졌으니... 세상이 원래 그런 법이오.";
			link.l1 = "흠...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "그리고 파리에서 직접 통제하는 군도 무역회사가 있다는 사실을 굳이 숨길 필요도 없소... 자네와 나, 부제독이여... 우리에겐 여기 그런 게 필요 없지 않소.";
			link.l1 = "알겠습니다.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "보시다시피, 친구여, 나는 지금 당신에게 매우 솔직하게 말하고 있소... 그래서 나는 포르게 나리께서 이 무역 회사를 설립하려는 생각을 바꾸시길 온 마음을 다해 바랐으나... 그렇게 되지 않았소. 나는 이미 남작에게 내 모든 영향력을 소진했으니, 이제 그대가 나서야 하오.";
			link.l1 = "흠... 르바쇠르 때처럼 말이오?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "오, 맙소사, 아니, 날 뭘로 보는 거요, 샤를?! 그 남작은 영향력 있는 인물이오, 재무장관의 친구이기도 하오! 게다가, 그를 물리적으로 제거해도 아무 소용 없소. 파리에서 새로운 정치가를 그냥 보내올 뿐이오. 애초에 그런 회사를 조직한다는 생각 자체를 무너뜨려야 하오, 이해하겠소, 샤를? 그래야 남작이 프랑스로 돌아가서 재정적으로 위험하고, 터무니없다고 보고할 것이오...\n";
			link.l1 = "생각이 있소, 나리?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "안타깝게도 아니오, Charles. 내가 할 수 있는 건 다 해봤소. 배와 돈이 없다고 겁도 줬고, 네덜란드인과 해적도 들먹였지... 아무 소용 없었소.";
			link.l1 = "말뿐으로는 부족한 일이로군. 흠... 해적들이라 했소?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "자네에게 좋은 생각이 있군, 친구여? 나는 조금도 의심하지 않았네. 자네의 머리는 정말 비상하니까. 저 남작을 설득하게. 그러면 자네 아버지께서 루브르에 어울릴 만한 보물로 집을 가득 채울 만큼 충분한 돈을 갖게 해주겠네. 약속하네, 샤를.";
			link.l1 = "알겠습니다, 드 푸앙시 나리. 임무는 분명합니다.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "맹세하네, 샤를, 자네가 성공한다면 결코 후회하지 않을 것이네. 그 점은 확신해도 좋네. 내가 자네를 배신한 적이 있었나, 친구여?";
			link.l1 = "절대 아니오, 나리. 남작은 어디에서 찾을 수 있소?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "지금 그는 포르토프랭스에 있소. 에스파뇰라의 끝없는 들판과 계곡이 무척 아름답다고 하더군...\n";
			link.l1 = "좋소. 이제 실례하겠소.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "바로 그거요. 남작이 내게 전부 말해주었소. 그가 겪은 모든 일을 생각하면... 하지만 자네만큼 명확하게 설명할 수 있는 사람은 없구려, 부제독! 나도 자네에게 그 점을 배워야겠군!";
			link.l1 = "당신에게서 많은 것을 배웠소, 푸앵시 나리.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "친구여, 내가 그대에게 신세를 졌소. 그대의 아버지께서 평생 필요로 하실 모든 것을 내가 반드시 마련해 드릴 것을 약속하오. 그리고 그대 가문의 저택도 이 지방에서 가장 훌륭한 집이 될 것이며... 프랑스 전체에서도 손꼽히는 저택이 될 것이오. 게다가 내가 10만 페소를 지불하겠소. 해적들에게 진 빚도 이것으로 해결되길 바라오...\n";
			link.l1 = "그 소식 참 반갑군요, 나리!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "자네를 위해 특별한 선물도 준비해 두었네. 이 물건의 가치와 내 진심 어린 감사의 뜻을 분명히 알아줄 것이라 믿네! 그러니, 부제독 샤를 드 모르, 자네에게 몰타 기사단의 나의 개인 의장검을 하사하겠네! 이 귀중한 무기는 자네의 제복과 완벽하게 어울릴 것이네! 만약 파리로 돌아갈 생각이 있다면, 노엘 포르제 남작이 자네를 국왕께 직접 소개해 주겠다고 약속했네 — 반드시 정복 차림에 이 훌륭한 검을 차고 그를 찾아가게! 프랑스 해군에서 자네를 기다리는 더 영광스러운 출세의 기회가 있을 것이네!\n";
			link.l1 = "이 검은 그 아름다움에 견줄 것이 없소! 감사합니다, 나리, 이런 영광은 저에게 과분하옵니다...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("You've received the Maltese Sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "그렇소! 그리고 자네가 여기 있는 동안, 큰 변화가 자네를 기다리고 있소. 좋은 변화들이지. 부제독 샤를 드 모르, 자네를 생마르탱의 총독으로 임명하겠소!";
			link.l1 = "하! 내가 제대로 들은 게 맞소?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "그래, 친구. 이제 그대는 그토록 성실히 지켜낸 생마르탱의 총독이 되었소.";
			link.l1 = "슈발리에 나리, 이 영광은 사양하겠습니다. 저는 이 외딴 섬 하나에 얽매이고 싶지 않습니다! 그리고 이런 내정 문제들까지... 그건 제가 할 일이 아니오!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "나는 그대의 거절을 받아들이지 않소. 친구여, 두려워하지 마시오. 예전처럼 살게 될 것이오. 모든 귀찮은 일들은 현 임시 총독이 처리할 것이오. 그대는 사실상 총독이 될 것이오. 샤를, 왜 하필 그대가 생마르탱을 통치하도록 임명되었는지 이해하지 못하겠소? 지금이야말로 완벽한 시기요, 아무도 의문을 제기하지 않을 때이니. 나는 내 사람 중 한 명이 그곳 총독이 되어야 하오, 내 말이 무슨 뜻인지 알겠소?";
			link.l1 = "소금 광산?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "물론이오! 그리고 두 번째 좋은 소식이 있소: 이제부터 매달 15일마다 자네는 광산 수익과 더불어 도일리의 무역에서 나오는 이익의 일부를 받게 될 것이오. 자네의 수동 소득은 한 달에 10만 페소가 될 것이오.";
			link.l1 = "하하! 그 말을 들으니 기쁘군요! 감사합니다, 푸앙시 나리. 음, 그 자리에 얽매여 앉아만 있지 않아도 된다면, 총독직을 받아들이겠소. 그런데 만약 내가 프랑스로 항해하겠다고 하면 어떻게 되오?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "결정하게 되면 — 그때 떠나게 될 것이고, 나는 매우 실망스럽겠지만 어쩔 수 없이 너를 대신할 사람을 찾을 것이오. 하지만 그게 전부가 아니오. 여기 네 아버지께서 보내신 편지가 있소. 한번 읽어보게.";
			link.l1 = "아버지께서요? 정말 기쁩니다!.. 좋습니다, 나리, 그렇게 하지요. 이제 가도 되겠습니까? 편지를 읽고 싶어서요... 저에게 새로운 임무는 없습니까?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "지금은 아니오, 총독 나리. 하지만 일이 생기면 어디서 찾아야 할지 알고 있소. 행운을 빌겠소, Charles!";
			link.l1 = "그리고 당신께도, 푸앙시 나리!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "제기랄, 이게 무슨 재앙이란 말인가! 이제 처리해야 할 문제가 더 늘었군. 이 일, 자네가 책임지나, 샤를? 사실대로 말하게. 이건 우연이었나?";
			link.l1 = "음, 뭔가 잘못됐군...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "제기랄, 이게 무슨 재앙이란 말인가! 이제 처리해야 할 문제가 더 늘었군. 남작이 죽을 장소를 정말 잘못 골랐어! 자네, 혹시 그가 이 세상을 떠나도록 도운 건 아니겠지?";
			link.l1 = "무슨 말씀입니까, 푸앙시 나리?! 당연히 아닙니다!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "제기랄, 이게 무슨 재앙이란 말이냐! 이제 처리해야 할 문제가 더 늘었군. 정말로 네가 그자를 저 세상으로 보내는 데 손을 쓰지 않았다는 게 확실하냐?";
			link.l1 = "무슨 말씀입니까, 푸앙시 나리?! 당연히 아닙니다!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "좋아. 자, 친구여, 어쩌면 모든 게 망가진 건 아닐지도 모르겠군. 열병은 열병일 뿐이니, 그렇지 않나? 그리고 부처에서 새로운 감찰관이 올 때까지, 우리는 여기서 어지러운 일들을 정리하고, 손님들을 잘 무장한 채로 맞이할 것이오... 이제, 샤를, 모든 연락처를 끊어야 하네. 왜 그런지 이해하리라 믿네?";
			link.l1 = "물론이오.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "좋아. 그럼, 친구여, 모든 게 망가진 건 아닐지도 모르지. 카리브 해에서 전투는 늘 있는 일이 아니던가? 새로 부임할 관청의 감찰관이 오기 전까지, 우리는 여기서 어지러운 일들을 정리하고 무장을 단단히 한 채 손님들을 기다릴 것이오... 그리고 지금, 샤를, 우리 모든 연락선을 끊어야 하네. 왜 그런지 이해하리라 믿네?";
			link.l1 = "물론이오.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "좋아. 그럼, 친구여, 아직 모든 게 망가진 건 아닐지도 모르지. 해적은 해적이니까, 그렇지 않나? 그리고 새 감찰관이 본국에서 오기 전까진, 여기 난장판을 정리하고 무장 단단히 한 채 손님들을 맞이할 준비를 하겠네... 그리고 이제, 샤를, 우리 모든 연락선을 끊어야 하네. 이유는 알겠지?\n";
			link.l1 = "물론이오.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "어쨌든, 친구여, 그대는 할 수 있는 모든 것을 다 했소. 그게 아무것도 하지 않은 것보다는 훨씬 낫지. 우리가 이렇게 인연이 닿은 것이 나는 기쁘오. 그대는 지금 자리를 계속 지켜도 되네, 그리고 프랑스에서 훌륭한 경력이 기다리고 있을 것이라 확신하오. 그리고 이제 파리로 돌아갈 때가 된 것 같군. 여기, 그대의 아버지께서 보내신 편지요. 받아두시오.";
			link.l1 = "제 아버지요? 그거 정말 반가운 소식이군요!.. 알겠습니다, 나리. 접촉은 금지, 완전한 비밀 유지, 그리고 가능한 한 빨리 파리로 가라는 말씀이시군요. 이제 가도 되겠습니까? 편지를 읽고 싶습니다...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "가거라, 샤를. 행운을 빌겠네!";
			link.l1 = "그리고 당신께도, 푸앙시 나리!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "정확하오. 그 어떤 이보다도 명확하게 설명하는군, 부제독 나리! 그 점은 나도 배워야겠소!!";
			link.l1 = "나리 드 푸앙시에게서 많은 것을 배웠습니다.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "친구여, 내가 그대에게 빚을 졌소. 그대의 사랑하는 아버지께서 평생 필요로 하실 모든 것을 내가 반드시 마련해 드릴 것이며, 그대의 가문 저택은 이 지방에서 가장 훌륭할 뿐만 아니라 프랑스에서도 손꼽히는 집이 될 것이오. 또한, 내가 10만 페소를 지급하겠소 – 이 돈이 그대의 여행 경비를 충당하고 충분한 휴식을 누리는 데 도움이 되길 바라오.";
			link.l1 = "그 말을 들으니 기쁘구려, 나리!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "어떻게 그럴 수 있죠, 샤를! 어떻게 저한테 이런 짓을 할 수 있습니까?!";
			link.l1 = "음...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "내가 다 알아! 네가 한 짓이야! 부정하지 마! 네 도움이 없었더라면 포르게 나리께서 광산 관리자에게서 온 보고서도, 광산 위치도, 피터 스타이베선트의 문서도 절대 받지 못했을 거야. 거기엔 네 이름이 없었지만, 분명히 말하겠다. 나는 확신해. 바로 네가 한 짓이야. 왜, 샤를?.. 대답만 해... 왜지? 미셸 때문인가? 백만 페소 때문인가? 르바쇠르 때문인가? 아니면 혹시 총독 자리를 노린 건가?";
			// belamour legendary edition -->
			link.l1 = "우리의 첫 만남을 기억하십니까, 푸앵시 나리? 그때 저를 제 자리로 돌려세우셨지요? 저에게서 백만 페소를 뜯어내셨던 것도요? 언젠가 우리가 입장이 바뀌었으면 하는 바람뿐이었습니다. 더 이상 드릴 말씀이 없습니다.";
			link.l1.go = "patria_prison_2";
			link.l2 = "르바쇠르를 위해서라면, 백만의 빚쯤은 이해할 수 있지. 나는 일했고, 죽였고, 벌었고, 빼앗았지만, 그 모든 손해를 너에게 다 갚았어. 그런데도 너는 만족하지 않았지. 너, 슈발리에, 네 개인 권력을 더 강화하려고 나를 왕실을 상대로 한 자살 임무에 보냈잖아! 네 배신에는 반드시 대가가 필요했지. 그리고 넌 그 대가를 받았어!\n";
			link.l2.go = "patria_prison_2";
			link.l3 = "야망이지, 푸앙시 나리. 이 낯선 신세계에서 나는 이미 할 수 있는 건 거의 다 이루었소. 총독 자리는 내게 걸맞은 목표로 보였지. 그대에게서 많은 것을 배웠소. 안녕히 계시오!";
			link.l3.go = "patria_prison_2";
			link.l4 = "솔직히 나도 잘 모르겠소. 아마도 나는 남작의 충성과 조국을 위한 헌신에 감명을 받았기 때문일지도 모르지? 어쨌든, 이제 자네가 이 문제에 대해 충분히 고민할 시간이 생겼으니, 나를 대신해 생각해 보시오. 그럼 안녕히!";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "만나서 반갑네, 샤를. 그대의 활약상을 들었소. 훌륭한 일이었네!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "그게 전부가 아니옵니다, 각하.";
					link.l1.go = "PZ_2";
				}
				else
				{
					link.l1 = "지금 제 형을 석방하라는 서면 명령을 써 주실 수 있습니까?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "어서 오게, 샤를. 들어오게; 이미 소식은 들었네.";
				link.l1 = "알고 계셨습니까? 무슨 착오가 있는 것 같소, 각하. 저는 임무를 성공적으로 완수했다는 보고를 드리러 왔는데, 기분이 그리 좋아 보이지 않으시는군요.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ_2":
			dialog.text = "그런가? 무슨 뜻이오, 선장?";
			link.l1 = "레바쇠르를 생포해서 당신께 데려왔소. 일이 끝나는 대로 그를 당신께 데려오라고 명령하겠소.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "그런 일이 가능하리라고는 상상도 못했소! 정말 훌륭한 솜씨로군, 샤를! 네 명망 높은 형조차도 이보다 더 잘하진 못했을 거요. 네 아버지도 분명 자랑스러워하실 게야, 내 친구.";
			link.l1 = "친절한 말씀 감사하오, Philippe 나리.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ_5":
			dialog.text = "아주 좋소, Charles. 나는 그대가 마음에 드는구려.";
			link.l1 = "지금 제 형을 석방하라는 서면 명령을 써주실 수 있겠습니까?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "아마도 내가 그대가 그대 형이 아니라는 점을 고려했어야 했겠군—군인도, 비밀 요원도 아니고, 아직 민감한 작전에 익숙하지도 않지. 토르투가 거리에서 병사들과 대놓고 싸우지 말았어야 했소. 조사들이 있을 것이고, 나에 대해서도 마찬가지요. 그대도 알다시피, 그건 만만치 않은 이들이 하게 될 것이오.";
			link.l1 = "실례를 범하오, 푸앵시 나리. 아시다시피, 르바쇠르는 싸움 없이 물러날 인물이 아니었소.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "그렇소, 하지만... 됐소. 첫 임무치고는 나쁘지 않구려. 공식 사찰 중 왕실 감사관과 그 호위를 습격했다고 보고하겠소.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "각하, 도움이 된다면 제가 르바쇠르를 직접 데려올 수 있습니다. 저와 제 부하들은 그의 부하들이 거리에서 우리를 체포하려다 실패한 후, 외진 곳에서 운 좋게 그를 붙잡았습니다.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "제 형제가 지금 구금에서 풀려나도록 나리께서 서면 명령을 써주실 수 있습니까?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "뭐라고 했나, 샤를? 다시 말해 보게.";
			link.l1 = "프랑수아 르바쇠르가 지금 제 선창에 있습니다, 필리프 나리. 넘겨드릴 준비가 되어 있습니다.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "내가 전에 한 말은 모두 잊으시오. 분명 내가 지나치게 반응했소. 훌륭한 일이었소. 자네의 명망 높은 형조차도 이 일은 해내지 못했을 것 같구려.";
			link.l1 = "감사합니다, 슈발리에 나리.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "그대는 큰 재능을 지녔구려, 친구여. 그대의 재능이 나라를 위해 더 자주 쓰였으면 하는 바람이 있소. 하지만 앞으로는 좀 더... 신중하게 행동해 주길 바라오. 우리의 일은 대개 섬세한 접근이 필요하니까. 아, 그리고 한 가지 더 있소.";
			link.l1 = "예, 나리?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
