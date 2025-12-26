// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("헤헤, 선장님, 지금 주둔군 절반이 선장님을 쫓고 있어요. 지금이 선장님 배에 들어갈 때는 아닌 것 같은데요!","배까지 싸우면서 돌파하자고? 아니, 선장, 그건 다음에 하자...");
				link.l1 = RandPhraseSimple("원하시는 대로...","사실, 너를 고용할 생각은 없었어."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "선장님, 장교가 필요하십니까?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "장교라고? 그래서 뭐 잘하는데?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "아니, 난 이미 다 갖췄어.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "선장님, 뭐 하십니까? 큰일 나기 전에 무기를 거두십시오!";
			link.l1 = LinkRandPhrase("좋아.","좋아.","걱정 마, 내가 치우고 있어...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "오늘, 드디어 출항한다!";
				link.l2 = "그래... 나도 기뻐.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "내 술만 다 마시고 갈게, 선장. 그다음에 배로 가겠어. 걱정 마, 제때 도착할 테니까.";
				Link.l1 = "좋아. 늦으면 갑판 청소 시킬 거야!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "무슨 일이오, 선장?";
			// эпилог -->
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers") && npchar.id == "Folke")
			{
				dialog.text = "이 날씨는 마음에 안 들어요, 선장님. 폭풍이 올 징조를 봤어요.";
				Link.l1 = ""+npchar.name+"님, 드릴 말씀이 있어요. 솔직히 말하자면, 저는 유럽으로 떠납니다. 언제 돌아올지는 정해지지 않았어요. 당신을 여기 남겨두고 기다리게 하는 건 어리석은 일이지만, 모두를 데려갈 수도 없어요. 저는 다른 배에 승객으로 타고 떠나요.";
				Link.l1.go = "SharlieEpilog_Folke_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers") && npchar.id == "Duran")
			{
				dialog.text = "(하품) 지루하군...";
				Link.l1 = "요즘 재미없는 날이 계속됐지, "+npchar.name+"?";
				Link.l1.go = "SharlieEpilog_Duran_1";
				break;
			}
			// эпилог <--
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "당신에게 몇 가지 명령을 내려야겠소.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", 나는 오래된 인디언 마을 타야살로 갈 거야. 이번 여정은 위험하고 특별할 거야 - 순간이동 우상을 통해서지. 같이 갈래?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", 너에게 진지한 부탁이 있어. 진짜 거래지, 목숨을 거는 일이지만 엄청나게 이득이 될 거야. 고대 인디언 도시로 가는 임무에 충직한 사람이 필요해. 같이 할래?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "클로드, 너 예전에 용병들은 박봉이라고 불평했지.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "이제 내 명령을 들어라!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "배에 대한 종합 보고서를 제출하시오, "+GetStrSmallRegister(XI_ConvertString("재무관"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "우리가 식민지에 머무는 동안 물자를 구입해 주었으면 한다.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "있잖아, 이제 더 이상 식민지에서 물건을 살 필요 없어.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "장교, 이제 네 도움이 더는 필요 없다.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "이 마을의 대리로 임명하겠소!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "아무것도 아니다. 편히 있어라!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "젠장, 선장! 난 네가 기회만 생기면 날 내칠 줄 알았는데, 역시 또 날 놀라게 하는군. 물론 난 네 편이지, 그리고 이 멍청이에게 진짜 바다늑대의 삶을 안겨줘서 고맙다!";
				Link.l1 = "잘했어, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "어? 내가 정말 그렇게 말했나?";
				Link.l1 = "네가 그랬지. 그때 네 말을 주의 깊게 들었고, 이제 그 부당함을 바로잡을 준비가 됐어.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("미안해, 선장. 하지만 내가 동의한 건 이게 아니야. 내가 겁쟁이라고 생각하진 마. 하지만 확실한 죽음을 맞이하러 갈 생각은 없어. 아직은 이렇게 살기 싫을 정도로 지치진 않았거든. 원하면 나를 해고해도 돼.","선장님, 실례를 무릅쓰고 말씀드리지만, 안 됩니다. 바다에서 싸우고, 적 도시를 습격하는 건 괜찮지만, 그 인디언 주술에는 관여하고 싶지 않습니다. 제 대답이 마음에 들지 않으시면 계약을 파기하셔도 됩니다.","불가능한 걸 원하시는군요, 선장님, 그리고 그건 본인도 잘 아실 텐데요. 아무도 살아 돌아오지 못할 겁니다, 선장님도 마찬가지고요. 난 사양하겠소. 내 거절이 계약 조건 위반이라 생각된다면, 계약을 파기하셔도 됩니다.");
			link.l1 = LinkRandPhrase("그대를 탓하지 않네, 장교. 나는 충분히 이해하고 있소.","안타깝지만, 이해하오. 그래서 미리 말씀드린 것이오.","나는 자네를 믿고 있었네... 하지만 자네 입장도 이해하네, 장교.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "헤! 그럼 내 봉급 올려줄 건가?";
			Link.l1 = "말도 안 돼! 나는 고대 인디언 도시로 가는 중이야. 그 일은 목숨을 거는 짓이지만, 거기엔 금이 있을 거야...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "나는 금에는 관심 없어. 네가 예전에 나를 도와줬으니, 이번엔 내가 너를 도와주는 게 영광이지, 선장. 언제 출발할까?";
			Link.l1 = "잘 말했다, Claude! 완전히 준비해 둬라 - 이제 곧이니.";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "선장님, 무슨 화물이요? 우선 배부터 구해야 합니다!";
				Link.l1 = "그래, 네 말이 맞아.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "그렇게 하겠습니다, "+GetSexPhrase("나리","아가씨")+" 선장님!";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "그렇게 하겠습니다, "+GetSexPhrase("나리","아가씨")+" 선장님!";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("선장님, 있잖아요, 저... 음, 저를 그만두게 해주셨으면 합니다. 이제는 정착해서 결혼도 하고 아이도 낳고 싶습니다. 아직 제 집도 없고요. 나이 들면 물 한 잔 떠다줄 사람도 없을 것 같아요.","선장님, 제발 저를 그만두게 해주십시오. 수년 동안 전 세계를 떠돌았지만, 아직도 제대로 본 게 없는 것 같습니다. 이제는 새로운 삶을 살고 싶고, 닻을 내리고 세상을 다른 시각으로 바라보고 싶습니다.","선장님, 해군 복무도 분명 멋진 일이죠. 이익도 많고 모험도 있지만, 이제 저 자신을 생각할 때가 온 것 같습니다. 아시잖아요, 조용한 항구에 닻을 내리고, 집도 사고, 자식도 두고 싶습니다. 제발, 저를 보내주십시오."),LinkRandPhrase("선장님, 있잖아요, 정말 죄송하지만, 저는 이 모든 임무와 감시, 그리고 규율에 진절머리가 났어요. 그냥 잠시라도 자유롭게 살고 싶을 뿐인데, 선장님께서 저를 기다려주지 않으실 거란 것도 알아요, 그래서... 저를 제대시켜 주실 수 있겠습니까?","선장님, 있잖아요... 제가 살 수 있는 작은 배가 있어서요, 이제 제 사업을 시작할 때가 된 것 같습니다. 제발, 저를 떠나게 해주실 수 있겠습니까?","선장님, 방금 항구에서 일자리를 제안받았습니다. 사실, 한동안 닻을 내리고 결혼해서 정착하는 삶을 오래도록 꿈꿔왔습니다. 제발, 가게 해주십시오. 이런 기회를 놓칠 수는 없습니다."),LinkRandPhrase("선장님, 저 정말 뱃멀미가 심합니다. 의사들은 계속 저만의 특이체질이라고만 하네요. 제발, 신의 이름으로 부탁드리니 저를 풀어주십시오. 아니면 언젠가 그냥 바다에 뛰어들고 말 겁니다.","선장님, 이제는 정착해서 좀 더 조용한 곳을 찾아야 할 것 같습니다.\n알다시피, 저는 두렵습니다. 어딘가에서 날아오는 총알도, 백병전 중에 죽는 것도 무섭습니다.\n살아남게 해달라고 주님께 기도하지만, 눈을 감으면 제가 죽인 무고한 영혼들이 떠오릅니다.\n그들은 저에게 살려달라고 애원합니다...\n부디 자비를 베풀어 저를 놓아주십시오.","선장님, 오래된 상처들이 쑤시고, 최근에 입은 타박상도 매일 저를 괴롭힙니다.\n곧 저를 내보내실 텐데, 그 다음엔 누가 저를 써주겠습니까?\n부디 저를 보내주십시오. 제가 직접 치료하고 좀 더 조용한 곳을 찾아보겠습니다."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("결국 모두 떠나게 마련이지. 좋아, 가도 된다.","그대의 생각은 이해하네. 모든 것은 언젠가 끝이 오지. 자, 가게... 내가 혹시라도 기분을 상하게 했다면 원망하지 말게나.","또 이러는 거야? 일부러 가장 곤란한 순간에 나를 떠나기로 한 거지? 뭐, 됐다. 잘 가라."),LinkRandPhrase("네가 하는 말을 믿기 힘들군... 좋아, 짐 챙기고 가.","너였어? 이럴 줄은 몰랐는데... 그 오랜 시간 함께 등을 맞대고 싸웠는데... 뭐, 널 막진 않겠다. 행운을 빈다.","진지하게 들리는군. 아무튼 행운을 빌고, 내가 너를 그리워할 거라는 걸 알아둬."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("알겠군... 그런 거였어? 나는 너를 믿고 있었는데... 뭐, 이미 결심했다면 여기서 갈라서자. 가져가라\n "+sti(NPChar.rank)*250+" 충성스러운 봉사에 대한 페소다. 그리고 내가 혹시라도 너를 불쾌하게 했다면 원망하지 마라.","글쎄, 나는 원한도 없고, 잘못도 기억하지 않아. 그게 네가 내린 결정이라면, 가. 그리고 가져가라\n "+sti(NPChar.rank)*250+" 페소가 있으면 새 출발하는 데 확실히 도움이 될 거야.","알겠네... 뭐, 언젠가는 그렇게 될 운명이었지. 내가 자네에게 주겠네 "+sti(NPChar.rank)*250+" 네 목숨 값을 치를 페소다. 그리고 건강도 챙겨라, 해군 복무는 고생이 많으니..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("그래서 그렇게 말하는 거야... 지금 떠난다는 건 나를 배신하는 거라는 걸 모르겠어? 지금은 널 보낼 수 없어, 생각도 하지 마.","이거야말로 소식이군! 이런 일은 미리 나한테 알려야 하는 거 알지! 그러니 당분간 사생활은 잊어버려. 때가 되면 내가 은퇴하라고 알려줄 테니까.","사직은 없다. 모두 인원 파악되어 있다. 각자의 사정만으로 모두를 내보낼 수는 없다. 내가 휴가를 줄 자격이 있는지 고민하는 동안 복무하라.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "감사합니다, 선장님! 이런 뜻밖의 관대함이라니... 있잖아요, 아직도 선장님의 물건 몇 가지가 제게 남아 있는데, 혹시 돌려받고 싶으신가요?";
			Link.l1 = "아마도... 요즘은 좋은 칼을 구하기가 쉽지 않지.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "아, 신경 쓰지 마시오. 그건 당신의 봉사의 기념으로 간직하시오.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("하지만 어찌 그런가요, 선장님? 노예들조차 결국에는 육지로 보내지지 않습니까. 그리고 저는 노예가 아니니 제 운명은 제가 직접 결정할 수 있습니다!","선장님, 저는 지금까지 충실히 당신을 섬겨왔습니다. 이제 제 운명만큼은 제가 스스로 결정할 권리를 얻은 것 아닙니까?");
			Link.l1 = LinkRandPhrase("보아하니 지금 상태로는 너를 붙잡아 둘 수 없겠군. 좋아, 그럼 금전적인 지원은 어떤가? 손해 볼 일은 없지. 그 돈으로 조용한 항구에 아늑한 집을 짓거나 건강을 챙기는 데 쓸 수 있을 거야.","좋아, 이렇게 해보자. 얼마를 주면 네 결정을 바꿀 수 있을까?","맞는 말이야. 하지만 일회성 금전 지원을 해주면 생각이 바뀔까?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("오, 아니야, 친구, 그건 네가 잘못 알고 있는 거야... 네가 선술집에서 술 마시고 여자나 쫓으며 시간을 허비할 때는 네 마음대로 할 수 있었지. 하지만 내 배에 올라탄 순간부터 네 운명은 내 손에 맡겨진 거야.","흠. 그거 참 심각한 말이군. 네가 어떻게 내게 발견됐는지 잊었나 본데, 주머니에 동전 한 푼 없이 썩은 선술집에 처박혀 있었잖아. 금화 한 닢도 보여줄 수가 없어, 바로 럼주로 바꿔버릴 테니까. '내 운명을 결정해라...' 푸하! 웃기는 소리 하지 마!"),LinkRandPhrase("내가 시키는 동안에는 내가 결정한다. 이제, 더 이상 내 화를 돋우기 전에 네 임무로 돌아가 주겠나!","흠. 그거 참 심각한 말이군. 하지만 아직 선불로 준 돈을 다 갚지 않았잖아. 그러니 네 행동은 갈취 시도로 볼 수 있겠지, 안 그래?","아, 그렇군... 다시 한 번 배의 규칙이 뭐라고 되어 있더라? 여기, 2항을 보자: '허락 없이 떠나려는 자는 화약 한 자루, 물 한 병, 권총 한 자루, 그리고 탄환 한 발만 들려 무인 해안에 내리게 한다.' 자, 이런 처분을 받고 싶나?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("글쎄, 그건 또 다른 이야기지. "+sti(NPChar.rank)*500+" 페소를 즉시 주면, 내가 너와 함께 있지.","글쎄, 아마도 "+sti(NPChar.rank)*500+" 페소만 있다면 머물 수도 있겠지, 아마.","글쎄, 그렇게 말한다면, "+sti(NPChar.rank)*500+" 페소만 있다면, 계속해서 봉사할 수 있겠소.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("좋아, 동의하지.","알겠어. 그래도 좀 덜 요구할 수도 있었잖아.","식욕이 대단하군! 하지만 내가 약속했지, 그리고 그 약속은 반드시 지킬 거야.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("그건 너무하군. 그 돈이면 장교 둘은 고용하겠어. 그냥 널 풀어주는 게 더 낫겠는걸.","흠, 자네 자신을 꽤 높이 평가하는군. 좋아, 풀어주지. 하지만 자유의 몸이 되면 직접 알게 될 거야, 자네 인생이 기대만큼 순탄치 않다는 걸.","나는 그만큼은 못 내겠어. 가도 좋지만, 다시 돌아올 생각은 하지 마. 나는 배신을 용서하지 않는다.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "좋아, 그렇게 말한다면 남겠어. 하지만 이렇게 하는 건 내 의지에 반하는 거라는 걸 알아둬.";
		Link.l1 = LinkRandPhrase("아주 좋소. 임무로 돌아가시오, 이 대화는 나중에 계속하겠소.","배로 돌아가라. 그리고 다음에는 은퇴를 요청하기 전에 두 번 생각해라.","그렇지. 의무는 의무이니, 아직 네 환상에 빠질 때가 아니야.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase("믿을 수가 없군! 고마워요, 선장님, 마음이 한결 가벼워졌어요.","고맙습니다, 선장님, 저를 붙잡으려 하지 않으셔서요. 있잖아요, 인생에서 다른 것도 정말 해보고 싶거든요.","헤, 이제야 내게 찾아온 자유에 익숙해져야겠군. 함대 복무가 얼마나 지긋지긋했는지 이제서야 제대로 실감하고 있어.");	
		Link.l1 = RandPhraseSimple("그래, 행운을 빌어.","이제 자유다. 네 복무는 끝났다.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("선장님, 양심에 어긋나는 짓을 하며 강도질에 가담하고 싶지 않습니다.","선장님, 더 이상 당신의 난동에 가담하고 싶지 않습니다. 저는 장교이지, 도살자가 아닙니다.","선장님, 당신의 도적 같은 방식으로는 제가 이 선원으로 남을 수 없습니다."),LinkRandPhrase("선장님, 솔직히 말씀드리자면 당신과 함께 일한 것은 실망스러운 실수였습니다. 어떤 돈을 준다 해도 제 명성을 희생할 생각은 없습니다.","선장님, 당신은 신세계에서 가장 악랄한 악당들을 모두 배에 모아 놓으셨군요. 제대로 된 사람이라면 저 놈들 쳐다보기도 역겹습니다. 이런 선원들과는 더 이상 함께 일하고 싶지 않습니다.","선장, 당신은 온통 악당들만으로 선원을 채웠군. 말 한마디 나눌 만한 제대로 된 놈이 하나도 없어. 이런 일은 정말 질색이야."))+" 안녕히 가십시오.";
			Link.l1 = "뭐?! 여긴 군함이지, 예절 학교가 아니야! 그럼 지옥이나 가라!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "나는 네가 곧 떠날 줄 알았지... 이 일은 너한테 맞지 않아. 하지만 나를 탓하지는 마라. 자, 여기 있어 "+sti(NPChar.rank)*500+" 페소야, 네 마음에 드는 일을 찾는 동안 유용하게 쓸 수 있을 거야.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("오, 이제 와서 그런 소리를 하는 거냐. 그럼 그동안 털었던 모든 약탈에서 네 몫은 어땠냐, 손에 불이라도 난 거냐? 아니면 죄를 용서받겠다고 수도원에 들어가 기도라도 할 생각이냐? 그럴 거면 우리도 좀 챙겨달라고 기도해 줘라! 하하하하하!","흠. 그거 참 심각한 말이군. 우리가 같이 상인들을 털 때 네 순수한 양심은 어디를 보고 있었지? 그걸 어떻게 깨끗이 씻을 건데? 아니면 우리를 밀고해서, 다 같이 교수대에서 멋진 동료들과 목매달리게 할 생각이야?","오, 잘했군! 네 주머니에 동전 한 푼 없이 썩은 선술집에서 내가 널 어떻게 찾아냈는지 벌써 잊은 모양이군. 참고로 말해두지, 너 같은 놈은 장교로서 구리 동전만큼의 값어치도 없어. 한마디로 쓸모없는 놈이지!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("선장, 나는 당신네 귀족들 장난이 정말 싫어. 그리고 당신 마음 편하라고 내 습관을 버릴 생각도 없어. 잘 가.","선장님, 더 이상 당신 밑에서 일할 수 없습니다. 나는 이미 너무 많은 시간을 허비했어요. 그냥 평범한 사략선장이었어도 벌써 큰돈을 벌었을 겁니다. 이제 떠나겠습니다.","선장, 당신 부하들은 정말 역겹군. 제대로 된 놈 하나 없고, 죄다 겉멋만 든 놈들뿐이야. 같이 술 한잔할 놈도 없어. 난 떠난다."),LinkRandPhrase("선장님, 저는 노련한 장교입니다만, 당신 배는 짐선처럼 보이는군요. 그런 배에서 복무하는 건 내키지 않습니다. 그럼 이만.","선장님, 당신 선원들 전부 멋만 부리고 있어. 같이 술 마시거나 얘기할 놈 하나도 없더군. 난 그런 근무는 딱 질색이야. 잘 있어.","선장님, 전에는 진짜 해적 밑에서 일한다고 생각했는데, 우리가 하는 건 자선뿐이잖아요! 더 이상 시간 낭비하고 싶지 않아요. 나 갑니다."));
			Link.l1 = RandPhraseSimple("알겠소. 당신 태도를 보니 언젠가는 그렇게 될 줄 알았지. 좋아, 더는 붙잡지 않겠소.","그런 말씀 하실 줄 알았습니다. 솔직히, 저는 꽤 오랫동안 당신의 태도에 불만이 있었어요.")+" 행운을 빌어.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "나는 네가 곧 떠날 줄 알았지... 이 일은 너와 맞지 않아. 하지만 나를 탓하지는 마라. 자, 여기 있어 "+sti(NPChar.rank)*500+" 페소인데, 새 일자리를 찾는 동안 유용하게 쓸 수 있을 거야.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("흠. 그거 꽤 심각한 말이군. 하지만 아직 선불로 준 돈을 다 갚지 않았잖아. 그러니 네 행동은 갈취 시도로 볼 수 있겠지, 맞나?","아, 그렇군... 그럼 배의 규정에는 뭐라고 되어 있지? 여기, 2항을 보게: '허락 없이 떠나려는 자는 화약 한 자루, 물 한 병, 권총 한 자루, 그리고 탄환 한 발만 들려서 무인도에 버려진다.' 이제, 자네는 그게 어떤가?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("나를 모욕하려 들지도 마! 나는 돈을 위해 일하지만, 그래도 내가 하고 싶은 일을 고를 권리는 있어!","나는 자유인이다! 그리고 내가 원할 때마다 새로운 일을 할 권리가 있다!","나는 먹을 것을 위해 일하는 노예가 아니니, 내 양심은 떳떳하다! 하지만 더 이상 약탈에는 가담하지 않겠다!");
				Link.l1 = "음, 사실 너 착각하고 있군... 네가 선술집에서 술 마실 땐 무슨 일이든 골라 할 수 있었지... 하지만 내 배에 발을 들인 순간부터 네가 돌아갈 수 있는 길은 목이 산산조각 나는 포탄뿐이야... 그리고 네 혀도 뽑아버릴 거다, 다음 세상에서 아무 말도 못 하게 말이지...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "좋아. 가도 된다... 하지만 망망대해에서 나를 다시 만나지 않길 신께 빌어라. 맹세컨대, 내 곁에 남지 않기로 한 그 순간을 뼈저리게 후회하게 될 거다.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("나를 겁주려고도 하지 마! 나는 돈을 위해 일하지만, 그래도 내가 하고 싶은 일을 고를 권리는 있어!","나는 자유인이다! 그리고 나는 원할 때마다 새 일을 맡을 권리가 있다!","나는 너의 노예가 아니야! 그리고 네 낡은 배에서 이렇게 비참하게 계속 살 생각도 없어!");
				Link.l1 = "음, 사실 너 착각하고 있군... 네가 선술집에서 술 마실 때는 원하는 일 골라잡을 수 있었지... 하지만 내 배에 발을 올리는 순간부터 네가 돌아갈 길은 목을 산산이 부수는 포탄뿐이야... 그리고 네 혀도 뽑아버릴 거다, 저승 가서 쓸데없는 소리 못 하게...";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "좋아. 가도 된다... 하지만 바다 한가운데서 나를 다시 만나게 되면, 신께 맹세코 그때 네가 내 곁에 남지 않기로 한 걸 뼈저리게 후회하게 될 거다.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("이렇게 말씀하신다면, 남겠소. 달리 선택지가 없으니. 하지만 내 의지로 하는 건 아니라는 점은 명심하시오...","좋아, 그렇게 말한다면 남겠어. 하지만 이렇게 하는 건 내 의지에 반하는 일이라는 걸 알아둬.");
			Link.l1 = RandPhraseSimple("괜찮아... 내가 놔줄 때까지 시중이나 들어.","좋아. 계속 일해라... 내가 언제 놓아줄지 결정하마.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"나는 절대 다시 생각하지 않을 거야! 나를 노예로 묶어둘 권리는 없어! 난 떠날 거니까, 가까이 오지 마, 아니면 끝장이야.","네가 베테랑 장교를 겁줄 수 있다고 생각하나?! 나는 죽음의 문턱까지 여러 번 갔던 사람이야. 그렇게 말한다면, 차라리 피비린내 나는 약탈 중에 죽는 것보다 정정당당한 전투에서 죽는 게 훨씬 낫지!");
			Link.l1 = NPCharRepPhrase(NPChar,"음... 누구나 자기 운명은 스스로 선택하지. 내게 오기 전에 기도는 했길 바란다.","술집에서 너를 데려올 때 이런 일이 벌어질 줄 알았다면, 차라리 교수대에 매달리게 놔뒀을 거다. 아직 늦지 않았으니, 그렇게 해줄 수도 있지...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"그래, 그렇게 자유가 필요하다면 떠나도 된다. 하지만 나는 아무런 추천장도 안 써줄 거다.","좋아. 가도 된다... 하지만 바다 한가운데서 나를 다시 만나게 된다면, 신의 저주가 내릴 거다. 맹세컨대, 내 곁에 남지 않기로 한 그 순간을 뼈저리게 후회하게 될 거야.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"이제 그만 겁 좀 줘! 네 졸개들 중에 누가 감히 나한테 맞서겠어? 내가 선장이었으면 지금쯤 돈방석에 앉아 있을 거다! 그렇게 자선 행세를 해놓고, 네 선원들이 내 편 들까 봐 두렵기라도 해?!","네 수작 그만둬라, 난 겁먹지 않아! 잘 가라.");
			Link.l1 = NPCharRepPhrase(NPChar,"아니, 이봐, 넌 교수대까지 살아남지 못할 거야. 그런 호사는 네 놈한텐 어울리지 않아...","그렇게 서두르지 마, 친구. 우리 아직 퉁 안 됐어. 너 나한테 빚졌잖아.");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" increased his loyalty");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"나는 최고다 "+XI_ConvertString(Npchar.quest.officertype)+" 이 바다 안에서. "+Npchar.quest.officertype_2+"그리고 나는 당신을 위해 한 가지 호의를 베풀 준비가 되어 있으며, 당신 밑에서 일할 준비도 되어 있습니다.","글쎄, 나 꽤 괜찮다는 소문이 있지 "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"나를 당신 배에 태워 보시오, 선장님, 직접 확인해 볼 수 있을 테니.");
			Link.l1 = "그래서 얼마를 원하는 거지?";
			Link.l1.go = "price";
			Link.l2 = "그대는 어떤 전문가지?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "안타깝게도, 나는 이미 하나 가지고 있어 "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("헤헤, 선장님, 지금 주둔군 절반이 선장님 뒤를 쫓고 있어요. 지금이 선장님 배에 들어갈 때는 아닌 것 같은데요!","배까지 싸우면서 돌파하자고? 아니, 선장, 그건 다음에 하자...");
				link.l1 = RandPhraseSimple("원하시는 대로...","사실, 너를 고용할 생각 없었어."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "마음이 바뀌었습니까, 선장님? 새로운 "+XI_ConvertString(Npchar.quest.officertype)+" 나쁠 건 없겠지?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "그런 셈이지. 얼마를 원하는가?";
                Link.l1.go = "price";
			}
			Link.l2 = "그래서 너는 뭘 할 수 있는데?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "나는 전부 다 갖고 있어. 또 보자.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "우리 합의할 수 있을 것 같군 "+Npchar.quest.OfficerPrice+" 페소입니다.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "우리 합의할 수 있을 것 같군 "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" 두블룬.";
			}	
			Link.l1 = "그거 좀 심한 거 아니야?";
			Link.l1.go = "trade";
			Link.l2 = "동의한다. 이제부터 넌 우리 선원이다.";
			Link.l2.go = "hire";
			Link.l3 = "너는 이 돈의 가치도 없어.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "좋아... 뭐, 나도 그 정도는 받아들일 수 있겠군 "+Npchar.quest.OfficerPrice+" 페소다. 어때?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "나도 그 점에는 동의할 수 있을 것 같군 "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" 두블론이지. 어때?";
				}
				Link.l1 = "이제야 됐군. 넌 들어왔어.";
				Link.l1.go = "hire";				
				Link.l2 = "아직도 좀 과하다고 생각해. 잘 가.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "죄송합니다, 선장님, 하지만 제가 요구한 만큼의 가치가 정확히 제 값입니다. 너무 비싸다고 생각되면 다른 사람을 찾아보시지요.";
				Link.l1 = "좋아, 동의하지. 데려가 줄게.";
				Link.l1.go = "hire";				
				Link.l2 = "그렇게 할 생각이오. 안녕히 계시오.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "돈이 부족한 것 같군, 선장! 미안하지만 외상은 안 돼.";
			Link.l1 = "오, 젠장!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "감사합니다, 선장님. 이 선택, 후회하지 않으실 겁니다.";
				Link.l1 = "그러길 바라오.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "감사합니다, 선장님. 당신의 선택을 후회하지 않을 것입니다.";
				Link.l1 = "그러길 바란다.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "술만 다 마시면 갈게, 선장님. 곧 배로 갈 테니 걱정 마시오. 제때 도착할 거요.";
			Link.l1 = "좋아. 늦으면 갑판 청소 시킬 거야!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "선장님, 하지만 배가 없으시잖아요!";
				Link.l1 = "상기시켜 줘서 고맙군...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "항해 중 쥐의 활동이 최대치임 "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"전체 화물량의 %%입니다. For "+GetCrewQuantity(PChar)+" 우리가 필요로 할 선원들 "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" 하루 식량. 이는 운송 중인 노예는 포함하지 않습니다.";
			Link.l1 = "고맙다.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "명령이 무엇입니까?";
            Link.l1 = "여기 서 있어라!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나를 따라와, 뒤처지지 마!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "목표물과 일정 거리를 유지해 주길 바라네.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "당신의 화기에 사용할 탄약 종류를 바꿔야 합니다.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "당신의 머스킷에 사용할 탄환 종류를 바꿔야 하오.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "전투를 위해 주 무기를 바꿔야겠어.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "탄약 종류를 선택하십시오:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "탄약 종류를 선택하십시오:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "전투가 시작될 때 당신이 사용할 것은 다음과 같습니다:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "정확히 어느 거리입니까, 선장님? 보폭으로 말씀해 주시되, 20보를 넘지 않게 해주십시오.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "선장님, 괜찮으십니까?";
				link.l1 = "죄송합니다, 제 실수였습니다...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "나는 여기서 꼼짝도 하지 않고 서 있겠소. 그게 당신이 원하는 건가요, 선장님?";
				link.l1 = "그래. 바로 그게 네게 요구되는 일이야.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "내가 목표물에서 20보 이상 떨어질 수 없다고 말했던 것 같은데.";
				link.l1 = "알겠어, 20미터 거리를 유지해.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "이해했고 반영하였소.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "선장님, 솔직히 말씀드려서 선장님의 의도를 잘 모르겠습니다만, 이 이야기는 육지에서 하면 안 되겠습니까? 아니면 저를 그냥 바다에 던져버릴 생각이신가요?";
					Link.l1 = "흠... 아니, 내 말은 그게 아니야. 우리가 항구에 도착할 때까지 여기 있어.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("이거 참 새롭군!","왜, 하늘에서는?","무슨 이유인데?!"),RandPhraseSimple("선장님, 미치신 겁니까? 아무 이유 없이 그런 소식을 말하다니!","이런 젠장! 내가 뭘 잘못해서 너를 불쾌하게 한 거지?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("나는 선원들에게 질서를 세우기로 했어. 그리고 네가 동료들과 맺고 있는 관계는 마음에 들지 않아.","당신의 장점이 채용 때 논의했던 것만큼 좋지 않았소. 그래서,","내 선원 중에 깡패나 불량배들은 못 남겨두지! 그러니,"),LinkRandPhrase("내가 알기로 그대가 럼주를 훔치고, 몰래 내 선원들에게 술을 권해 사기를 떨어뜨리고 있더군. 그러므로,","나는 네 도적 같은 행실에 진저리가 나서 더는 참지 않을 거다. 그러니,","당신은 계속해서 중앙 선실에서 카드나 주사위를 하며 시간을 보내고, 다른 장교들이 임무를 수행하는 데 방해가 되고 있소. 이런 일이 계속될 수는 없소. 그러니,"))+" 짐 챙겨서 배에서 내려.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("그런 결정을 내린 이유를 여쭤봐도 되겠습니까?","분명히, 그런 결정은 충분히 근거가 있군."),RandPhraseSimple("변명해 보시오, 선장","그건 정말 뜻밖이군. 하지만 그래도 이유를 알고 싶어."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("나는 네가 네 임무에 대해 보이는 태도에 전혀 만족하지 않는다.","안타깝지만, 너는 훌륭한 장교가 되지 못했고 앞으로도 될 가능성이 없어...","자네는 훌륭한 장교였고 근무도 성실했지. 하지만 이제 우리의 길은 갈라졌네. 왜 그런지 묻지 마라."),LinkRandPhrase("내가 경고했잖아, 럼주에 대한 네 집착이 널 망칠 거라고. 칼집에 칼도 제대로 못 꽂는 놈을 싸움에서 어떻게 믿겠어?","넌 형편없는 선원이자 장교야... 내 생각엔 바다보단 육지에서 더 오래 머물게 될 거다.","나는 네 자격에 만족하지 않지만, 이제야 마침내 적합한 대체자를 찾았어."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("흠... 이유를 여쭤봐도 되겠습니까?","그건 심각한 말씀인데요. 구체적으로 무엇이 불만이신지 여쭤봐도 되겠습니까?"),RandPhraseSimple("변명해 보시오, 선장.","분명히, 그런 말에는 충분한 근거가 있겠지?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("나는 당신의 자격에 전혀 만족하지 않으니, 그러므로","유감이지만, 그대는 훌륭한 장교임을 증명하지 못했소. 그래서,","네 고상한 태도에 진저리가 난다. 영원히 참아주진 않을 거야, 그러니까"),LinkRandPhrase("내가 알아낸 바로는 네가 선원들을 선동해서 불복종하게 만들고 있다더군. 내 배에서는 소란 따위 절대 용납하지 않는다! 그리고 지금까지 너를 바다에 던지지 않은 것에 대해 고마워할 필요도 없어. 그러니\n","그대의 고귀한 신념은 분명 칭찬할 만하오. 하지만 그것들은 자유로운 사략선의 무법한 삶과는 어긋나오. 그러니\n","나는 네가 네 임무에 대해 보이는 태도가 마음에 들지 않아. 그래서\n"))+" 짐 챙겨서 배에서 내려.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("선장님, 정말 이렇게 될 줄은 몰랐습니다! 무슨 일이 벌어지고 있는지 설명해 주시겠습니까?","선장님, 무슨 걱정이라도 있으십니까?!","그게 무슨 뜻입니까, 선장님?!"),RandPhraseSimple("대체 뭐야, 선장?! 어제까지만 해도 다 괜찮아 보였는데, 지금 이게 뭐야, 무슨 일이 있었던 거야?","이런 젠장! 네가 뭘 했는지 설명해 볼래?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("너는 완전 게으름뱅이에 쓸모없는 바보야, 연안선의 견습 선원조차 너보다 낫겠다. 나는 너 때문에 너무 오래 고생했어. 그러니까\n","한동안 너를 해고할까 고민했는데, 이제야 마땅한 대체자를 찾았어. 그러니\n","내가 알기로 그대가 럼주를 훔치고, 몰래 내 선원들에게 술을 권해 사기를 떨어뜨리고 있더군. 그러므로\n"),LinkRandPhrase("내가 너를 고용할 때, 함대 전체에서 최고의 장교라고 큰소리치더니, 알고 보니 그냥 빈둥거리는 놈이었군, 그래서\n","네 술버릇이 결국 화를 부를 거라고 경고했잖아. 쓸모없는 주정뱅이를 내 배에 왜 두고 있어야 하지? 그러니까\n","일을 해야 할 때 자꾸 어딘가로 사라지거나, 카드나 주사위 놀이만 하고 있군. 이게 영원히 계속될 거라 생각한 건 아니겠지? 그래서"))+" 짐을 챙겨서 배에서 내려라.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("이제 와서 그런 식으로 말하는 거냐! 좋아, 네 뜻대로 해라. 하지만 명심해라: 내가 굶어 죽게 되더라도 다시는 너한테 돌아가지 않을 거다!","솔직히, 나도 너희 귀족들 장난엔 별 관심 없어. 그러니, 잘 가라...","아, 지옥이나 가라! 네 아첨꾼들이랑이나 있어라. 영웅이라니, 웃기고 있네!"),LinkRandPhrase("사실, 나는 당신을 모시는 게 한 번도 마음에 든 적 없었어... 저건 제대로 된 배가 아니라 그냥 화물선이지. 마치 숙녀학교 같다고...","있잖아, 네 선원들 정말 지긋지긋해. 다들 멋만 부리고, 애들 같기만 하고, 진짜 사나이 하나도 없잖아...","알겠습니다, 선장님, 말씀대로 하겠습니다. 하지만 하느님만이 아시겠지요, 저는 제 일을 잘해왔으니까요..."));
			Link.l1 = "잠깐. 지금은 장교 없이 배를 떠날 수 없어. 하지만 이 이야기는 나중에 다시 하자.";
			Link.l1.go = "exit_bad";
			Link.l2 = "그럼 평안히 가시오.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "흥분하지 마. 내가 퇴직금 준비해 뒀어 - "+sti(NPChar.rank)*500+" 페소입니다. 이것으로 모든 문제가 해결되길 바랍니다.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("이봐! '배에서 내리라'니 그게 무슨 말이야?! 내가 네 맘대로 내쫓기려고 포탄 아래서 목숨 걸고 싸운 줄 알아?!","하! '배에서 내리라'고?! 내가 고양이 새끼처럼 내던져질 거라 진심으로 생각하는 거야?!","진정해, 선장. 진지한 사람들은 이런 식으로 문제를 해결하지 않아. 내가 풋내기 취급당할 줄 아나?");
			Link.l1 = "좋아, 당분간은 머물러도 된다. 하지만 내가 괜찮은 대체자를 찾을 때까지만이야.";
			Link.l1.go = "exit_bad";
			Link.l2 = "다시 말하지만, 네 임무는 끝났다. 짐을 챙겨도 된다.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "흥분하지 마. 내가 준비해 놨어 "+sti(NPChar.rank)*500+" 당신에게 페소를 주겠소. 이것으로 모든 문제가 해결되길 바라오.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("사실 여기 머물고 싶은 마음은 없어. 하지만 보상 없이 떠나지도 않을 거야!","이제 네 그 낡은 배에 절대 머물 생각은 없지만, 먼저 나한테 보상부터 해라!")+" "+sti(NPChar.rank)*1000+" 페소만 주면, 서로 모르는 사이로 해주지.";
			Link.l1 = "내가 좀 흥분했군... 부디, 내 사과를 받아주고 다시 임무로 돌아가 주시오.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "네가 항상 네 몫을 제대로 받아왔는데 무슨 돈 타령이야? 이건 내 눈엔 갈취로밖에 안 보여!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "좋아. 장비를 돌려주면, 네가 원한 것을 주겠다.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "그건 또 다른 이야기지. 잘 가라!";
			Link.l1 = "우리의 길이 다시는 교차하지 않기를 바란다.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("이것을 정신적 피해에 대한 보상으로 생각하시오. 나는 그런 대우를 절대 용납하지 않을 것이며, impudently 나를 그렇게 대하는 자는 반드시 후회하게 될 것이오!","이건 협박이 아니라, 내 시간을 이렇게 멍청하게 낭비한 데 대한 보상이야! 그리고 무슨 수를 써서라도 받아낼 거다!","너 같은 겁쟁이 밑에서 너무 많은 시간을 허비했어. 상선들을 약탈했다면 큰돈을 벌 수 있었을 텐데. 그러니 잃어버린 이익을 보상받고 싶을 뿐이야.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "좋아. 여기 네 돈이다... 이제 꺼져!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "네가 누군지 잊은 것 같군! 너 같은 멍청이가 나한테 소리치는 건 절대 용납 못 해!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "가라, 선장! 네 모습을 보여 줘!";
			Link.l1 = "신만이 아시겠지, 나는 원치 않았어!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "그건 또 다른 이야기지. 잘 가라!";
			Link.l1 = "우리의 길이 다시는 교차하지 않기를 진심으로 바란다.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("그렇다면, 결정된 거군. 안녕히 가시오, 선장. 그리고 원망은 하지 마시오...","안타깝군요, 선장님. 하지만 하느님도 아시다시피, 나는 노력했소. 안녕히 가시오.","음, 선장님, 정말 까다로우시군요! 좋아요, 행운을 빕니다."),LinkRandPhrase("안타깝군, 선장. 있잖아, 너랑 일하는 거 즐거웠어.","그래, 그런 일도 있지... 하지만 나는 원한은 없어. 잘 가라.","당신은 저에게 불공평하십니다, 선장님. 그래도 당신의 결정을 존중합니다. 안녕히 계십시오."));
			Link.l1 = "잠깐만, 마음이 바뀌었어. 이 이야기는 나중에 다시 하자.";
			Link.l1.go = "exit_good";
			Link.l2 = "기운 내. 행운을 빌어...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "잠깐만... 내가 너한테 좋은 장비를 챙겨줬잖아. 다 돌려줘, 내가 무리 전체를 챙겨줄 생각은 없으니까...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "잠깐만... 빈손으로 보내고 싶지 않아. 자, 이걸 가져가. "+sti(NPChar.rank)*500+" 페소야. 새 일자리를 찾는 동안 요긴하게 쓸 수 있을 거야.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "그래, 다 가져가라...";
			Link.l1 = "내 말 알아듣는 거지, 그렇지...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "감사합니다, 선장님! 이런 뜻밖의 관대함이라니... 있잖아요, 아직 선장님의 물건 몇 가지가 제게 남아 있는데, 혹시 돌려받고 싶으신가요?";
			Link.l1 = "어쩌면... 요즘은 좋은 칼을 구하기가 쉽지 않지...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "오, 걱정하지 마시오. 그건 당신의 봉사의 기념품으로 간직하시오.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("좋아, 원하는 대로 해. 하지만 명심해라: 내가 굶어 죽게 되더라도 다시는 너한테 돌아오지 않을 거야!","선장, 당신의 도적 같은 장사 방식은 나도 진절머리가 납니다. 이런 일은 언젠가 반드시 일어날 일이었지요. 그리고 변명할 필요도 없습니다.","그럼 네놈들 같은 살인자들이랑이나 있으라고. 제대로 된 인간이라면 네 배의 장교실엔 얼굴도 안 비출 거다. 여긴 완전 창관이구나, 신이시여 용서하소서!"),LinkRandPhrase("솔직히 말해서, 당신 밑에서 일하는 것도 마음에 들지 않았소. 당신은 죄다 악당들만 뽑아놨지, 말 한마디 제대로 나눌 만한 사람 하나 없더군.","그래, 네가 계속 그렇게 선원들한테 굴면 곧 혼자 남게 될 거고, 변명할 필요도 없어질 거야.","우리의 적대감은 서로 같으니, 그게 위안이 되는군. 잘 가라."));
			Link.l1 = "잠깐. 지금은 은퇴할 때가 아니야. 하지만 네 요구는 유효해.";
			Link.l1.go = "exit_bad";
			Link.l2 = "가, 가. 네 잔소리 없이도 난 괜찮아.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "잠깐만. 내가 줄게 "+sti(NPChar.rank)*500+" 페소야. 네가 길바닥에서 죽는 걸 보고 내가 죄책감을 느끼는 일은 없었으면 해.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("그래, 고맙다. 잘 가라...","이해해 주셔서 감사합니다. 행운을 빕니다.","이제 끝났군. 행운을 빌어...");
			Link.l1 = "내 말 알아듣는 거지, 그렇지.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("하지만 선장님, 그러면 저는 완전히 땅에 남겨지게 됩니다. 정말 저를 배에서 곧장 교구로 보내실 생각이십니까?","저에게 너무하십니다, 선장님. 하지만 제대로 보상만 해주신다면 원망하지 않겠습니다.","이게 내 전투 상처에 대한 너의 감사란 말이냐? 뭐, 금전적 보상 없이는 안 되겠군.");
			Link.l1 = "좋아, 마음이 바뀌었어. 너는 있어도 돼. 하지만 이 얘기는 나중에 다시 하자.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "아, 신경 쓰지 마. 여기 - "+sti(NPChar.rank)*500+" 페소다. 이걸로 내 배에서 보낸 시간에 대한 보상이 될 거야.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "돈은 줄게. 그래도 내 덕분에 장비 잘 챙겼으니, 이제 그 물건들 나한테 돌려주는 게 공평하겠지.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "오, 정말이야? 그런데 네 몫은 어쩌고, 그동안 꼬박꼬박 받아왔잖아?! 결국엔 이렇게 투덜대고 보너스 달라고 구걸할 줄 알았지.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "네가 그렇게 말할 줄 알았지, 하지만 내가 받을 때까지 네 장비는 돌려주지 않을 거야\n "+sti(NPChar.rank)*1000+" 페소다. 아니면 내 시체를 넘고 가져가야 할 거야!";
			Link.l1 = "좋아, 그럼 돈 가져가.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "미쳤어, 뭐야?! 공짜로 받은 걸 두고 그런 거금을 요구하다니?! 이제 보니 네 가식적인 선의보다 탐욕이 완전히 이긴 게 분명하군.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "감히 나를 모욕하지 마라! 내가 해군에서 최고는 아닐지 몰라도, 그래도 전투 장교다. 그리고 너 같은 무뢰한에게도 존중받을 거다!";
			Link.l1 = "아직 못 알아들었으면 한 번 더 말해주지. 구걸 그만해, 나한테서 아무것도 못 얻어.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "그래도 난 만족을 얻고 말겠어!";
			Link.l1 = "오, 그게 도전이란 말이지? 좋다, 네가 원한다면...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("이런 운도 지지리도 없지! 온 마음을 다해 일했건만, 연금 한 푼 못 받고 쫓겨나다니!","무슨 불운이람?! 겨우 고용됐는데 금방 쫓겨나 버렸어. 요즘엔 어느 성인한테 촛불을 켜야 할지 모르겠네...","이런 젠장! 올해만 벌써 세 번째 해고당했네, 그것도 전부 월요일에. 숙취가 있을 땐 선장님 앞에 나서지 말았어야 했나 봐."),LinkRandPhrase("그래, 원하는 대로 해. 다시는 마주치지 않기를 기도해라.","원하시는 대로 하십시오. 하지만 명심하시오, 나보다 더 나은 장교는 절대 못 찾을 것이오.","알겠습니다, 선장님, 말씀대로 하겠습니다. 하지만 하느님이 아시다시피, 저는 제 일을 잘해왔습니다..."));
			Link.l1 = "잠깐. 지금은 은퇴할 때가 아니야. 하지만 네 요구는 유효해.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("이제 꺼져. 오늘 내가 기분이 좋아서 다행인 줄 알아.","지금 당장 꺼져. 너 같은 장교는 똥으로 총알 만드는 것만큼이나 쓸모없어.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "잠깐만. 내가 줄게 "+sti(NPChar.rank)*500+" 페소지. 네가 길바닥에서 죽는 걸 보고 내가 죄책감 느끼고 싶진 않으니까.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "잠깐만... 내가 너한테 제대로 장비를 줬으니, 내 물건 돌려줘.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("아, 감사합니다, 선장님! 정말 친절하시네요...","이해해 주셔서 감사합니다. 행운을 빕니다.","이제 끝났어. 행운을 빌지...");
			Link.l1 = "행운을 빌지. 첫 번째 선술집에서 다 탕진하지 않길 바란다.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("이제 내 장비까지 가져가는 거야! 젠장, 다 집어치워! 나 낚시나 하러 갈 거야, 진짜로...","내가 완전히 털릴 작정이군. 뭐, 이제 나한테 남은 길은 하나뿐이지, 처형장으로 가는 것뿐이야...","아, 정말 고맙군! 이제 나를 털기로 했구나. 아, 이 잔인한 운명이라니... 가져가라, 가져가! 내가 뭘 할 수 있겠어...");
				Link.l1 = "지금 당장 꺼져. 네가 장교라면 똥으로 총알 만드는 거랑 다를 바 없지.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("원하시는 대로 하겠습니다, 선장님. 하지만 먼저, 제게 이것을 건네주시겠습니까? "+sti(NPChar.rank)*1000+" 페소다. 이걸로 정신적 피해에 대한 보상으로 삼으시오.","알겠어. 그래도 나는 받고 싶어 "+sti(NPChar.rank)*1000+" 내가 힘들고 성실하게 일한 대가로 주는 페소입니다.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "정말 악당이군! 좋아, 여기 네 돈이다.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "정신 나갔어?! 내가 직접 준 걸 두고 어떻게 그렇게 많은 돈을 요구할 수가 있어!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "아하! 농담이었어! 구멍 난 모자처럼 오래된 친구를 어떻게 내쫓겠어!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "좋아, 그럼 넌 아무것도 못 가져가! 내 돈 소리가 들리기 전엔 한 발짝도 안 움직일 거야!";
			Link.l1 = RandPhraseSimple("곧 내 칼날 소리가 들릴 거다!","그럼 넌 두 발 먼저 끌려 나가게 될 거다!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "이제 뭐야?! 이미 다 얘기했잖아! 다시는 네 배에 발도 들이지 않을 거야.";
			Link.l1 = RandPhraseSimple("이제 꺼져라. 어차피 별로 아쉬울 것도 없으니까.","좋아, 가라. 더는 붙잡지 않겠다.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "더 할 말 있습니까, 선장님? 우리는 이미 모든 것을 다 논의한 줄 알았는데...";
			Link.l1 = "아니, 아무것도 아니야. 그냥 작별 인사하려고 했어...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "선장님, 우리는 모든 것을 논의했고 요구사항도 밝혔습니다. 이제 와서 마음이 바뀌었다고 하실 건 아니겠지요?";
			Link.l1 = "좋아, 가봐라. 어차피 큰 손해도 아니니까.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "선장님, 또 무슨 질문이 있겠습니까? 알아두시죠, 저는 매우 불쾌하며, 돌아가고 싶은 마음도 전혀 없습니다...";
			Link.l1 = "좋아, 가라. 그렇게 네가 꼭 필요했던 건 아니니까.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "알겠어요, 선장님!";
		    Link.l1 = "쉬어.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "알겠어요, 선장님!";
		    Link.l1 = "편히 있으시오.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "선장님! 그건 영광입니다!";
            Link.l1 = "질서를 유지하고 도시를 번영시키시오. 나는 때때로 항해해 와서 관세를 거둘 것이오.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "내 마음이 바뀌었어.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "무슨 명령이십니까? 지난번에 저를 찾아오셨을 때\n "+FindRussianDaysString(iTemp)+" 전에.";
			}
			else
			{
			    dialog.Text = "명령이 무엇입니까?";
			}

            Link.l1 = "세금으로 얼마나 거둬들였소 "+NPCharSexPhrase(NPChar,"수집됨","수집됨")+" 이 시점에서?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "배에서 네가 필요하다. 도시 임무에서 해제한다.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "행운을 빕니다.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "내 기술로 나는 모을 수 있어 "+FindRussianMoneyString(iFortValue*iTax)+" 하루에. 끝. "+FindRussianDaysString(iTemp)+" I "+NPCharSexPhrase(NPChar,"수집됨","수집됨")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "모은 세금 전부를 가져가고 싶다.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "수고해 주셔서 감사합니다!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "좋아! 나도 땅만 밟고 다니는 놈은 아니거든.";
            Link.l8 = "그거 좋군.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "듣고 있소.";
			Link.l1 = "이건 승선에 관한 일이야.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "이건 당신 배에 관한 일이오.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "잠시 내 함대에서 나가서 네 운명을 스스로 개척해 보길 바란다.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "아직 아무것도 없어.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "그래서 네 소원이 뭐냐?";
			Link.l1 = "적선에 올라타지 마라. 너 자신과 선원들부터 챙겨.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "적선에 승선해 주길 바라네.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "그래서 네 소원이 뭐냐?";
			Link.l1 = "나는 네가 배에 올라탄 후에 다른 배로 바꾸지 않았으면 좋겠어. 그 배는 너무 소중하거든.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "적선에 올라타면, 배가 쓸 만하다면 네 것으로 가질 수 있다.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "예, 알겠습니다, 선장님.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "알겠습니다, 선장님.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "알겠소, 선장님.";
			Link.l1 = "편히 하시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "알겠습니다, 선장님.";
			Link.l1 = "편히 있으시오.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "선장님, 저는 당신의 함대에서 떠나지 않겠습니다. 이미 세 척의 배를 해산시키셨으니까요.";
					Link.l1 = "그래, 어쩌면 네 말이 맞을지도 모르지.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "문제없어, 선장. 어느 마을에서 만나면 되지?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "내 마음이 바뀌었어.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "선장님, 하지만 우리에게 적대적인 식민지에서는 기다릴 수 없습니다!";
				Link.l1 = "있잖아, 이런 여행들 다 잊어버려...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "선장님, 우리 선원들이 거의 없어요! 무슨 항해를 말씀하시는 거예요?!";
				Link.l1 = "맞아, 우리 선원이 정말 부족해...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "선장, 이런 항해에 필요한 식량이 배에 충분하지 않아.";
				Link.l1 = "그래, 네 말이 맞아. 여행은 나중에 해도 되지...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "선장님, 하지만 제 배 상태가 좋지 않습니다. 이런 상황에서 혼자 출항하는 건 현명하지 않겠어요!";
				Link.l1 = "그래, 네 말이 맞아. 네 배는 수리가 필요해.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "알겠소. 다음에 "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gen")+" 가다 "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" 며칠 뒤 도착하면 무엇을 해야 하지?";
				Link.l1 = "식민지 항구 앞바다에 한 달 동안 정박하라.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "있잖아, 그런 생각이 들었어. 나랑 같이 있어줘...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "알겠습니다, 선장님. 바로 출발하겠습니다.";
				Link.l1 = "네, 그렇게 해주십시오.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("오늘, 나는 다시 항해를 시작하겠어...","우리 만남이 있는 것을 잊지 마시오 "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Dat")+".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "나도 그러고 싶어. 이제부터 내 배는 다시 네 지휘 아래에 있어, 선장.";
					Link.l1 = "좋아.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "선장, 당신 함대에 이미 배가 다섯 척이나 있는데 여섯 번째 배는 어쩔 셈이야? 뭐, 난 그냥 내 배에서 여기서 기다릴래. 당신 새 동료들은 믿음직해 보이지 않아. 저 배들은 곧 가라앉을 테고, 당신은 결국 나를 데리러 다시 오게 될 거야.";
					Link.l1 = "이봐, 너 꽤 똑똑하잖아? 그냥 선장이 아니라 제독이 되어야겠는걸!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "오, 선장님, 말씀드린 대로 돌아오셨군요. 이제 당신 함대에 빈자리가 생겼습니까?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "그래, "+NPChar.name+", 한 명 있어. 함대에 온 걸 환영한다.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "아직 아니오, 유감스럽게도.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "선장님, 상황이 심각합니다! 적이 우리를 꽉 조이고 있어서, 우리가 죽을 때까지 절대 놓아주지 않을 것 같습니다! 우리 사람들이 지금 정말 위험에 처해 있고, 대부분의 포병들도 쓰러졌습니다!";
			link.l1 = "내가 저들을 도울게. 네가 지휘해서 여기서 나가자!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "네, 나리!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "승리입니다, 선장님! 상륙 부대는 전멸했고, 적은 남쪽으로 퇴각하기로 했습니다. 배의 상태는 양호합니다. 생존 선원: "+GetCrewQuantity(pchar)+" 사람들. 보고 완료했다!";
			link.l1 = "고맙다! 모두에게 럼을 돌려라, 그리고 항구에 도착할 때까지 경계를 강화해라!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "만세! 알겠어!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		// --> Эпилог
		case "SharlieEpilog_Folke_1": // Фульк
			dialog.text = "그래서… 이제 작별을 고할 시간이 된 건가?";
			link.l1 = "그런 것 같네. 솔직히 말하면, 이 결정을 내리는 게 더 쉬울 줄 알았어.";
			link.l1.go = "SharlieEpilog_Folke_2";
		break;
		
		case "SharlieEpilog_Folke_2":
			dialog.text = "그럼… 모든 것에 감사해, 캡틴. 많은 선장들을 봤지만, 진심으로 말할게 — 당신이 그중 최고야. 당신의 깃발 아래에서 항해할 수 있어 영광이었어.";
			link.l1 = "넌 충성스러운 장교였어, "+npchar.name+"야. 네 서비스에 감사해. 언젠가 운명이 우리를 다시 만나게 해주길 바라 — 그리고 서로 적이 아닌, 같은 편으로.";
			link.l1.go = "SharlieEpilog_Folke_nothing";
			link.l2 = "그 말을 들으니 기쁘네, 친구. 고맙게 생각해. 널 위해 한 달치 급여로 전역 처리를 해줄게. 오랜 세월 너의 충성심과 봉사에 감사해. 그리고 말인데… 이제 네가 선장이 되어도 될 때가 된 것 같아. 생각해 봐.";
			link.l2.go = "SharlieEpilog_Folke_salary";
			link.l3 = "그리고 너에게도 감사해, 동료. 넌 훌륭하고 유능한 장교야. 네 충성에 대한 감사의 표시로 세 달 치 급여를 전역금으로 주도록 할게. 그리고 말인데, "+npchar.name+"… 또 빚 때문에 감옥에 갔다는 얘기를 들으면… 맹세하지만 난 모든 걸 버리고 돌아와서 널 구해줄 거야 — 그리고 개인적으로 외딴 섬에 버려버릴 거야.";
			link.l3.go = "SharlieEpilog_Folke_salary_X3";
		break;
		
		case "SharlieEpilog_Folke_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
		break;
		
		case "SharlieEpilog_Folke_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Folke_salary_X3":
			dialog.text = "하하, 아니야, 캡틴. 난 다시는 고리대금업자에게 발도 들이지 않을 거야. 하지만 선장이 되는 건… 흥미로운 생각이야. 솔직히 몇 번이나 생각해 본 적 있어. 어쩌면 진짜 그렇게 할지도 몰라.";
			link.l1 = "그리고 한 가지 더. 탕헤른에서 작별 파티를 열려고 해. 네가 와주면 좋겠어. 우리 녀석들을 네 선원으로 영입할 좋은 기회가 될 거야.";
			link.l1.go = "SharlieEpilog_Folke_salary_X3_2";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Folke_salary_X3_2":
			dialog.text = "물론 갈게요, 캡틴.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Folke_salary_X3_3";
		break;
		
		case "SharlieEpilog_Folke_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
		break;
		
		case "SharlieEpilog_Duran_1":
			dialog.text = "아, 그래, '오래'란 말로도 부족하지. 너무 오래돼서 이젠 어떻게 하는지도 기억이 안 난다, 하하.";
			link.l1 = "그럼 내가 말하려는 걸 아마 좋아할 거야. 들어봐, 난 구세계로 떠날 거야. 아버지를 본 지 오래됐어, 아버지는 걱정하고 있고 — 솔직히 나도 걱정이야. 하지만 난 승객으로 갈 거야. 다른 사람의 배로.";
			link.l1.go = "SharlieEpilog_Duran_2";
		break;

		case "SharlieEpilog_Duran_2":
			dialog.text = "승객으로? 흥, 그렇구만.";
			link.l1 = "계속 이 길을 가야 할지 알아보고 싶어. 누가 알아, 행운이 준비되기도 전에 나를 떠날지.";
			link.l1.go = "SharlieEpilog_Duran_3";
		break;

		case "SharlieEpilog_Duran_3":
			dialog.text = "그런 거구나. 하하하. 네가 바다를 포기할 수 있다고 난 믿지 않아. 명심해 — 진짜 바다 사나이는 육지에선 지루해서 술에 취하거나 목을 매달거나 할 거야.";
			link.l1 = "그래서 난 승객으로 가는 거야 — 그 시간이 왔을 때 그런 삶을 살 수 있을지 알아보려고. 하지만 중요한 건 그게 아니야: 난 너희를 데려갈 수 없어 — 그리고 기다리라고 할 수도 없어. 나도 언제 돌아올지 몰라. 아버지는 분명 내가 남아서 집안일을 처리하길 원하실 거야.";
			link.l1.go = "SharlieEpilog_Duran_4";
		break;

		case "SharlieEpilog_Duran_4":
			dialog.text = "그러니까 이제 각자 알아서 살아야 한다는 거지? 음… 언젠간 그렇게 됐겠지. 하지만 난 작별 인사를 싫어해, 그러니까 눈물이나 포옹은 기대하지 마.";
			link.l1 = "수고했어. 난 네가 잘 해낼 거라 확신해 — 그렇지만 우리가 다시 만날 때까지 목숨을 잃지 않도록 해.";
			link.l1.go = "SharlieEpilog_Duran_nothing";
			link.l2 = "그럼 내 조언을 들어봐 — 옛 직업은 멀리하는 게 좋아. 좋은 일은 없을 거야. 여기, 잠시 버틸 수 있을 만큼의 은화를 줄게. 군대에 가는 건 추천하지 않겠지만, 어떤 프라이빗커의 호위병이 되는 건… 나쁘지 않을 거야. 생각해 봐.";
			link.l2.go = "SharlieEpilog_Duran_salary";
			link.l3 = "눈물은 없다고? 그럼 은화를 줄게. 하하, 네 눈이 반짝이는 게 보이네. 자, 이걸 가져. 세 달치 급여 — 르 프랑수아의 모든 해적들에게 일주일 술 사줄 수 있을 만큼이야. 아니면 간단히 말해, 반년은 살 수 있을 거야. 뭔가 할 일을 찾고 생계를 꾸릴 방법을 찾길 바랄게.";
			link.l3.go = "SharlieEpilog_Duran_salary_X3";
		break;
		
		case "SharlieEpilog_Duran_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
		break;
		
		case "SharlieEpilog_Duran_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Duran_salary_X3":
			dialog.text = "벌써 결심했어. 난 보물 사냥꾼이 될 거야. 거기엔 뭔가… 있어.";
			link.l1 = "하하! 좋은 선택이야! 그리고 한 가지 더: 마지막으로 제대로 즐길 거야. 그러니까 함께 하고 싶다면 — 술집으로 와.";
			link.l1.go = "SharlieEpilog_Duran_salary_X3_2";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Duran_salary_X3_2":
			dialog.text = "농담이지, 캡틴? 하하! 이건 절대 놓치지 않을 거야!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Duran_salary_X3_3";
		break;
		
		case "SharlieEpilog_Duran_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
		break;
		
		
		// <-- Эпилог
	}
}
