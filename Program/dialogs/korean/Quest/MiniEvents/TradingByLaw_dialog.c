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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "내 누추한 집에 온 걸 환영하오! 나는 크리스티안이오. 크리스티안 들루스, 당신을 위해 봉사하겠소. 무슨 일로 내 집 문턱까지 오셨소?";
			link.l1 = "이름은 선장이오 "+GetFullName(pchar)+". 나는 많은 양의 술을 구하려 하오. 내 뜻이 분명하겠지?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "뭐라고??? 누가 그런 거짓말을 퍼뜨렸단 말이오? 큰 오해라네, 분명히 말하겠소! 나는 어떤 종류의 술도 다루지 않소!";
			link.l1 = "흠, 흠... 내가 찾던 바로 그 사람을 발견한 것 같군.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "이런, 천만에요, 아니-아니-아니오! 무슨 말씀을 하시는 겁니까! 술을 거래한다고요? 제가요? 나는... 나는 그저, 음, 그러니까... 알겠습니다, 사실 약간의 술을 가지고 있긴 하지만, 전부 합법적인 것들입니다! 나는 단지 일반 시민들을 위해, 그러니까... 축제나 소박한 사교 모임을 위한 음료를 마련하는 것뿐이에요!";
			link.l1 = "왜 그리 떨고 있소, 이보게? 나는 그대의 감시자가 아니라 은인으로 온 것이오. 그대의 운이 트일 수도 있고, 내 주머니에는 두블룬 몇 개가 더해질 수도 있지.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "나? 나, 긴장했다고? 말도 안 돼! 내가 뭘 걱정할 이유가 있겠어? 나는 흠잡을 데 없는 인품을 가진 사람이야 – 내 집은 총독 관저 바로 옆에 있다네! 나는 법을 어기는 일이라곤 전혀 없어, 내 명예를 걸고 말이야!";
			link.l1 = "그럼 술 거래에 관여하지 않는 거로군? 참 안타까운 일이야. 나는 상당한 이익이 될 기회를 가지고 왔었지. 평범한 암거래 상인이라면 상상도 못 할 두블룬 말이야. 하지만 네가 내 사람이 아니라면 더 이상 귀찮게 하지 않겠다. 그럼 이만 가보지. 아니면...?";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "아... 잠깐만... "+GetAddress_Form(NPChar)+"... 용서해 주시오, 내 정신이 폭풍 속 갈매기처럼 흩어져서, 귀하의 존함을 깜빡 잊었소.";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+", 사실을 말하자면, 나... 그러니까... 당신이 찾는 그 사람의 행방을 알고 있을지도 모르네. 내가 그 사람에게... 당신의 후한 제안을 전해줄 수 있지.";
			link.l1 = "전달하라고? 농담이겠지. 이런 민감한 일들이 불필요한 손을 거쳐야 한다고 진심으로 생각하나?";
			link.l1.go = "Kristian_7";
		break;

		case "Kristian_7":
			dialog.text = "진실을 말하시는군. 하지만... 하늘이시여, 도와주소서... 이미 주사위는 던져졌소... 그래, 나는 정말 당신 편이오.";
			link.l1 = "이제 서로 이해했군, 크리스찬. 선술집에 술이 심각하게 부족한 상황이라네, 그리고 이 난국에서 우리 둘 다 큰 이득을 볼 수 있을 거라고 생각하네.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "선장님, 저는 주점 주인의 고충을 잘 알고 있소. 사람들이 내 집 문턱이 닳도록 찾아오고 있어서, 이제는 내 소박한 장사를 계속하기가 두렵소이다. 너무 많은 눈들이 지켜보고 있거든요. 혹시 선장님께서... 그러니까, 선장님처럼 지위 있는 분이 혹시...";
			link.l1 = "왜 직접 주점 주인에게 네 물건을 가져가서 팔지 않지?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "그 자... 나랑 거래하느니 차라리 나병환자랑 껴안을 거야. 그 거만한 바보는 나 같은 평범한 상인들을 완전히 깔보고 있지.";
			link.l1 = "확실히, 그의 명성은 이미 자자하지. 직접 네가 뭔가를 내밀면 그가 무시할 수도 있지. 하지만 나를 통해 건네면 이야기가 달라진다네.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "네가 중간 역할을 자처하겠다고? 그거라면 나도 꽤 만족스럽군... 최근에 엄청난 양의 화물을 들여왔지 - 이렇게 많은 건 처음이야! 적어도 반 년은 내 저장고가 꽉 찼을 텐데. 하지만 전능하신 하느님의 은총으로, 간신히 발각을 피했지\n아직도 우리가 어떻게 총독의 그물망을 빠져나왔는지 이해가 안 돼. 이런 식으로 두 번이나 운을 시험하는 건, 그야말로 자멸이나 다름없지.";
			link.l1 = "그렇다면 이제 슬슬 빛으로 나올 때가 된 것 같군. 물론 완전히는 아니지만, 네 일들을 좀 더 덜 위험하게 처리할 만큼은 말이야.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "빛으로... 나가라고? 하지만... 왜, 그건 힘 있는 친구들과 엄청난 돈이 필요하잖아! 무슨 이유로? 설마 너처럼 배까지 가진 선장이 영영 닻을 내리고 그냥 선술집 납품업자가 되려는 건 아니겠지?";
			link.l1 = "연줄에 관해서라면, 내 손이 닿는 곳은 자네가 미치지 못하는 곳까지 이어지지. 재정 문제라면... 투자 규모는 그리 크지 않을 걸세. 마지막으로 걱정하는 부분에 대해선, 염려 말게. 자네는 이 일에서 내 대리인으로 움직이면 되네. 내가 자네의 방패가 되어 줄 것이고, 자네는 내 꾸준한 공급원이 될 걸세. 우리의 거래는 오래가고 서로에게 이익이 될 걸세. 자네는 믿을 만한 손님을 얻고, 나는 확실한 물건을 확보하지. 이런 사업, 자네 생각은 어떤가?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "이게 뭔가 정교하게 짜인 함정이라고 확신했소. 하지만 사실, 그대의 제안은... 정말로 매혹적으로 들리는군. 안정, 신뢰... 이런 행운이 내게 미소 지을 줄은 꿈에도 몰랐소. "+GetSexPhrase("Monsieur","Mademoiselle")+", 전적으로 동의합니다! 얼마나 구매하시겠습니까?";
			link.l1 = "우선 당신의 무역을 제대로 자리잡게 한 뒤에, 구체적인 사항을 논의합시다. 지금 창고에 럼주와 와인이 얼마나 있소?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "바로 지금 말인가? 아... 내 지하 저장고를 살펴보는 게 어떻겠소, 거기서라면 내 재고를 정확히 확인해 줄 수 있을 테니.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "어디 보자... 아래에는 어떤 보물이 있을까? 아, 그렇지\n지금 내 재고는 고급 럼주 백 병과 훌륭한 와인 백 병이 정확히 있지.";
			link.l1 = "공정한 시작이라고 해야겠군. 네가 수입 문제만 해결하면, 매달 이런 납품을 빠짐없이 계속할 수 있겠나?";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "틀림없습니다, 선장님! 아니, 이 정도 양이라면 세 번, 아니... 네 번도 거뜬히 처리할 수 있습니다! 절대 지연되는 일 없을 것이니, 언제나 충분한 비축분을 유지하여 어떤 불상사가 닥쳐도 선장님의 보급에 차질이 없도록 하겠습니다.";
			link.l1 = "이 화물의 값을 말해 봐.";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "공정한 대가라면 이렇게 생각하겠소: 와인 열 병마다 두블룬 열 개, 럼 열 병마다 두블룬 세 개. 합해서 전체 화물은 모두 백삼십 두블룬이오.";
			link.l1 = "좋소. 여관주인과 협상하고 곧 돌아오겠소.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "선장님, 소식이 어떻습니까? 주점 주인과의 이야기는 어떻게 되었습니까?";
			link.l1 = "아직 그와 얘기하지 못했어. 그게 내가 다음으로 들를 곳이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "어떻게 되었소, 선장님? 주점 주인과 합의를 볼 수 있었소?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "아주 훌륭하게 해냈네, Christian. 그는 이 물건과 앞으로 올 모든 화물을 이백사십 두블룬에 사겠다고 했어. 첫 번째 화물에 대해서는 자네가 요구한 백삼십을 주고, 나머지는 내 보수로 챙기겠네. 하지만 앞으로의 이익은 전부 자네 몫일세.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "잘했네, 크리스찬. 그는 이번 물건과 앞으로 올 물건도 200두블룬에 사겠다고 했어. 첫 번째 거래는 네가 요구한 130두블룬을 주고, 남은 차액은 내가 정당한 보수로 가지겠네. 앞으로의 이익은 전부 자네 몫이야.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "정말 놀라운 소식입니다, 선장님! 이런 거래는 꿈도 꾸지 못했는데, 감사합니다! 하지만... 혹시 너무 성급하게 행동하신 건 아닌지요? 총독이... 저는... 그러니까...";
			link.l1 = "총독께서는 잘 알고 계시다. 이제부터 너는 매달 100두블룬을 내고, 제대로 된 무역 보고서를 제출해야 한다.";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "믿을 수가 없군요! 어떻게 해내신 겁니까, 선장님? 총독은 엄격한 분이시고, 암시장 상인들에게는 무서운 적인데...";
			link.l1 = "그게 바로 그 점이야, 크리스티안. 그는 불법 거래에는 반대하지만, 정당한 거래에는 반대하지 않아. 내 말을 다 듣고 나서 섬에서 주류 거래에 대한 명확한 조건을 제시했지. 이제부터 너는 내 이름 아래에서 일하게 된다. 무슨 잘못이라도 저지르면, 나 역시 너만큼 책임을 져야 해. 그러니 실수하지 마라. 아니면 내가 저승까지라도 널 쫓아갈 테니.";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "맹세합니다, 선장님, 이 일은 절대 후회하지 않으실 겁니다!";
			link.l1 = "이제 주점주인과 일을 마무리해야 하고, 그 다음에 우리 약속의 세부 사항을 정하겠소.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "물론입니다, 선장님. 지금 바로 화물을 가져가실 준비가 되셨습니까? 130두블룬입니다.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "그래, 여기 네가 찾던 두블룬이다.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "현재 나는 필요한 자금이 부족하오. 여기서 기다리시오 — 내가 돈을 가지고 돌아오겠소.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "선장님! 물건 가지러 다시 오셨습니까? 값은 여전히 130두블룬입니다.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "정말로 그랬지! 여기 보수다.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "유감스럽게도 아직 자금이 부족하오. 나중에 다시 오겠소.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "정말 고맙다! 가져가라! 약속한 대로 와인 백 병과 럼주 백 병이다.";
			link.l1 = "내 선원들이 화물을 처리할 거다. 그동안 나는 주점 주인과 얘기 좀 해야겠군.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! 이렇게 빨리 돌아오다니! 말해보게, 우리 약속은 잘 진행되었나?";
			link.l1 = "모든 일이 아주 훌륭하게 진행되었네, 크리스티안. 선술집 주인은 앞으로 매달 두 번씩 똑같은 물품을 요구할 걸세.\n그의 가게에 술이 꾸준히 들어가게만 하면, 곧 궁핍이란 말은 네 삶에서 사라질 것이야.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "선장님... 당신이... 이건 마치 신의 섭리가 직접 저를 이끌어 이 문턱에 서게 한 것 같습니다! 진정한 기적이 제 앞에 펼쳐졌으니, 제 행운이 믿기지 않을 지경입니다! 제가 무슨 선행을 했기에 이런 은혜를 입게 된 것입니까? 감사의 마음을 말로 다 표현할 수 없습니다!";
			link.l1 = "그러나 나는 너에게 깨우침을 줄 수 있지, 크리스천. 매달 너는 네가 가진 최고의 상품 중 일부를 특별히 내게만 남겨 두고, 다른 누구에게도 팔지 말아야 한다. 나는 네가 정한 가격대로 그것을 사겠다 - 와인 열 병마다 금화 열 닢, 럼주 열 병마다 금화 세 닢씩 말이다.";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "제게 더없는 영광이오, "+pchar.name+", 당신만을 위해 물품을 따로 빼놓겠습니다! 맹세코, 절대 실망시키지 않겠소! 얼마나 필요하십니까? 쉰 병? 아니면 백 병? 원하시는 수량을 말씀해 주시오!";
			link.l1 = "이 정도 양이면 내게는 지나치네. 각 20병이면 충분하겠소. 만약 더 필요하게 되면 즉시 알려주겠소.";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "물론이오, 물론이지! 그럼 이렇게 합시다 - 와인 스무 병과 럼주 스무 병을 이십육 두블룬에 드리겠소. 매달 열다섯째 날마다 당신의 상품이 준비되어 있을 것이오. 안부 인사만 나누러 오셔도 언제든 귀하의 방문을 환영하겠소!";
			link.l1 = "훌륭하오! 마지막으로 강조할 일이 있소, 크리스찬. 나는 그대의 성실함에 내 명예를 걸었소. 나를 실망시키지 마시오, 그렇지 않으면 그 대가를 알게 될 것이오.";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "저... 무슨 제안을 하시겠습니까, 선장님... 설마 당신이... 아니-아니오, 절대 실망시키지 않겠습니다! 모든 일은 제 영혼을 걸고 흠잡을 데 없이 제대로 처리하겠습니다!";
			link.l1 = "그럼 다시 만날 때까지!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "귀찮은 녀석 "+GetSexPhrase("똥개","창녀")+"! 네 일 아닌 일에 끼어들면 불행만 부른다는 걸 배우지 못했나?";
			link.l1 = "네가 내 배에 무단으로 들이닥쳤으면서, 이제 와서 나를 방해했다고 비난하는 건가? 완전히 미쳐버린 거 아니냐?";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "천둥이 내 앞 돛대를 날려버려라! 그러니까 너, "+GetSexPhrase("비참한 새끼놈","쓸모없는 창녀")+", 네가 어떤 일에 휘말렸는지 전혀 모르는 거야? 선창의 물자가 그냥 우연히 사라졌다고 생각했나?";
			link.l1 = "그 증류소를 잿더미로 만든 책임이 네게 있다고 주장하는 거냐?";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "하하, 드디어 네 두꺼운 대가리에 진실이 박히는구나, 체인샷이 내 창자를 꿰뚫어도 좋다! 그래, 내가 한 짓이지! 그 공급상은 장사에 뿌리를 너무 깊이 박았더군. 하지만 보다시피, 나는 결코 경쟁자들에게 지지 않아. 그리고 너도 그놈들과 같은 운명을 맞이하게 될 거다, 산탄이 내 돛을 갈기갈기 찢어도 상관없지!";
			link.l1 = "정말 재미있군. 그럼 네 실력을 한번 보자꾸나, 넵튠의 괴물들이 네 시체를 뜯어먹게 해 주마! 하하!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "안녕하시오, "+pchar.name+"! 어떤 순풍이 그대가 내 문턱까지 오게 했소?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "안녕하시오, 크리스티안. 내 물건 준비해 두었는가?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "좋은 하루구나, 크리스티안. 그저 네 일이 잘 풀리고 있는지 확인하고 싶었을 뿐이야. 더 이상 방해하지 않겠다.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "물론입니다, 선장님! 제 성실함에 대해 조금이라도 의심이 드십니까?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "잠깐도 미루지 않겠소, 크리스티안. 약속한 대로 대가요. 이제 내 술을 가져가겠소.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "전혀 아니오. 유감스럽게도 지금 내 주머니가 너무 가벼워서 말이오. 좀 더 준비가 되면 다시 오겠소.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "물론입니다, 선장님! 제 성실함에 대해 조금이라도 의심하실 수 있겠습니까?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "잠깐도 미루지 않겠소, 크리스티안. 약속한 대로 두블룬을 여기 두겠소. 이제 내 술을 가져가겠소.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "전혀 그렇지 않소. 유감스럽게도 지금은 제대로 된 보수가 없구려. 주머니가 충분히 무거워지면 다시 오겠소.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, 월별로 럼주와 와인 각각 백 병씩 정기 주문을 늘리고 싶네. 정확히 그렇게 해 주게.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, 우리 협약을 확장하는 것에 대해 다시 생각해보고 싶소.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "훌륭합니다. 언제나처럼, 신선한 물건이 15일에 맞춰 준비될 것입니다. 다음 방문을 기다리겠습니다.";
			link.l1 = "내가 꼭 돌아올 거라 믿으시오. 다시 만날 때까지.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "선장님, 그런 확장이라면 사업에 대단히 환영할 일이지만, 상당한 비용이 따릅니다! 더 많은 양을 다루려면 추가 인력, 더 큰 창고, 더 넓은 선박을 임대해야 하지요... 적절한 투자가 없다면 그렇게 대량의 주문을 제때에 맞춰 납품할 수 없을 것입니다.";
			link.l1 = "그런 조치를 취하려면 얼마가 필요하지? 이 확장된 사업이 원활히 돌아가게 하려면 어느 정도 투자가 보장되어야 하겠나?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "오만 페소면 충분하오. 추가 비용은 내가 직접 부담하겠소.";
			link.l1 = "오만? 맹세코... 그건 만만한 돈이 아니지. 정말로 좀 더 적은 자금으로는 안 되겠나?";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "깊이 유감스럽지만, 선장님, 이 금액이 절대적인 최소치임을 강조드려야 하겠습니다. 비용을 줄이려 든다면, 우리의 사업이... 그러니까, 아주 심각하게 탈선할 수도 있습니다. 그런 불상사는 선장님이나 저 모두에게 결코 도움이 되지 않을 것이라 생각합니다.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "여기 네 보수를 전부 주겠다. 이런 신뢰에 걸맞은 행동을 하도록 해라, 크리스천.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "다시 생각해 보니, 크리스티안, 이번 확장은 다소 시기상조일 수 있겠소. 상황이 더 나아지면 이 문제를 다시 논의합시다.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "원하시는 대로 하겠습니다, 선장님. 생각이 바뀌시면 언제든 제 도움이 필요하시면 말씀해 주십시오.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "선장님, 정말 기쁜 소식입니다! 즉시 진행하려면 은화 오만 닢을 가져오셨습니까?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "여기 네 보수 전액이다. 이런 신뢰에 걸맞은 자임을 증명해 보이거라, 기독교인.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "현재 내 금고에 필요한 자금이 부족하오. 자금이 마련되면 다시 오겠소.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "내 명예를 걸고, "+pchar.name+", 이 결정을 절대 후회하지 않을 것이오! 지체 없이 준비를 시작하겠소. 다음 수금부터는 최고의 럼주 100병과 훌륭한 와인도 같은 양으로, 한 번의 완전한 선적마다 130두블룬에 받을 수 있소.";
			link.l1 = "매우 만족스럽소. 하지만 명심하시오 – 모든 일에 극도의 신중함을 기해야 하오. 그대의 행동이 이 바다에서 내 위신에 직접적으로 영향을 미치니.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}