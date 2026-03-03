// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "말해 봐라, 꼬마야. 하지만 빨리 해라. 나는 바쁜 사람이니까.";
				link.l1 = "선장들을 고용하고 있다고 들었소.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "저에게 맡길 일이 있습니까?";
			link.l1 = "아니, 미안하오. 나는 떠나겠소.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "지금쯤이면 Sint Maarten으로 반쯤 갔어야 했잖아, 카피텐.";
				link.l1 = "나는 출항 준비 중이오, 나리.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "아, 카피텐, 여기 계셨군요! 오시는 줄도 몰랐습니다. 방금 리더브록의 편지를 다 읽은 참입니다. 당신이 꽤 깊은 인상을 남겼더군요. 그는 당신을 '상인들의 수호자이자 해적들의 재앙, 회사에 내린 신의 선물'이라고 불렀습니다! 이에 대해 어떻게 생각하십니까?\n";
				link.l1 = "나는 그냥 평범한 선장으로 남고 싶소. 평범하지만, 부유한 선장으로 말이오.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "아직 여기서 뭐하고 있나, 쿠바로 출발하지 않고?!";
				link.l1 = "그래, 그래, 가고 있소, 마인헤르.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "아, 카피텐! 사실 걱정이 되기 시작했었소. 어떻게 되었소?";
				link.l1 = "쉽지 않았소만, 그 이야기는 나중에 하겠소. 우선 일부터지. 나리\n "+GetFullName(sld)+" 다음과 같이 전해 달라고 했소: '이 자는 반드시 죽어야 한다.' 그러면 제랄디가 이 사건을 끝난 것으로 여기겠다고 했소. 또한, 이 결정은 그들의 가문의 뜻이라고도 전했소.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "반갑소, 카피텐! 나를 찾아와 주어 기쁘오.";
				link.l1 = "안녕하십니까, 나리. 또 다른 회사 일거리가 있으신가요?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "배를 정박하라고 했잖아. 명령도 못 알아듣는 멍청이거나 무식한 거냐?";
					link.l1 = "둘 다 아니오, 마인헤르. 나는 가는 길이오.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "그래, 네가 배를 정박시켰군. 이제 내 제벡선을 빌려주지. 즉시 임무를 시작할 준비가 되었나? 내 배는 장비도 잘 갖추어져 있고 언제든 출항할 수 있으니, 더 이상 걱정할 필요 없어.";
					link.l1 = "예, 물론입니다. 준비되었습니다, 로덴부르흐 나리.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "왜 아직 여기 있는 거야? 당장 롱웨이에게 가.";
				link.l1 = "미안하지만, 가는 길이야.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "카피텐... 이미 당신의 항해에 대해 알고 있소.";
					link.l1 = "오, 정말인가? 그럼 너도 알겠군...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "카피텐... 이미 당신의 항해에 대해 알고 있소.";
					link.l1 = "그런가? 그렇다면 너도 알겠군...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "카피텐... 이미 당신의 항해에 대해 알고 있소.";
					link.l1 = "그런가? 그렇다면 너도 알겠군...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "여기 있소, 카피텐... 자네의 여정에 대해선 이미 다 알고 있네.";
					link.l1 = "그런가? 그렇다면 자네도 알겠군...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "앤티가로 가. 지금.";
				link.l1 = "미안하지만, 나는 가는 중이야.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "당신이 도착했다는 소식은 이미 들었소, 카피텐. 그리고 내 미라주를 전투에서 잃었다는 것도 알고 있소.";
					link.l1 = "정보가 아주 빠르시군요, 로덴부르크 나리. 내가 아무리 애써도, 그녀를 구하지는 못했소.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "당신이 도착했다는 소식을 들었소, 카피텐. 미라주가 무사히 정박해 있는 것을 보니 다행이오. 좋군.";
					link.l1 = "모두 나리의 지시에 따른 것이오. 플리트우드를 죽이라고 명하셨고, 그는 죽었소. 미라주를 이 항구로 가져오라고 하셨고, 여기 있습니다.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "아, 여기 있었군. 만나서 반갑네. 약속한 대로 또 다른 임무가 있네.";
				link.l1 = "듣고 있소, 나리.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "아, 너를 보게 되어 기쁘구나, 내 아들. 늦게 와서 걱정이 되기 시작했었다네. 에비게일에게서 뭔가 얻을 수 있었느냐?";
				link.l1 = "그뿐만 아니라, 다른 문제들도 모두 해결했소. 나는 그 섬과 세뇨르 슈뇌르의 잃어버린 재산도 찾아냈지. 솔로몬도 기뻐하고, 아비가일도 당신의 청혼을 받아들일 거요. 축하하오, 마인헤르!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "아, 만나서 반갑네, 친구. 아비게일에게서 뭔가 얻었는가?";
				link.l1 = "예. 아비게일과 그녀의 아버지와 이야기를 나눴소. 문제가 있소, 나리: 그녀 아버지의 잃어버린 재산 말이오. 아비게일은 자신이 그대에게 어울리지 않는다고 느끼고, 지참금 없는 처지로 그대 같은 신사와 결혼하면 사람들의 뒷말과 소문을 두려워하오. 이해해 주시길 바라오.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "아, 내 친구! 좋은 소식을 가져왔겠지?";
				link.l1 = "계획이 성공했소. 아비게일이 승낙할 것이오. 축하하오, 마인헤르.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "기다리고 있었네. 자네, 큰 위험에 처해 있네.";
				link.l1 = "무슨 뜻이오?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "부두에 있는 내 정보원들이 자네가 도착했다고 알려주더군. 요한 반 메르덴은 죽었나?";
				link.l1 = "그래. 그 자와 그의 공범은 사라졌어. 힘든 싸움이었지만 끝까지 해냈지.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "더 이상 논의할 일은 없소, 카피텐.";
			link.l1 = "알겠습니다, 나가겠습니다.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "무슨 일이오? 시간은 돈이니라.";
		link.l1 = "미안하지만, 난 떠난다.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "그럴지도. 너는 누구냐? 빨리 말해라, 시간은 돈이다.";
			link.l1 = "나는 선장이오 "+pchar.name+", 내 배와 내가 당신에게 도움이 될 수 있소.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "흠, 도가니에서 시험해야 할 미지의 합금이군.";
			link.l1 = "그래서 제가 여기 온 것이오, 나리.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "좋아, 네 깡이 어느 정도인지 직접 보게 되겠군. 그래, 이름도 잘 모르는 카피텐 양반, 발타자르 리더브로크를 아나? 아니? 운이 좋군. 그처럼 욕심 많고, 심술궂고, 성질 더러운 바보는 드물지.\n하지만 그 뛰어난(?) 자질만으로는 부족했는지, 그 자는 '필리버스터'라는 자를 건드릴 만큼 영악했지. "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" 현지 선술집에서 그가 칼을 집어 드는 순간, 모욕당한 쪽이 바로 경비를 불렀지...";
			link.l1 = "...그리고 그들은 눈에 띄는 밧줄을 집어 바로 그 해적을 목매달았나?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "그렇게 간단하지 않아. "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" 평범한 해적이 아니라 네덜란드의 사략선장이며, 지난 두 차례 영국과의 전쟁을 모두 겪은 노련한 자요. 이곳 납세자들은 그를 꽤 좋아하지. 리더브록에 대해서는 그렇게 말할 수 없지만.";
			link.l1 = "그래서 우리 사략선장이 아직 살아 있단 말이오?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "그래, 하지만 그는 정말 화가 났어. 그래서 리더브록이 겁에 질려 있지.";
			link.l1 = "내 행운도 이제 끝나려나 보군. 내가 언제 리더브로크 나리를 만날 수 있지?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "곧 도착할 거다. 필립스버그의 선량한 사람들이 설탕 선적을 기다리고 있는데, 우리 둘 다 아는 리더브로크가 그걸 보내주기로 약속했지. 나는 그 자가 신발 가죽만큼의 값어치도 없다고 생각하지만, 어쩔 수 없이 우리 일을 하고 있으니, 항만 사무소로 가게. 거기서 리더브로크를 찾아 내가 즉시 출항하라고 명령했다고 전해라.\n자네는 그를 따라가서... 무사히 필립스버그까지 호위하라. 나는 원치 않네 "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" 그의 화물과 함께 회사의 명성을 카리브 해 바닥으로 보내버리려고.";
			link.l1 = "으, 호위 임무라니. 이런 불쾌한 일의 보수는 어떻게 되는 거지?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "선장, 일부터 끝내시오. 발타자르가 목적지에 도착하면 곧바로 돈을 줄 거요. 필립스버그에서 말이오! 데이비 존스의 금고가 아니라! 일이 끝나면 나에게 다시 보고하시오. 성공한다면 내 후원과 회사의 지원을 계속 받을 수 있을 것이오. 물러가도 좋소.";
			link.l1 = "또 봅시다, 나리.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "그래, 리더브록은 네덜란드 놈들 중에서도 인색한 개자식이지. 뭐, 이제 내 알 바 아니다. 자, 이제 당신 얘기를 해보자고, 이름도 모를 카피테인. 난 당신 스타일이 마음에 들어. 그래서 이번엔 내가 직접 돈을 내고 또 다른 일을 맡기려고 한다.";
			link.l1 = "듣고 있소, 나리.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the brave kapitein who escorted that scoundrel Ridderbrock? We heard all about about it... He paid you only five thousand pesos! He's been boasting about it nonstop at the tavern in Philipsburg drunk as a swine. If I were you captain, I drag him out into the street and thrash him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "아주 중요한 일에 쓸 사람이 필요하오. 리더브록 사건을 잘 처리했으니, 회사에서도 자네에게 이 일을 맡겨도 된다고 생각하더군.";
			link.l1 = "영광으로 알아야 하나? 무슨 일이오?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "정확한 세부 사항은 말해줄 수 없지만, 이 일은 내 일이 아니라 회사의 일이니, 우리에게 잘 보여서 이득을 볼 기회가 있다는 점은 알아두시오. 정말로 큰 이익이 될 거라 장담하오.\n쿠바의 산티아고로 가서 이 소포를 돈에게 전달하시오 "+GetFullName(sld)+". 그는 제랄디 은행에서 높은 자리에 있고, 나의... 아니, 우리의 사업 파트너이기도 하오. 내가 지금 바로 줄 이 금을 그에게 전달해야 하오. 나는 자네의 정직함을 믿지, 카피텐. 뭐, 정직함이 아니라면 살아남으려는 본능이라도 믿겠소. 우리 회사를 속이려는 자는 언제나 결국 잡히게 되어 있소.";
			link.l1 = "나를 의심하시오, 나리?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term Company trade license in order to spare you from any diplomatic entanglements with the Spanish. This will allow you to dock at Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "지금은 당신을 의심하지 않소. 믿으시오, 내가 의심했다면 이 일에 대해 당신과 이야기조차 하지 않았을 것이오. 이 일을 준비하느라 많은 시간을 허비했으니, 당신에게 주어진 시간은 오직 열다섯 날뿐이오."+sTemp+"\n내 전갈과 소포는 반드시 제때에 전달되어야 한다. 이건 아주 중요하니라, 꼬마야. 서두르되 조심하게, 이 일은 결코 쉽지 않을 것이니.";
			link.l1 = "더 할 말 있소? 왜 나에게 경고하는 것이오, 로덴부르크 나리?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "내가 의심이 좀 있다는 정도로만 해두지. 걱정 마라, 지난번 일처럼 신속하게 처리한다면, 회사의 민감한 사안에 쓸 만한 요원이 될 기회가 있을 것이니.";
			link.l1 = "이 편지와 돈을 산티아고의 은행가에게 15일 안에 전달하기만 하면 된다고? 겉보기엔 별로 어려울 것 같지 않군.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "그렇게 서두르지 마라, 꼬마야... 네가 이 상황의 심각함을 아직 잘 모르는 것 같군. 이 일을 제대로 해내면 내가 너한테 크게 신세를 지게 되지. 하지만 실패하면, 아주 빡칠 거다. 그땐 네 위에 오줌을 싸줄 테니. 서로 이해했나, 카피텐\n "+GetFullName(pchar)+"?";
			link.l1 = "알겠소. 약속하오. 기분 좋게 해드리려고 최선을 다하겠소.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "좋소. 이제 이 편지와 이 상자들을 가져가고, 약정과 조건을 명심하시오. 그리고 한 가지 더: 산티아고에서 문제를 일으키지 마시오.";
			link.l1 = "좋소.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'죽어야 한다'... 그냥 그렇게. 전혀 예상 못 했군. 흠. 임무는 잘 끝냈어, 카피텐. 이제 보고하시오.";
			link.l1 = "별일 없었어... 그냥 식은 죽 먹기였지.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "나는 산티아고에서 어떤 남자에게 기습을 당해 납치되었어. 그자는 자네가 제랄디와 무슨 일을 하고 있는지 몹시 궁금해하더군. 겨우 도망쳤지만, 먼저 그를 죽여야만 했지. 그가 남긴 유일한 단서는 가스통이라는 이름뿐이야. 이 모든 일이 도대체 무슨 뜻인지 나는 전혀 모르겠어.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "나는 산티아고에서 어떤 남자에게 기습을 당해 납치되었어. 그자는 자네가 제랄디와 무슨 일을 하는지에 몹시 관심이 많더군. 겨우 도망치긴 했지만, 먼저 그놈을 죽여야 했지. 지옥으로 보내기 전에 아무것도 알아내지 못했어.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "회사의 감사는 말뿐만이 아니오. 보상을 받아가시오, 그럴 자격이 있소.";
			link.l1 = "회사에서 일하면 꽤 이득이 되지.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "뭐라고! 납치라니... 잠깐, 그런데... 가스통! 이제 알겠구나... 그렇군. 아, 이보게, 너도 결국 이런 더러운 일에 휘말렸구나. 우린 미지의 바다에 들어섰으니, 앞으로 어떻게 될지 두고 봐야겠지. 그래도 살아 돌아와서 다행이야.\n좀 더 유쾌한 이야기를 하자꾸나 – 이 보상은 네가 받을 자격이 충분하니 받아라.";
			link.l1 = "회사에서 일하면 꽤 이익이 되지\n";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "말도 안 돼! 널 납치하다니... 그래도 의심 가는 점이 좀 있긴 해. 계속 내 밑에서 일하면 더 알게 될 거야. 운이 좋았군, 네가 살아남아서 다행이야.\n이제 기분 좋은 얘기를 하자꾸나 – 이 보상을 받아라, 충분히 받을 자격이 있다.";
			link.l1 = "회사 일을 하면 꽤 수익이 좋지\n";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "정확하네, 내 아들! 우리가 계속 함께 일한다면 자네는 회사의 충분한 보상을 받는 요원이 될 수 있지. 이제 가서 항해의 피로를 좀 풀게. 자네는 내 기대에 부응했네. 일주일 후에 다시 와준다면 정말 고맙겠네, 아직 할 일이 많으니.";
			link.l1 = "저를 믿으셔도 됩니다, 로덴부르크 나리.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "영리하시군요, 선장님. 맞습니다. 자, 곧 있을 임무의 세부 사항을 논의해 봅시다...";
			link.l1 = "귀 기울여 듣고 있소.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "당신에게 매우 중대하고 중요한 임무가 있소. 내 지시에 따라 모든 일을 처리해 주길 기대하오. 알다시피, 합스부르크 연합주와 영국의 관계는... 원만하지 않소. 영국 놈들은 오직 자신들만이 세상을 지배해야 한다고 확신하고 있지. 문제는, 그런 주장에 모두가 동의하는 건 아니라는 거요. 그들이 어디로든 장사를 하러 가면, 네덜란드 서인도 회사가 이미 먼저 다녀갔다는 걸 명심하시오.\n우리 네덜란드는 세계에서 가장 큰 무역 함대를 보유하고 있고, 군사 함대 역시 공화국의 이익을 이곳과 해외에서 모두 지킬 수 있소. 영국인들은 우리의 무역력을 시기하여, 회사의 활동을 방해하려 온갖 수를 쓰고 있지. 그런데, 리처드 플리트우드라는 영국 해군 선장이 있소. 연방의 정식 장교임에도 불구하고, 지금은 해적으로 활동 중이오. 그는 카리브 해에서 네덜란드 깃발을 달고 항해하는 모든 배를 공격하고 약탈하고 있소. 그는 자신의 행동을 '유령선'에 대한 대응책이라 설명하오. 그 유령선이 네덜란드 사략장 허가장을 받은 사략선이라고 주장하지.\n'유령선'에 대해 들어본 적 있소, 카피텐?";
			link.l1 = "그런 헛소리는 아무 선술집에서나 들을 수 있지. 늙은 보스운에게 럼주 한 잔만 사 주면 원하는 이야기는 뭐든 들을 수 있을 거야...\n";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "이 일은 주정뱅이의 망상이 아니오. 나는 이 '유령선'의 행적을 조사했소. 그 결과, 그 배는 평범한 사내들이 타는 목재와 돛으로 된 케치선, 이름은 '미라주'였소. 그리고 야곱 판 베르흐라는 자가 지휘하고 있는데, 그가 그 배를 전설의 '플라잉 더치맨'인 척하고 있소.";
			link.l1 = "반 베르그? 그건 네덜란드 성씨잖아. 진짜 '플라잉 더치맨'이로군, 응?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "맞소. 야콥 판 베르흐는 네덜란드인으로, 원래 라이덴 출신이오. 하지만 공화국에서 이미 오래전에 교수형을 선고받았지. 그는 도망 중인 범죄자이자, 오직 자기 이익만을 위해 움직이는 해적이오. 리처드 플리트우드가 판 베르흐를 쫓고 있소. 이 사실을 저 건방진 영국놈에게 역이용할 것이오.\n플리트우드를 당장 죽이고 싶지는 않소, 비록 그 자는 오래전에 죽어 마땅했지만. 죽음만으로는 부족하오. 나는 그를 죽이는 것뿐만 아니라, 그의 이름과 명예까지 짓밟고 싶소. 그것이 내가 바라는 바이오. 그리고 그것이 다른 오만한 영국 돼지들에게도 본보기가 될 것이오.\n이제 세부 사항을 이야기해 봅시다.";
			link.l1 = "나리, 이건 점점 사적인 이야기처럼 들리기 시작하는군...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "그건 네가 신경 쓸 일이 아니다. 명령을 따르고, 그 다음에 돈을 받게 된다. 내 첩자 덕분에 야콥 판 베르흐가 그의 '미라주'와 함께 어디에 숨어 있는지 알아냈다. 그는 스페인 본토 남부의 한 도시를 근거지로 삼고 있다. 그에게 가서 그의 유령선이 어디에 정박해 있는지 알아내라\n그리고 그를 죽이고, '미라주'를 찾아내어 노획한 뒤, 이곳으로 가져와라. 반드시 '미라주'를 생포해야 한다. 침몰시킬 생각은 하지도 마라.";
			link.l1 = "간단해 보이는데. 반 베르흐를 어디서 찾아야 하지?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "모든 세부 사항은 내 대리인이 알려줄 것이오. 그의 이름은 롱웨이, 중국인이지. 이번 임무를 위해 내 개인 선박인 세벡 '메이펑'을 제공하겠소. 롱웨이가 그 배의 선장이지만, 이번에는 당신의 지시를 따를 것이오.\n현지 항만 사무소로 가서 당신의 모든 선박을 정박시키시오. 일이 끝나면 내게 다시 오시오.";
			link.l1 = "좋소, 내가 항만 관리인을 찾아가겠소. 너무 오래 기다리게 하진 않겠소.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "롱웨이가 밖에서 기다리고 있소. 그는 자네에게 새 배를 보여주고 반 베르크의 위치에 관한 정보도 줄 것이오. 행운을 비오, 카피텐. 내 기대를 저버리지 말게. '메이펑'을 반드시 내게 돌려줘야 하니, '미라주'를 탈취하는 동안 배를 침몰시키지 않도록 조심하게.";
			link.l1 = "가는 중이야!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "이 무능한 바보 같으니. 해적선을 잡는 임무를 실패했군. 내 모든 계획이 망가졌어. '메이펑'은 네 손에서 뺏겠다. 나가라, 이제 너는 필요 없다.";
			link.l1 = "죄송합니다. 안녕히 계십시오, 로덴부르크 나리.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "이 멍청한 바보 자식아. '메이펑'을 잃다니, 용납할 수 없는 일이야... 나는 네게서 '미라주'를 빼앗고, 내 손해에 대한 보상으로 네 임금도 주지 않겠다. 나가, 이제 너 따위는 필요 없다.";
			link.l1 = "죄송합니다. 안녕히 계십시오, 로덴부르크 나리.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "세상에, 너 정말 보기 드문 놈이구나. 무능한 얼간이에다 멍청이까지. 미라주를 놓치고 메이펑까지 잃어버렸지. 내 사무실에서 당장 꺼져!";
			link.l1 = "나 간다.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "잘했네. 자네의 성공 소식은 이미 내 귀에 들어왔다네. 반 베르크는 죽었고, 자네가 그의 배를 포획했다지. 보수로 5만 페소를 주겠네, 받아가게.\n이제 '메이펑'은 내가 회수하겠네. 이제 자네가 '미라주'를 지휘할 차례일세. 다음 단계에서 중요한 역할을 하게 될 것이네. 준비됐나?";
			link.l1 = "예, 로덴부르흐 나리.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "이제는 플리트우드와 상대할 차례다. 그가 그렇게 열정적으로 쫓고 있는 '유령선' 미라주를 미끼로 삼아 그를 유인할 거다. 도미니카 근처에 함정을 설치해라. 미라주가 미끼 역할을 할 것이다.\n먼저, 플리트우드에게 미라주가 도미니카 근처에서 목격되었다는 소식을 흘려라. 우리의 용감한 영국인은 하던 일을 모두 내팽개치고 먹잇감을 찾아 도미니카로 곧장 달려올 것이다. 플리트우드와 직접 대화하지 마라, 살아남지 못할 테니. 세인트 존스에 있는 약국을 찾아가라. 약제사 존 머독은 내 오랜 친구다.\n내 명령을 받고 왔다고 말하면, 그가 도미니카 근처에서 '유령선'이 영국 상인들을 습격했다는 달콤한 거짓말을 퍼뜨릴 만한 현지 인물을 찾아주는 데 도움을 줄 것이다.";
			link.l1 = "내가 할 수 있소. 목표는 도미니카에서 플리트우드를 매복하는 것, 맞소?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "맞아. 롱웨이와 '메이펑'이 도미니카 근처에서 너를 기다릴 거다. 너희 둘이면 그 영국 개새끼쯤은 쉽게 처리할 수 있지. 그의 배에 올라타서 선실을 뒤져라. 나는 그의 항해일지가 필요하다. 그걸 가져오면 추가로 돈을 주겠다.\n하지만 네 최우선 임무는 그 자식 플리트우드를 죽이는 거다. 만약 배에 오르는 게 현실적으로 어렵다면, 그냥 바다 밑으로 보내버려라. 무엇보다도 '미라주'만큼은 반드시 지켜야 한다. 다음 단계 계획에서 그녀가 아주 중요한 역할을 하게 될 테니까.";
			link.l1 = "알겠습니다.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "조언 하나 하지, 카피텐. 세인트 존 항구에 닻을 내리지 말게. 섬의 어느 만에 상륙해서 정글을 통해 도시로 가게나, 그렇지 않으면 존이 자네와 말도 안 할 걸세. 자네가 너무 눈에 띄면, 그가 모르는 척할 테니 조심하게. 그리고 바다에서도 조심하게. '미라주'는 영국 식민지들 사이에서 악명이 높으니, 그들의 군함이나 정착지는 피하는 게 좋을 걸세. 바다의 이리 떼에게 덤벼들고 싶지 않으면 말이야. 이상이네. 신의 가호가 있기를.";
			link.l1 = "알겠소.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "돌아왔군, 카피타인... 리처드 플리트우드의 항해일지를 가져왔나?";
				link.l1 = "유감이지만, 아니오. 그가 배를 침몰시키기 전에 내가 승선할 기회가 없었소.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "돌아왔군, 카피텐... 리처드 플리트우드의 항해일지를 가지고 있나?";
				link.l1 = "유감스럽게도, 그러지 못했소. 내가 발키리에 올라타 그 자와 맨손으로 싸워 죽이긴 했으나, 그의 일지는 찾지 못했소. 그의 부하 중 한 명이 탄약고에 불을 질러서, 우리는 목숨을 건져 도망칠 시간이 겨우 몇 초밖에 없었소.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "돌아왔군, 카피텐... 리처드 플리트우드의 항해일지를 가지고 있나?";
			link.l1 = "내가 했어. 여기 있어. 발키리에 올라타는 데 성공했지만, 정말 아슬아슬했지. 그 자식이 자기 배에 탄약고를 쏴서 배를 산산조각 내버렸거든. 우리도 겨우 목숨만 건졌어.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "정말 유감이군, 그게 있었다면 우리가 가진 많은 의문에 답이 되었을 텐데. 하지만 이제는 상관없다. 네가 그 건방진 영국 놈을 죽였으니 그게 가장 중요한 일이지. 여기 보상금 10만 페소다. 이제 '미라주'는 내가 가져가겠다, 이 배는 영국으로 돌려보낼 거다.";
			link.l1 = "이런 젠장?! 저 배 참 멋진데, 내가 가지고 있으려고 했단 말이야!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "훌륭하오! 자네는 정말 유능한 사람이로군. 우리 모든 선장들이 자네 같았다면, 네덜란드 공화국이 역사상 가장 위대한 해양 국가들 중 으뜸이 되었을 것이오. 여기 보상금 10만 페소와, 항해일지에 대한 추가금 5만 페소를 주겠소. 이제 '미라주'는 내가 가져가겠네; 이 배는 영국에 돌려보낼 것이오.";
			link.l1 = "이런 젠장?! 저 배 정말 멋진데, 내가 갖고 싶었단 말이야!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "내 아들아, 너는 훌륭한 군인이지만, 정치 문제에 있어서는 내 경험과 말을 믿거라. 내가 플리트우드에 대해 뭐라고 했는지 기억하지? 나는 그의 이름과 명성을 맷돌에 박아 깊은 바다에 던져버릴 생각이다. 그리고 포트 로열에서 온 저 오만한 귀족들은 이를 삼키고 목이 막히게 될 거다.\n우리는 리처드 플리트우드를 '유령선' 미라주의 선장으로 만들 것이다. 그는 잉글랜드와 네덜란드, 두 나라를 서로 이간질하며 약탈하고, 약탈하고, 양국의 평화로운 시민들을 죽이며 자기 배만 불리는 늑대인간이 되는 거지! 이 얼마나 가증스러운 일인가! 나는 이미 증거와 증인들을 준비해 두었지만, '미라주'가 내 완벽한 연극의 하이라이트가 될 것이다.";
			link.l1 = "그래, 젠장할. 내 훌륭한 배를 네 계획 때문에 희생시키겠다는 거냐!?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "말조심해라, 꼬마야. 지금은 전쟁 중이다. 때로는 정치적 목적을 이루기 위해 사람뿐만 아니라 배와 부유한 식민지까지 희생해야 할 때가 있지. 전쟁에는 항상 손실이 따르는 법이다... 손실 얘기가 나와서 말인데, 안타까운 소식이 있네.\n자네가 없는 사이에 윌렘스타드가 영국 사략선들에게 공격당했네. 요새가 간신히 그들을 쫓아냈지만, 그 전에 그놈들이 화공선을 몰고 항구까지 들어왔지.\n자네 배가 정박 중에 불에 휩싸여 물가까지 다 타버렸네. 완전히 잃은 셈이야.";
			link.l1 = "나리, 지금 장난하는 겁니까? 젠장, 다 말아먹었군! 이제 어쩌란 말이오?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "그렇게 화내지 마시오, 카피텐. 좋은 소식도 있소. 당신의 분노를 달래기 위해 내 '아름다운 바람', 즉 '메이펑'이라는 제벡선을 드리겠소. 합리적인 범위 내에서 마음껏 사용하시오. 그리고 내일 총독 관저에서 나를 만나시오. 당신은 네덜란드 공화국과 서인도 회사의 감사와 함께 국가 포상 후보로 지명되었소. 상을 받을 때까지는 마을을 떠나지 마시오, 카피텐.";
			link.l1 = "그 덕분에 내 손해가 좀 덜 아프군. 영광이오. 그런데, 나리, 롱웨이는 어디로 갔소?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "내가 롱웨이에게 도미니카로 항해하라고 명령하자마자 그가 갑자기 사라졌소. 영국 첩자들이 그를 덮쳤을지도 모르지... 아니면 아닐 수도 있고. 내가 조사 중이오.";
			link.l1 = "알겠소. 도미니카에서 그의 도움이 있었다면 정말 든든했을 텐데. 플리트우드와 그의 '발키리'는 정말 무서운 한 쌍이었지. 롱웨이가 아직 살아 있길 바라오... 토트 지엔스, 마인헤르!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			AddDialogExitQuestFunction("GollandGambit_AwardFromLucas_1");
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "너는 그냥 평범한 어릿광대가 아니라, 아예 서커스 전체구나. 우리가 마지막 공연까지 거의 다 왔는데 네가 다 망쳐놨지... 플리트우드를 제거하면 3만 페소를 주겠다. 더 이상 맡길 일도 없고, 우리 거래도 끝이다. 나가라.";
			link.l1 = "원하시는 대로 하겠습니다.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "안타까운 소식을 전해야겠소.\n당신이 없는 사이에 윌렘스타트가 영국 사략선들에게 공격을 받았소. 요새가 그들을 쫓아내긴 했지만, 그 전에 그놈들이 화공선을 몰고 항구까지 들어왔지.\n당신의 배가 정박 중에 불길에 휩싸여 완전히 불타버렸소. 완전한 손실이오.";
			link.l1 = "그럼 난 그냥 혼자 엿이나 먹으러 가지! 고맙다, 아무 쓸모도 없네!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Kapitein "+GetFullName(pchar)+"! 위험한 국가 범죄자 리처드 플리트우드를 제거하고, 공화국을 향한 영국의 배신 음모를 폭로했으며, 용기와 담력을 보여준 공로로 네덜란드 공화국을 대표하여 황금 두블론 1,000개를 수여하오!\n또한 모든 해군 장교의 꿈인 이 귀중한 항해 도구도 받게 될 것이오.";
			link.l1 = "공화국을 위해 봉사하게 되어 기쁩니다!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "다시 한 번 축하하네, 친구. 그리고 제발, 일주일 후에 나를 찾아오게. 아주 민감한 일로 자네의 도움이 필요하네.";
			link.l1 = "알겠습니다, 로덴부르흐 나리. 일주일 후에 다시 찾아뵙겠습니다.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "이야기 하나 들려주지. 네가 맡을 다음 임무가 얼마나 민감한지 이해하는 데 도움이 될 거야. 몇 달 전, 영국 국기를 단 플라이트 한 척이 윌렘스타드로 향하던 중 고(故) 야콥 판 베르크에게 습격당했지. 그는 그 배를 빼앗아 우리 지도에는 없는 어떤 섬 근처에서 침몰시켰어. 플라이트에 타고 있던 승객 중 단 두 명만 살아남았지. 솔로몬 슈네우르라는 유대인과 그의 딸 아비가일이야. 나머지 가족을 포함한 다른 승객들은 모두 목숨을 잃었어. 우리 두 유대인은 난파선 잔해를 붙잡고 섬에 도착했지\n솔로몬은 가족의 금이 가득 든 궤짝까지 질질 끌고 갔더군. 참 알뜰한 사람이야. 여기 또 다른 인물, 리처드 플리트우드가 근처를 항해하다가 전투 소리를 들었어. 그는 판 베르크를 잡기엔 너무 늦게 도착했고, '미라주'는 도망쳤지. 플리트우드는 혹시 생존자가 있을까 싶어 그 섬을 확인하기로 했어\n그는 솔로몬과 아비가일을 그 무인도에서 확실한 죽음에서 구해냈지. 불행하게도, 늙은 유대인 솔로몬은 선원의 눈썰미가 없었어. 그는 리처드의 '발키리'를 야콥의 '미라주'로 착각했고, 해적이 마무리하러 돌아온 줄 알고 겁에 질려 금을 어딘가에 숨겼지. 그 결과, 그는 딸과 함께 한 푼도 없이 여기 도착했고, 플리트우드가 원래 목적지인 윌렘스타드 근처 블랑카 라군에 내려주었어\n솔로몬이 이 이야기를 내게 해줬지. 네덜란드 공화국은 종교의 자유로운 신앙을 지지해. 그 정책의 일환으로 회사도 이곳 유대인 공동체를 지원하지. 그래서 내가 그들에게 지붕과 먹을 것, 입을 것을 마련해줬어. 난 그 집에 자주 들렀지. 아비가일은... 참 특별한 아가씨야. 진실하고 믿음이 깊지\n거짓말하지 않겠네, 선장. 나는 그녀를 원하고, 내 아내로 삼을 생각이야. 그녀도 나를 사랑하지만, 우리 사이에 뭔가가 끼어들었지.";
			link.l1 = "장인어른께서 이방인 사위를 별로 달가워하지 않으시나?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "하! 내가 아비가일과 결혼만 한다면, 솔로몬 영감은 사위가 할례를 받았든 아니든 그저 황홀해할 거야. 사실 그 양반이 오히려 아비가일에게 내 청혼을 받아들이라고 재촉하고 있지. 아니, 아니, 이건 유대인과 이방인의 문제를 넘어선 일이야. 자네에게 부탁하네, 내 문제를 좀 해결해주게. 아비가일과 이야기해서 뭐가 문제인지 알아봐주게\n자네는 이곳에선 낯선 사람이니, 아비가일이 그 수줍은 성격 때문에 익숙한 이들에게는 절대 말하지 않을 이야기도 자네에게는 털어놓을지 몰라. 쉬네우르의 집은 회사 사무실을 등지고 서면 오른쪽에 있네. 자네 말재주가 뛰어나다는 건 잘 알고 있지\n하지만 한 가지만 명심하게. 리처드 플리트우드가 바로 '유령선'의 진짜 선장이었다는 사실을... 아비가일과 이야기할 때 이 점을 꼭 기억하게.";
			link.l1 = "하! 물론 기억하지, 로덴부르크 나리. 그건 공식적으로 인정된 사실 아니오? 그럼 시간 낭비하지 않겠소, 곧장 당신의 연인에게 찾아가겠소.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "정말 솔로몬이 금을 숨긴 섬을 찾았단 말이오? 훌륭하군! 이제 그대라면 어떤 일이든 해낼 수 있을 것 같다고 생각하기 시작했소... 그 보물에서 다른 것도 발견했소?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "아니, 더는 없어. 돈뿐이야.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "재미있는 물건이 있었어. 옥으로 만든 해골이었지. 내가 그걸 솔로몬에게 줬더니, 자기 집안의 가보라고 하더군. 그리고 자네가 그걸 사려고 했다는 말도 하던데...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "흠. 좋아. 하지만 참 이상하군. 뭐, 됐다... 내가 자네에게 신세를 졌으니, 절대 잊지 않겠네. 자네를 위해 보상을 준비해 두었지 - 5만 페소와 이 부적이네. 이제 모두 자네 것이야.";
			link.l1 = "감사합니다, 로덴부르흐 나리!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "훌륭하오! 그래, 나는 이 유물을 솔로몬에게서 살 생각이오. 그에게는 필요 없는 물건이고, 나에게는 이걸 아주 후하게 사줄 손님이 있지. 자네를 위해 보상도 준비했네 - 5만 페소와 이 부적이네. 이제 이것은 자네 것이오.";
			link.l1 = "감사합니다, 로덴부르크 나리!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "지금은 너 같은 카피텐에게 맡길 만한 일이 없어. 하지만 쿠라사오를 너무 오래 비우지 마라, 곧 네 도움이 다시 필요할 테니.";
			link.l1 = "알겠소, 나리. 안녕히 가시오!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Have you heard the latest news? Mynheer Rodenburg is going to marry Abigail Shneur, the beautiful daughter of the old crazy Jew Solomon. What can I say, she is a lucky girl. God willing, she'll be baptized a true Christian before the wedding!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "하, 그게 다라고? 정말 어이없군... 여인네답지. 내 말 좀 들어라, 이 친구야, 이 문제는 쉽게 해결할 수 있다. 내가 솔로몬의 은닉금이 얼마였는지 안다네: 20만 페소지. 나와 아비게일의 행복을 위해 이 돈을 기꺼이 내놓겠네. 내가 자네에게 돈을 줄 테니, 자네는 쿠라사오를 일주일이나 이주일 정도 떠나 있게. 그 후 솔로몬에게 돌아가서 돈을 건네주게. 자네가 은닉금을 찾아냈다고 가장하는 거지. 이리도 배부르고, 양도 무사하겠지. 자, 필요한 돈을 가져가게.";
			link.l1 = "좋고 간단한 계획이군. 하자.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "열린 바다로 나가서 열흘 뒤에 내게 돌아오시오. 가서 쓸모 있는 일이나 하시오. 망가 로사를 찾아보든, 재료를 만들든, 뭐라도 하시오.";
			link.l1 = "무엇이든 말씀대로 하겠습니다, Rodenburg 나리.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "훌륭하오! 이번에도 완벽하게 일을 해냈구려. 내가 자네에게 신세를 졌소, 나리. 결코 잊지 않겠소. 자네를 위해 보상을 준비했네 – 5만 페소와 이 부적이오. 이제 자네 것이오.";
			link.l1 = "감사합니다, 로덴부르크 나리!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "그래, 바로 그렇소. 친구여, 때로는 누가 진짜 친구고 누가 적인지 구분하기가 어렵지. 가장 가까운 동료가 어느새 원수가 되어버리는 것도 눈치채지 못할 때가 있소. 우리 둘 다 아는 세인트 존스 출신 존 머독, 혹은 요한 판 메르덴이라고도 불리는 자는, 원래 회사의 첩자였으나 지금은 영국 해군에 몸을 팔았소.\n그 자의 최근 임무는 회사에서 가장 촉망받는 인재 중 한 명을 제거하는 것인데... 바로 그게 자네요.";
			link.l1 = "과찬이십니다. 말씀해 주셔서 다행이군요, 아니었으면 전혀 예상 못 했을 테니까요.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "정확히 그렇소, 카피테인. 그 자는 교활한 놈이오. 그 개자식을 찾아서 놈이 먼저 치기 전에 죽이시오. 앤티가로 항해해 그의 약방으로 통하는 비밀 입구를 찾으시오.\n교회 앞에 비밀 통로로 이어지는 해치가 있소. 그걸 사용하시오.";
			link.l1 = "내가 처리하겠다.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "한 가지 더 있소, 카피타인. 요한이 죽으면, 그의 시체와 집, 그리고 지하실까지 샅샅이 뒤지시오. 그자는 기록 보관소를 가지고 있소—회사에서 일할 때 치명적인 메모들을 적어둔 두꺼운 장부가 있지. 이 정보가 적의 손에 들어가면 우리 모두가 파멸할 것이오.\n저주받은 그 기록 보관소를 찾아서 내게 가져오면 추가 보수를 주겠소. 이제 가시오. 신의 가호가 있기를, 카피타인 "+pchar.name+", 그리고 살아서 돌아오도록 하시오. 공화국이 그대를 필요로 하오!";
			link.l1 = "약속드리오, 나리. 반드시 무사히 돌아오겠소. 그게 내게도 가장 이익이 되니까!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "훌륭합니다, 선장님! 정말 기쁩니다, 진심으로요. 그의 기록 보관소를 찾으셨습니까?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "예, 여기 있습니다. 약사의 시체나 그의 상자들에서는 다른 문서는 없었습니다.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "아니. 여기저기 다 찾아봤지만 아무것도 못 찾았어.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "정말 아쉽긴 하지만, 나는 괜찮소. 요한이 그걸 영국 놈들에게 넘길 시간은 없었을 거라 확신하오. 그렇지 않았다면 우리 목에 이미 올가미가 걸렸겠지... 아마도 어디 비밀 은닉처에 숨겨놨을 거요... 영원히 거기 머물게 두시오! 임무를 성공적으로 마친 걸 축하하오, 카피텐!";
			link.l1 = "감사하오!";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "훌륭하오! 이제 그것은 마땅히 있어야 할 곳에 안전하게 돌아왔소. 자네가 다시 한 번 최고의 실력을 증명했구려... 책을 주시오... 기록 보관소에 대한 보상으로 이 훌륭한 머스킷을 주겠소. 이 총은 내게 큰 공을 세웠으니, 이제 자네 것이오!";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "무슨 꿍꿍이요, 선장? 몇 장이 빠져 있소. 내게 아주 중요한 쪽지들이오. 내가 모를 줄 알고 나를 함정에 빠뜨리려 했소? 아니면 더 큰 이득을 보려고 했던 거요? 유감이오만, 둘 다 헛수고였소.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(믿을 만함) 사과드리오. 내 유일한 잘못은 미리 직접 기록 보관소를 확인하지 않은 것이었소.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "내가 정말로 페이지를 찢어내고 아무렇지 않은 얼굴로 기록물을 넘길 것 같소?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "탐욕, 어리석음, 그리고 뻔뻔함이 때로는 사람들을 가장 미친 짓으로 내모는 법이지요, 선장.";
			link.l1 = "저 셋 중 누구도 나를 움직이게 하진 않았소, 분명히 말하오.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "그러니까, 반 메르덴이 그 페이지들을 떼어내서 다른 곳에 숨겼다는 말이오?";
			link.l1 = "정확합니다. 원하신다면 제가 다시 돌아가서 그들을 찾아볼 수도 있습니다—약국 전체를 샅샅이 뒤지거나, 아니면 세인트 존스 전체를 뒤집어 놓을 수도 있지요—필요하다 생각하신다면요.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "필요 없습니다, 나리. 중요한 건 대부분 여기 있으니, 빠진 쪽지가 없으면 나머지는 나에게 위협이 되지 않소.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "그러니까, 부정직하거나 숨기는 의도가 있어서가 아니라 그냥 무관심하거나 궁금하지 않아서란 말이오? 자네가 처음 발견했을 때도 이미 이랬다고 생각하나?";
			link.l1 = "아마도 로덴부르흐 나리일 거요. 어쩌면 반 메르덴이 미리 그 쪽지를 뜯어냈을 수도 있지. ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "어쩌면 그게 더 나을지도 모르지. 그 페이지들이 없다면, 나머지 기록물은 내게 아무런 위협도 되지 않아 – 특히 무지한 자들의 손에 있다면 말이야.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "기록 보관소에 대한 보상으로 이 훌륭한 머스킷을 주겠네. 나에게 큰 공을 세운 무기인데, 이제 자네 것이오!";
			link.l1 = "감사합니다!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "우린 잘 해냈소, 그대와 나, 카피텐. 이 모든 일이 그대 없이는 일어나지 않았을 거라는 말이 결코 과장이 아니오. 앞으로도 공화국을 위해 계속 봉사한다면, 경이로운 성공을 거둘 것이며, 어쩌면 귀족 작위까지 받을 수 있을 것이오.";
			link.l1 = "이제 작별이군요, 로덴부르흐 나리.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "이제 작별이오, "+pchar.name+". 여기서 내가 원하던 모든 일을 마쳤으니, 일주일 후에 고향 암스테르담으로 떠날 것이오. 내 새 아내 아비게일과 장인 솔로몬도 함께하오. 피터 스토이베산트가 이미 새로운 회사 부국장을 찾았으니, 필요한 일이 있으면 그와 상의하시오\n그대의 공로에 대한 보답으로 메이펑을 주겠소. 이제 그 배는 그대의 것이오, 카피텐, 그대가 받을 자격이 있소.";
			link.l1 = "감사합니다, 로덴부르크 나리. 저는 메이펑에 꽤 정이 들었고, 이미 제 배처럼 여기기 시작했습니다.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "이제 나를 좀 내버려 두어야겠구나, 자네. 출항 전에 해야 할 일이 많네... 언젠가 암스테르담에서 나를 찾아오게! 술 한잔 나누며 옛 시절을 추억하세나...\n";
			link.l1 = "예, 나리. 새 삶에서 모두가 행복하고 번영하길 바랍니다! 안녕히 계십시오!";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "그래, 나리. 새 삶에서 모두 행복하고 번창하길 바라오!\n(이를 악물고) ... 다시는 안 봤으면 좋겠군, 이 오만한 자식아. '얌전한' 유대인 악처와 결혼한 기쁨이 어떤 건지 곧 알게 될 테니 두고 봐.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "하느님 맙소사! 플리트우드의 개 자식! 오늘은 네가 이길지 몰라도, 루카스 로덴부르크는 쉽게 죽지 않을 거다.";
			link.l1 = "그럴 생각 없다. 공짜로 목숨 내놓게 될 거다, 이 네덜란드 구두쇠야.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "지옥 깊은 곳에서 네 입에 똥을 싸주마! 방금 화물창에 불을 질렀으니 곧 화약고까지 번질 거다! 우리 배들은 서로 바짝 붙어 있어서 도망칠 희망도 없어! 불타 죽든가 상어 밥이 되든가 해라!";
			link.l1 = "젠장! 물러서라, 놈들아, 후퇴해야 한다!";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "네 영혼이 몸을 떠날 때까지 나는 안 떠난다. 가만히 있어, 아플 거다.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "여기 왜 왔냐, 이 자식아? 날 조롱하러 온 거냐? 이제야 네가 이 연극에서 무슨 역할인지 말해줄 생각이냐? 브리건틴을 잡은 것도 너였지? 처음부터 이게 네 계획이었냐?";
			link.l1 = "나는 전갈을 전하러 왔소, 루카스 로덴부르크. 네가 배신한 존 머독이 안부를 전하라고 했지. 너는 내 임무였고, 나는 그 임무를 완수했다. 그럼 이만.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "요한? 하하! 결국 이 모든 일의 배후가 그 자였군! 그 늙은 악당 놈! 하지만 게임은 아직 끝나지 않았다. 야콥 판 베르크가 널 잡으러 오고 있어, 넌 절대 도망칠 수 없어! 너와 네 배는 이제 끝장이야, 한심한 바다 거지 녀석아!";
			link.l1 = "목매다는 재판에서 변명이나 하시지, 로덴부르크.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
