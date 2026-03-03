#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Soaram os alarmes na cidade. Pelo visto, chegou a minha vez de pegar em armas também...","Os guardas da cidade não estão te perseguindo, por acaso?","Você não vai encontrar abrigo aqui, mas pode acabar com alguns centímetros de aço frio cravados nas suas costelas!"),LinkRandPhrase("O que você precisa, "+GetSexPhrase("canalha","canalha")+"?! Os guardas estão no seu encalço, você não vai longe, "+GetSexPhrase("pirata imundo","fedelho")+"!",""+GetSexPhrase("Imundo","Imundo")+" Assassino! Guardas!!!","Eu não tenho medo de você, "+GetSexPhrase("desgraçado","fedelho")+"! Em breve você será enforcado em nosso forte, não vai chegar longe..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Vejo que você está cansado de viver...","Pelo visto, não há pessoas pacíficas em "+XI_ConvertString("Colônia"+npchar.city+"Gen")+", todo mundo quer ser herói!"),RandPhraseSimple("Vá para o inferno!","Heh, esses serão os últimos segundos da sua vida..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "O que te traz até mim desta vez?";
				link.l1 = "Acredito que você conhece um cavalheiro chamado Gerard LeCroix? Ele deveria ter deixado uma recompensa para mim...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Boa tarde, marinheiro! Meu nome é "+GetFullName(npchar)+", e eu sou o guardião deste farol. Que ventos trouxeram você até aqui?","Olá! Faz bastante tempo desde a última vez que vi rostos novos no meu farol... Permita-me apresentar - "+GetFullName(npchar)+", e este farol é tanto minha casa quanto meu trabalho. O que posso fazer por você?");
				link.l1 = "Olá, "+npchar.name+"! Meu nome é "+GetFullName(pchar)+", eu sou capitão de um navio. Estava passeando por essa enseada maravilhosa e decidi passar aqui para ver quem mora neste lugar.";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, meu velho amigo, Capitão "+GetFullName(pchar)+"! Entre, entre! O que te traz aqui desta vez?";
				link.l1 = "Saudações, velho lobo do mar! Não está aqui sozinho, lamentando-se no seu farol?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Agora você sabe. Eu já fui marinheiro, assim como você, mas faz muito tempo desde a última vez que pisei no convés de um navio. Agora este farol está sob meus cuidados, e também vendo algumas coisas...";
			link.l1 = "E o que exatamente você está vendendo?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = " O que te traz aqui desta vez?";
			link.l1 = RandPhraseSimple("Você pode me dizer se aconteceu algo interessante recentemente na sua colônia?","Faz um bom tempo que não piso em terra... O que está acontecendo por aqui?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Vamos ver o que você tem à venda.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Então, "+npchar.name+", meu amuleto já chegou?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", quero encomendar um amuleto com você.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Escute, "+npchar.name+", eu sei que você trabalha entregando amuletos sob encomenda. Então, deve entender bastante sobre eles. Por favor, dê uma olhada nisso aqui — o que pode me dizer sobre esse objeto?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Amigo, estou aqui de novo para te perguntar sobre aqueles amuletos estranhos";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "Tem algo que eu queria te perguntar...";
			link.l4.go = "quests";
			link.l9 = "Eu só dei uma espiada...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Às vezes vou até a praia e coleto conchas, tem um lugar bonito não muito longe daqui, então você sempre pode comprar pérolas comigo. Toda tempestade traz âmbar, também vendo isso, mas vai te custar caro. Às vezes as ondas trazem todo tipo de bugiganga interessante de navios naufragados, e meus velhos conhecidos me trazem itens especiais. Tenho interesse em amuletos encantados, sábios pagam bem por eles. Também ofereço armas em ocasiões especiais, não me pergunte de onde eu as tiro. Um comerciante da cidade compra toda a tralha de mim, as coisas boas eu mesmo vendo depois de consertar e limpar. Tenho interesse em rum. Não estou falando daquela mijo que servem na taverna local por dois pesos a caneca. Quero dizer rum jamaicano de verdade, engarrafado. Ele cura e ressuscita gente. Pago dez vezes mais por cada garrafa que você trouxer. Pense nisso.";
			link.l1 = "Escute, "+npchar.name+", você comentou que tem velhos amigos marinheiros que lhe trazem amuletos encantados. É possível encomendar um amuleto específico com você? Pago muito bem por isso.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Capitão, uma quantidade de mercadorias apareceu recentemente na praia - "+GetGoodsNameAlt(sti(npchar.quest.goods))+". Algumas partes foram estragadas pela água salgada, mas "+FindRussianQtyString(sti(npchar.quest.goodsqty))+" Consegui salvá-los em ótimo estado. Quer comprar alguns? Faço um preço camarada, só para "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" por unidade.";
				link.l1 = "Não. Mostre-me o que você conseguiu recentemente.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Hm... Uma oferta honesta, concordo. Acho que posso revendê-lo e ganhar algum lucro. Vejamos... Isso vai dar "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". Isso está correto?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "Está certo, capitão. Um ótimo negócio! Nós dois saímos ganhando com isso...";
			link.l1 = "Certo, então. Vou mandar os marinheiros levarem a carga para o meu navio. Agora, mostre o que você trouxe para vender.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Bem, não todos, mas alguns amuletos aparecem por aqui com mais frequência que outros, então acho que posso te ajudar. Mas já aviso: qualquer amuleto encomendado desse jeito vai te custar 100 dobrões. Espero que entenda...";
				link.l1 = "Preço não é problema. Que amuletos você pode me oferecer?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Pff! Com esse dinheiro dá pra comprar um navio. Está caro demais. Acho que vou me virar sozinho mesmo...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "Não, capitão. Essas coisas só aparecem por acaso, então é impossível encomendá-las com antecedência. E além disso, você teria que esperar por elas quase uma eternidade...";
				link.l1 = "Bem, se é assim, não há nada a fazer.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Como quiser. Venha me procurar se mudar de ideia.";
			else dialog.text = "Gostaria de ver o que tenho à venda hoje, capitão? Se não encontrar nada que valha a pena, volte em breve – talvez eu tenha algo diferente para vender.";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "Tudo isso, claro, é bom, mas o que eu queria perguntar – suponho que você conheça um cavalheiro chamado Gerard Lecroix? Ele deveria ter deixado uma recompensa para mim...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "Mostre-me seus itens.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Me conte, o que aconteceu de interessante na sua colônia ultimamente?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Negócios são negócios, mas eu queria te perguntar uma coisa.";
			link.l3.go = "quests";
			link.l4 = "Tenha um bom dia, "+npchar.name+"! Foi um prazer te conhecer! Passo aqui outra hora...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Faça sua escolha.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Infelizmente, nada nesta lista me interessa por enquanto.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Uma boneca de vodu? Você gosta de armas de fogo? Ótimo...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Testador de pólvora? A pontaria é o segredo do sucesso em qualquer confronto. Interessante...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Uma adaga ritual? Você gosta de cortar seus inimigos com golpes poderosos de uma espada larga pesada? Então isso é pra você. Muito bem... ";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Uma alabarda? Um golpe descendente de um machado enorme vai esmagar qualquer inimigo! Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Uma tsantsa? Aquilo sim pode assustar até o pirata mais destemido. Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Uma cabeça de coral? A sua munição de canhão vai direto no alvo! Ótimo...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Corcunda? A resistência é a melhor amiga de um guerreiro. Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli? Que o casco do navio inimigo se desfaça em pó! Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? Coloque o Baldo no comando – e cada bala de canhão vai acertar em cheio o alvo! Ótimo...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella? Veneno de cobra é a coisa mais perigosa que existe. Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Máscara Ngombo? Diminui a vigilância dos seus inimigos, ha-ha! Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Escudo Ngombo? Se você não conseguiu desviar de uma bala, esse amuleto pode salvar sua vida. Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Euchologion? Uma boa oração pode até desviar uma bala. Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Um crucifixo? Isso vai ajudar muito um cristão em combate corpo a corpo. Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo? Essa aqui transforma um ferimento mortal em só um arranhão. Ótimo...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo?   E que os canhões estejam sempre prontos para a batalha!   Bom...";
			link.l1 = "Quando devo voltar para buscar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna? A imagem da Santíssima Virgem possui poderosas propriedades de cura. Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Água benta? Até um covarde banhado em água benta vira um herói lendário! Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Uma âncora? Que seu navio fique à tona mesmo sob uma chuva de balas de canhão, ha-ha! Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Encolpion? Suas velas não temerão nenhum vento enquanto você possuir este amuleto. Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Milagreiro? Que o Senhor proteja sua tripulação tanto em terra quanto no mar! Bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta? Balas de mosquete vão voar sobre sua cabeça, sem te causar nenhum dano! Ótimo...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo? Todo mestre de doca sonha com isso. Ótimo...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli? Isso vai economizar um bom tempo remendando as velas. Ótimo...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Um macaco? Eu diria um burro de carga! Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Fã de cigana? Engane um patrulheiro! Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Uma tartaruga de jade? Essa é sua carta na manga! Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Um nó de macaco? Como dizem - faça com que te respeitem! Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Um pescador? Esse é o sonho de todo navegador. Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Contas de mercador? Dinheiro gosta de ser contado, não é? Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl? Qualquer barco velho e lento vai navegar mais rápido que o vento! Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Brinco de marinheiro? Dê esse para o seu timoneiro! Muito bem...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Peregrino? Um vento contrário vira vento a favor. Bom...";
			link.l1 = "Quando devo voltar para pegar meu pedido?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "Daqui a dois meses, nem um dia antes. Acho que até lá eles já vão ter me trazido. Então vou te esperar com o dinheiro em dois meses.";
			link.l1 = "Ótimo! Eu estarei lá! Obrigado, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Sim, eu tenho. Você trouxe as 100 dobrões, Capitão?"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "Claro! Aqui está, conforme combinado.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Ah, deixei o dinheiro no navio! Vou trazer em breve.";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "Ainda não. Venha me ver mais tarde. E não se preocupe – seu amuleto certamente vai chegar.";
			link.l1 = "Certo.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveDublonsFromPCharTotal(100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "Parece que está tudo certo. Aqui está seu amuleto. Boa sorte com ele!";
			link.l1 = "Obrigado, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Mostre-me o que você tem aí.";
			link.l1 = "Aqui, parece um amuleto indígena antigo. Mas não faço ideia de como usá-lo ou que poder oculto ele guarda.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Olha só. Você é a terceira pessoa que me mostra uma coisa dessas, camarada. Esse amuleto veio da selva selvagem do Continente do Sul. Existem índios não muito longe do Panamá que usam enfeites como este. Os nativos dizem que isso é um legado dos 'grandes ancestrais' deles.\nNão faço ideia de quem eram esses ancestrais ou que tipo de legado deixaram, mas posso te dar um conselho sobre onde perguntar. Interessado?";
				link.l1 = "Com certeza!";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "Hmm... I've held a lot of amulets in my hands, but this one, I see for the first time in the Caribbean. Sorry, mate, I cannot help you; I don't know this kind of stuff. But it is not a simple thing; that's a fact. Ask somebody else. I know for sure that there are other lighthouse keepers like me who know about amulets not any less.";
				link.l1 = "Com licença... Então vou continuar perguntando.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "There is a Carib village on Dominica, and the local chief is named Moknitekuvri. They have a shaman named Tuttuathapak, a highly respected Indian. He's not one of the Caribs; he's from that place about which I've told you already. He can tell you more about this amulet than me. But be careful - Tuttuathapak hates white people. He really hates them. After all, they once enslaved him and took him away from his home...";
			link.l1 = "Imagino que ele tenha vindo para o Caribe desse jeito?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Sim. Essa é uma história bem interessante. O navio, que transportava escravos indígenas, ficou preso numa calmaria perto de Marie Galante e metade da tripulação morreu de uma febre repentina. Mas nenhum indígena adoeceu!\nDepois disso, o capitão enlouqueceu e incendiou o navio. Com isso, os indígenas presos iniciaram um motim e massacraram a tripulação. Consegue adivinhar quem foi o líder deles?";
			link.l1 = "Eu aceito...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "É isso. Aposto que foi um feitiço de xamã que deixou o mar calmo como um morto e infectou a tripulação com uma doença mortal. Esse índio é muito esperto e perigoso. Se for falar com ele, seja educado e tome cuidado com o que diz – senão, vai arrumar muita confusão. E mais: ele nem vai te dar atenção se não levar uma oferenda.";
			link.l1 = "E que tipo de oferenda ele pode exigir?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Você não vai suborná-lo com qualquer porcaria. Pelo que sei, ele manda seus soldados caribes até os assentamentos dos brancos para comprar armas de fogo. Traga um mosquete de presente para ele e aí, acho que vai agradá-lo e conseguir um pouco da atenção dele.";
			link.l1 = "Obrigado! Vou fazer como você disse... Me diga, como você sabe de tudo isso?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Meu amigo era marinheiro naquele navio amaldiçoado. Por sorte, ele conseguiu sobreviver àquele inferno... Vi nele um amuleto igual ao seu, então parece que o falecido capitão também pegou alguns pertences dos índios. Tenho certeza de que seu amuleto veio da coleção dele – quando o capitão enlouqueceu e incendiou o navio, os marinheiros o mataram e depois saquearam os baús da cabine.";
			link.l1 = "Entendi. Então só preciso levar um presente para Dominica. Obrigado pela ajuda e pela história interessante!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Boa sorte, meu amigo, e tome cuidado com esse diabo de pele vermelha...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Sim? Você já falou com Tuttuathapak, estou certo?";
			link.l1 = "Exatamente. E agora quero encontrar mais dois amuletos. Você disse que eu fui o terceiro a lhe mostrar esse artefato. E quem foram os outros dois?";
			link.l1.go = "caleuche_10";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_10":
			dialog.text = "Um deles é meu amigo, o marinheiro daquele navio que trouxe Tuttuathapak para as ilhas do Caribe. Desde aquele incidente, ele não pisou mais no convés de nenhum navio. Faz um tempo que não o vejo, mas sei onde ele mora. Procure por ele no West Main, em Belize – agora ele é caçador e vive pelas selvas. O nome dele é Fergus Hooper.";
			link.l1 = "Certo. E o segundo?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Eu sei só um pouco sobre o segundo. Se o nome dele é Jack ou Jackson, e se ele é corsário, pequeno comerciante ou simplesmente um aventureiro. Ele tem um xebec com um nome estranho... hmm... o nome dela é... Droga, esqueci! Mas o nome é algo demoníaco. Perguntei o que significava, e ele disse que era uma mulher-pássaro, nascida dos deuses do mar. Bah! Sem Deus...";
			link.l1 = "Nerd... Então você não lembra o nome dela?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Não, que o raio me parta, não me lembro. Ah, e quando ele se apresentou, disse que era de Barbados.";
			link.l1 = "Isso é alguma coisa! Tudo bem, vou tentar encontrar esse amante de mulheres emplumadas antes que alguém mais o faça... Valeu, amigo, você me ajudou muito!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "De nada, capitão, apareça quando quiser.";
			link.l1 = "Claro!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
			AddLandQuestMark(characterFromId("Bridgetown_Portman"), "questmarkmain");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Você é "+GetSexPhrase(" um ladrão, meu caro! Guardas, peguem-no"," Ladrã! Guardas, peguem ela")+"!!!","Caramba! Olhei pro lado por um instante e você já está enfiando a cabeça no baú! Pare, ladrão!","Guardas! Roubo! Peguem o ladrão!");
			link.l1 = "Droga, maldição!";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "Ah, então você é aquele capitão! Sim, eu estava esperando por você. O Gerard também estava, mas precisou sair às pressas para uma expedição e me pediu para entregar o pagamento a você. Ele disse que era importante você vir. Aqui estão 90 dobrões, se quiser conferir.");
			link.l1 = "Obrigado! É bom lidar com gente honesta.";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 90);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
