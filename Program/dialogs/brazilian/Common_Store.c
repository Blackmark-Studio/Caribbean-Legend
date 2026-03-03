// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("O alarme foi disparado na cidade, e todos estão procurando por você. Se eu fosse você, não ficaria aí.","Todos os guardas da cidade estão vasculhando a cidade à sua procura. Não sou tolo e não vou falar com você!","Corra, "+GetSexPhrase("amigo","moça")+", antes que os soldados te encham de furos..."),LinkRandPhrase("O que você precisa, "+GetSexPhrase("canalha","canalha")+"?! Os guardas da cidade já estão no seu encalço, você não vai longe, "+GetSexPhrase("pirata imundo","escória assassina")+"!","Assassino imundo, saia da minha casa agora mesmo! Guardas!","Eu não tenho medo de você, "+GetSexPhrase("desgraçado","fedelho")+"Em breve você será enforcado em nosso forte, não vai chegar muito longe..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, um alarme nunca é problema pra mim...","Jamais vão me pegar."),RandPhraseSimple("Cale a boca, seu desgraçado, "+GetWorkTypeOfMan(npchar,"")+", ou eu arranco essa sua língua imunda!!","Heh, "+GetWorkTypeOfMan(npchar,"")+", e todo mundo lá está aqui para pegar piratas! Vou te dizer uma coisa: sente-se quieto e você não vai morrer..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Ei, seu desgraçado! Acha que pode pegar o que quiser? De jeito nenhum! Pessoal! Às armas! Derrubem esse maluco!","Se quer alguma coisa, compre, seu bruto! Agora vou te mostrar como é que se faz! Pessoal, peguem suas armas! Alerta!");
				link.l1 = RandPhraseSimple("Hã? O quê?","Ué, por que você está fazendo isso?");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Gostaria de comprar um lote de vinho europeu com você – cinquenta ou sessenta garrafas. Disseram-me que você tem o suficiente em estoque."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Olá novamente. Por favor, dê uma olhada nesta carta – talvez você reconsidere sua posição sobre me vender vinho?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Sou eu de novo. Podemos retomar nosso acordo de vinho que foi interrompido? Consegui juntar dinheiro suficiente."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Queria comprar alguma coisa, monsieur?";
				Link.l1 = "Claro que sim – pra que servem as lojas, afinal? Mostre-me o que tem à venda.";
				Link.l1.go = "trade_1";
				Link.l2 = "Vim tratar de um assunto específico de negócios...";
				Link.l2.go = "quests";
				Link.l3 = "Me desculpe, mas eu preciso ir.";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "Escute, monsieur, estou procurando trabalho. Não um emprego fixo ou carregar carga, mas algo mais como fazer alguns serviços, por assim dizer. Por acaso precisa de alguma ajuda?";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "Terminei sua tarefa. Encontrei Gralam Lavoie.";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "Conheça seu novo assistente, monsieur.";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "Sou eu de novo, monsieur. Vim buscar minha recompensa.";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "Dê uma olhada nesses brincos, monsieur. Encontrei-os no corpo de um bandido que foi morto na selva. É claramente obra de um ourives talentoso que, tenho certeza, não é daqui. Você pode me dizer algo sobre esses brincos?";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Capitão, obrigado por me salvar.";
				Link.l1 = "Oh, de nada.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "O que houve, capitão? Perdeu alguma coisa? Por que está andando desse jeito pela minha loja?";
				Link.l1 = "Veja só, pois é que eu tenho mesmo! Onde está aquele maldito Gerard LeCroix? Cumpri todas as tarefas que o Florian Shoke me deu e, que um tubarão me engula inteiro, foi um trabalho dos infernos! E agora, quando venho buscar minha recompensa, descubro que esse passarinho já voou!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Como posso te dizer... Perdido. Você viu meu cliente? O nome dele é Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Capitão, quero lhe pedir um favor. Você pode me ajudar?";
				link.l1 = "Como posso ajudar você?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Prazer em conhecê-lo, senhor! É novo por estas terras?","Bem-vindo, capitão! Minha loja está à sua disposição, senhor.","Senhor, por favor, entre! Fico feliz em lhe oferecer as melhores mercadorias que você pode encontrar neste arquipélago."),LinkRandPhrase("Oh, monsieur capitão! As melhores mercadorias de todas as colônias francesas - bem aqui, bem agora, e exclusivamente para você!","Que agradável encontro, monsieur! A melhor loja com os melhores produtos franceses - ao seu dispor!","Já nos conhecemos antes, monsieur capitão? Saiba que minha loja é tão boa quanto as melhores lojas da metrópole!"),LinkRandPhrase("Oh! Señor capitão! Que alegria ver você na minha loja!","Estou feliz em receber um caballero tão brilhante na melhor loja de todas as colônias espanholas!","Oh, nobre hidalgo! O destino em pessoa trouxe você à minha humilde loja! Aqui você encontrará tudo o que desejar!"),LinkRandPhrase("Boa tarde, senhor capitão. É a sua primeira visita aqui?","Olá, senhor. É sua primeira vez aqui? Garanto que a qualidade dos nossos produtos holandeses vai te surpreender!","Por favor, entre, senhor capitão! As melhores mercadorias pelos menores preços disponíveis – esse é o jeito holandês de fazer negócios!"));
			Link.l1 = LinkRandPhrase("Prazer em conhecê-lo também. Meu nome é "+GetFullName(pchar)+" e sou relativamente novo por estas terras. Bem, mostre-me as riquezas do arquipélago!","Prazer em conhecê-lo também. Eu sou "+GetFullName(pchar)+". capitão do navio '"+pchar.ship.name+"'. Então, quais são as ofertas do momento?",""+GetFullName(pchar)+", capitão do navio '"+pchar.ship.name+", prazer em conhecê-lo. Então, o que pode me oferecer?");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "Capitã Helen! Sempre um prazer.";
				link.l1 = "Assim como sou para você, obrigado.";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("O alarme foi dado na cidade, e todos estão procurando por você. Se eu fosse você, não ficaria aí.","Todos os guardas da cidade estão vasculhando a cidade atrás de você. Eu não sou tolo e não vou falar com você!","Corra, "+GetSexPhrase("amigo","moça")+", antes que os soldados te transformem num coador..."),LinkRandPhrase("O que você precisa, "+GetSexPhrase("canalha","canalha")+"?! Os guardas da cidade já estão no seu encalço, você não vai longe, "+GetSexPhrase("pirata imundo","escória assassina")+"!","Assassino imundo, saia da minha casa agora! Guardas!","Eu não tenho medo de você, "+GetSexPhrase("canalha","fedelho")+"Em breve você será enforcado em nosso forte, não vai chegar muito longe..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, um alarme nunca é problema pra mim...","Eles nunca vão me pegar."),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", ou eu arranco essa sua língua imunda!","Heh, "+GetWorkTypeOfMan(npchar,"")+", e todos lá - estão aqui para pegar piratas! Vou te dizer uma coisa, amigo: fique quieto e você não vai morrer..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Por favor, me desculpe, mas não tenho tempo para você agora.";
				link.l1 = "Sim, claro. Passo aqui outra hora, então.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Capitão, obrigado por me salvar.";
				Link.l1 = "Oh, de nada.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "O que houve, capitão? Perdeu alguma coisa? Por que está andando desse jeito pela minha loja?";
				Link.l1 = "Veja só, quem diria – eu realmente cumpri! Onde está aquele maldito Gerard LeCroix? Cumpri todas as tarefas que o Florian Shoke me deu e, que os tubarões me devorem, não foi nada fácil! E agora, quando venho buscar minha recompensa, descubro que esse passarinho já voou!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Como posso te dizer... Perdido. Você viu meu cliente? O nome dele é Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Capitão, quero lhe pedir um favor. Você pode me ajudar?";
				link.l1 = "Como posso ajudar você?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Ah, veja só quem apareceu! Bem, como dizem, dinheiro não tem cheiro, então entre, capitão, e vamos negociar...","Não posso dizer que estou feliz em te ver, "+GetFullName(pchar)+"... Mas ainda posso negociar com você.","He-he... Bem, eu não o convidaria para minha casa, capitão - mas minha loja continua à sua disposição."),LinkRandPhrase("Ah, veja só quem está aí! Não é "+GetFullName(pchar)+"! Quer negociar, ou só quer pegar algo de graça? Ei, tô brincando...","Não posso dizer que estou feliz em te ver aqui, "+GetAddress_Form(NPChar)+". Mas se você tem dinheiro para gastar - entre, entre...","Quer negociar, capitão "+GetFullName(pchar)+"? Se for o caso, poderia ser rápido, por favor? Os outros clientes estão evitando você, e isso prejudica meus negócios,"),LinkRandPhrase("Quer negociar, senhor? Só um instante, vou contar o dinheiro – sabe como é, tem uns tipos suspeitos por aí... Claro, não estou falando de você, capitão!","Se eu te visse em alto-mar, "+GetAddress_Form(NPChar)+", eu provavelmente encomendaria mais velas... Mas aqui, na minha loja, posso lhe oferecer uma troca.","Capitão, vou avisar logo: se o tecido estiver manchado de sangue e o café cheirar a pólvora, não aceito. Fora isso, dê uma olhada e escolha o que quiser.")),LinkRandPhrase(LinkRandPhrase("Fico feliz em vê-lo novamente, "+GetAddress_Form(NPChar)+"! Comprando ou vendendo - estou sempre feliz em ajudar você.","Eu lhe imploro, "+GetAddress_Form(NPChar)+", entre! Sempre fico feliz em ver meu cliente favorito aqui. O que vai ser desta vez - comprar ou vender?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Que alegria te ver de novo! O que vai ser desta vez - comprar ou vender?"),LinkRandPhrase("Gostou dos nossos produtos, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Estou sempre ao seu dispor - dê uma olhada e faça sua escolha.","Olá, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Fico feliz em vê-lo novamente! Gostaria de dar uma olhada na nossa seleção de mercadorias?","Que bom ver você, capitão! Eu sabia que ia valorizar nossos produtos de qualidade. Quer dar uma olhada nas novidades?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Por favor, entre! Todas as mercadorias são para você – e com ótimos descontos nesta ocasião!","Capitão "+GetFullName(pchar)+", mais uma vez você me alegra com sua visita! Por favor, escolha o que quiser, fique à vontade!","O que deseja desta vez, capitão? Fico feliz que ainda se lembre de como me encontrar. Temos todas as mercadorias de que possa precisar – da melhor qualidade!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("É assim que você me recebe, amigo? Bem, vou lembrar disso se nos encontrarmos no mar... Pare de tremer, era só brincadeira. Mostre o que você tem.","Certo, camarada. Posso precisar dos seus produtos, mas não preciso da sua língua. Consegue ficar quieto ou vai precisar de ajuda pra isso? Cala a boca e mostra logo o que tem pra vender."),RandPhraseSimple("Vamos direto ao assunto, mercador. Não tenho tempo para discutir questões de moral com você, então vamos apenas negociar como pessoas decentes.","Calma aí, amigo. Brincar tudo bem, mas lembre-se que eu posso me irritar... Então para de me provocar e só me mostra o que você tem pra vender.")),RandPhraseSimple(RandPhraseSimple("Sempre gosto de passar aqui. O que você tem de interessante à venda?","Sempre bom te ver, amigo. E então, quais as novidades para os viajantes do mar que não pisam em terra firme há meses?"),RandPhraseSimple("E mais uma vez, estou em "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! Ainda bem que não estive aqui para esquecer. Mas sobrou algo nos seus armazéns para mim? Ou já resolveram tudo?","Como você pôde não vir? Você sempre me agrada mais do que isso. Então, o que você trouxe aí?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(RandPhraseSimple("Todos a postos! ","Faça uma inspeção! ")+LinkRandPhrase("O que um "+GetSexPhrase("cavalheiro","cavalheiro, oh, me perdoe - uma dama")+" de sorte que você precisa na minha loja, he-he?","Que surpresa para um pobre velho lojista! He-he!","Então, que bons ventos trouxeram você à minha loja?"),LinkRandPhrase("Abram os portos!"," Ganchos para o lado! ","Siga em frente!")+RandPhraseSimple(" Aqui você vai encontrar"," Minha loja tem")+LinkRandPhrase(" os melhores preços de toda a ilha."," excelente variedade de mercadorias."," mercadorias da mais alta qualidade disponíveis.")+RandPhraseSimple(" Estou ao seu dispor"," O que você quiser")+", capitão!"),pcharrepphrase(RandPhraseSimple("Alguma mercadoria para "+GetSexPhrase("senhores","senhores e senhoras")+" da fortuna! He-he! Até serem pendurados para secar ao sol!","O vento balança os enforcados no porto e leva o tilintar das correntes. Mas dinheiro não tem cheiro, não é?"),"Você gostaria de "+LinkRandPhrase("compre as melhores mercadorias de "+NationNameGenitive(sti(NPChar.nation)),"comprar ou vender sua carga","Tem alguma carga lucrativa?")+RandPhraseSimple("? Estou ao seu dispor!","? Minha loja está ao seu dispor!")+RandPhraseSimple(" Que bom te ver"," Faça como quiser")+", capitão!")),NPCharRepPhrase(npchar,pcharrepphrase("Se quer um conselho, capitão, não economize na bala de canhão. Os mortos são muito mais fáceis de revistar, sabe!","Notei logo de cara que você é um "+GetSexPhrase("companheiro habilidoso","moça astuta")+". "+RandPhraseSimple("Mas agora posso ver que você é mesmo um verdadeiro "+GetSexPhrase("herói","audacioso")+".","Você é jovem, mas "+RandPhraseSimple("fique sempre atento.","você certamente não é fácil de enganar."))),pcharrepphrase("Estou disposto a comprar toda a carga dos prêmios capturados de você. Prefere ser pago em prata ou ouro? Essas coisas sempre têm um preço alto.","A navegação comercial é um negócio lucrativo, capitão "+GetFullName(pchar)+", não é?")),NPCharRepPhrase(npchar,RandPhraseSimple("Enrolamos todos eles bem apertados Com vinte voltas de um cabo forte E jogamos no mar, fora do nosso alcance! ",RandPhraseSimple("Quinze homens no baú do morto!","Bebida e o diabo acabaram com o resto!")+" Yo ho ho e uma garrafa de rum! ")+RandPhraseSimple("E aí, capitão?","Procurando algo para comprar, capitão?"),pcharrepphrase("Vejo que você é bom de barganha, capitão "+GetFullName(pchar)+" Como você é um cliente que sempre volta, estou te oferecendo preços muito bons!","Certo, Capitão "+GetFullName(pchar)+", em consideração a você, posso oferecer só um pouquinho mais! O que deseja?")),NPCharRepPhrase(npchar,"Juro, conversar com você está me dando enjoo. "+LinkRandPhrase("Compre um pouco de amendoim. Porcos adoram essas coisas. ","Você espera que alguém lustre suas botas com rum aqui? ",pcharrepphrase("Eu conheço o seu tipo. Enche a cara de rum – e vai direto pra forca.","Fico pensando como sua mãe deixou você virar marinheiro! Marinheiro! Você daria um alfaiate muito melhor...")),pcharrepphrase(RandPhraseSimple("Eu pensei que ","Eu esperava que ")+RandPhraseSimple("achei que você tinha deixado nossa ilha para sempre.","Eu achei que nunca mais fosse te ver.")+RandPhraseSimple(" Os mortos estão pendurados no seu pescoço como pedras de moinho... "," Quantos marinheiros você já deixou apodrecer entre os corais?!"),"Capitão "+GetFullName(pchar)+", sua paixão pelo comércio superou todas as minhas expectativas!"+RandPhraseSimple(" Quer fazer alguma compra de última hora antes de zarpar?"," Está procurando algo especial?"))),"cycle",10,npchar,Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, veja só quem apareceu! Bem, como dizem, dinheiro não tem cheiro, então entre, capitão, e vamos negociar...","Não posso dizer que estou feliz em vê-lo, "+GetFullName(pchar)+"... Mas ainda posso negociar com você.","He-he... Bem, eu não o convidaria para minha casa, capitão – mas minha loja continua à sua disposição."),LinkRandPhrase("Ah, veja só quem apareceu! Não é aquele(a) "+GetFullName(pchar)+"! Quer negociar ou só quer pegar algo de graça? Ei, tô brincando...","Não posso dizer que estou feliz em te ver aqui, "+GetAddress_Form(NPChar)+". Mas se você tem dinheiro para gastar - entre, entre...","Quer negociar, capitão "+GetFullName(pchar)+"? Se for o caso, poderia ser rápido, por favor? Os outros clientes estão te evitando, e isso prejudica meu negócio,"),LinkRandPhrase("Quer negociar, senhor? Só um instante, vou contar o dinheiro – sabe como é, tem uns tipos suspeitos por aí... Claro, não estou falando de você, capitão!","Se eu te visse em alto-mar, "+GetAddress_Form(NPChar)+", eu provavelmente encomendaria mais velas... Mas aqui, na minha loja, posso lhe oferecer uma troca.","Capitão, já vou avisando: se o tecido estiver manchado de sangue e o café cheirar a pólvora, não vou aceitar. Fora isso, dê uma olhada e escolha o que quiser.")),LinkRandPhrase(LinkRandPhrase("E fico feliz em vê-lo novamente, "+GetAddress_Form(NPChar)+"! Comprando ou vendendo - estou sempre feliz em ajudar você.","Eu lhe imploro, "+GetAddress_Form(NPChar)+", entre! Sempre fico feliz em ver meu cliente favorito aqui. O que vai ser desta vez – comprar ou vender?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Que alegria te ver de novo! O que vai ser desta vez - comprar ou vender?"),LinkRandPhrase("Gostou dos nossos produtos, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Estou sempre ao seu dispor - dê uma olhada e faça sua escolha.","Olá, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Fico feliz em vê-lo novamente! Gostaria de dar uma olhada na nossa seleção de mercadorias?","Que bom ver você, capitão! Eu sabia que você ia valorizar nossos produtos de qualidade. Quer dar uma olhada nas novidades?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Por favor, entre! Todas as mercadorias são para você - e com ótimos descontos nesta ocasião!","Capitão "+GetFullName(pchar)+", mais uma vez você me alegrou com a sua visita! Por favor, escolha o que quiser, fique à vontade!","O que deseja desta vez, capitão? Fico feliz que ainda se lembre de como me encontrar. Temos todas as mercadorias que possa precisar – da melhor qualidade!")));
					link.l14 = "Escute, estou prestes a partir para Porto Bello agora e gostaria de comprar uma remessa de café e cacau com você. Digamos, trezentas unidades de cada."; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, veja só quem apareceu! Bem, como dizem, dinheiro não tem cheiro, então entre, capitão, e vamos negociar...","Não posso dizer que estou feliz em te ver, "+GetFullName(pchar)+"... Mas ainda posso negociar com você.","He-he... Bem, eu não o convidaria para minha casa, capitão – mas minha loja continua à sua disposição."),LinkRandPhrase("Oh, olha só quem está aí! Não é "+GetFullName(pchar)+"! Quer negociar ou só pegar umas coisas de graça? Ei, tô brincando...","Não posso dizer que estou feliz em te ver aqui, "+GetAddress_Form(NPChar)+". Mas se você tem dinheiro para gastar - entre, entre...","Quer negociar, capitão "+GetFullName(pchar)+"? Se for o caso, poderia se apressar, por favor? Os outros clientes estão te evitando, e isso prejudica meus negócios,"),LinkRandPhrase("Quer negociar, senhor? Só um instante, vou contar o dinheiro – sabe como é, tem uns tipos suspeitos por aí... Claro, não estou falando de você, capitão!","Se eu te visse em alto-mar, "+GetAddress_Form(NPChar)+", eu provavelmente encomendaria mais velas... Mas aqui, na minha loja, posso lhe oferecer uma troca.","Capitão, já vou avisando: se o tecido estiver manchado de sangue e o café cheirar a pólvora, não aceito. Fora isso, dê uma olhada e escolha o que quiser.")),LinkRandPhrase(LinkRandPhrase("Fico feliz em vê-lo novamente, "+GetAddress_Form(NPChar)+"! Comprar ou vender – estou sempre à disposição para ajudar você.","Eu te imploro, "+GetAddress_Form(NPChar)+", entre! Sempre fico feliz em ver meu cliente favorito aqui. O que vai ser desta vez - comprar ou vender?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Que alegria te ver de novo! O que vai ser desta vez - comprar ou vender?"),LinkRandPhrase("Gostou dos nossos produtos, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Estou sempre ao seu dispor - dê uma olhada e faça sua escolha.","Olá, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Fico feliz em vê-lo novamente! Gostaria de dar uma olhada na nossa seleção de mercadorias?","Que bom ver você, capitão! Eu sabia que ia apreciar nossos produtos de qualidade. Quer dar uma olhada nas novidades?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Por favor, entre! Todos os produtos são para você – e com ótimos descontos nesta ocasião!","Capitão "+GetFullName(pchar)+", mais uma vez você me alegra com sua visita! Por favor, fique à vontade, escolha o que quiser!","O que deseja desta vez, capitão? Fico feliz que ainda se lembre de como me encontrar. Temos todas as mercadorias de que possa precisar – da melhor qualidade!")));
				link.l14 = "Vim buscar café e cacau. "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Mostre o que você tem aí, seu velho pirata!","Eu só queria dar uma olhada nas suas mercadorias, meu bom homem."),pcharrepphrase("Eu juro pela forca, "+GetFullName(npchar)+", não vou deixar você me enrolar! Mostre suas mercadorias agora mesmo!","Vamos dar uma olhada nas suas mercadorias, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Isso é certo! Os mortos não mordem! Agora, o que você tem no seu porão?","É melhor você tratar dos seus negócios, meu bom homem. Que tipo de mercadorias pode me oferecer?"),pcharrepphrase("Vai chegar o dia em que você será meu prêmio, heh-heh. Brincadeira. Mostre-me o que tem à venda.","Vamos discutir nossos negócios, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("O que eu quero? Quero comprar alguma coisa!","Beber vai te levar pra cova, "+GetFullName(npchar)+". Quero dar uma olhada nas suas mercadorias."),pcharrepphrase("Eu conheço seus descontos! Dois quilos de cacau pelo preço de três! Agora me mostre suas mercadorias.","Isso é sempre bom. Então vamos negociar.")),"Mostre-me o que tem à venda. Quanto menos conversa, melhor. Estou com pressa.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Ah, eu adoraria esfaquear alguém. Certo, vamos ao que interessa.","Vamos tratar de outros assuntos, meu bom homem."),pcharrepphrase("Caramba! Estou aqui por outros motivos!","Quero conversar com você sobre um certo negócio, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Tenho negócios com você, velho pirata!","Vamos direto ao assunto, amigo!"),pcharrepphrase("Juro pelo diabo, você não vai me enganar, seu patife! Tenho outros assuntos com você!","Concordo plenamente, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", eu queria conversar sobre outros assuntos com você.")),NPCharRepPhrase(npchar,pcharrepphrase("Já está carregado? Tenho negócios com você.","Não vim aqui para negociar, meu bom homem. Tenho outros assuntos a tratar."),pcharrepphrase("Que um raio caia sobre você com esses preços! Tenho negócios com você.","Descontos são sempre bem-vindos, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", mas tenho outros assuntos para tratar com você.")),NPCharRepPhrase(npchar,pcharrepphrase("Fique quieto, seu velho bêbado, tenho negócios com você","Você está de ressaca de rum, imagino. Também não sou lá muito fã de você. Vamos ao que interessa."),pcharrepphrase("Você já me passou a perna, seu patife! Tenho assuntos a tratar com você.","Sua ironia é inadequada. Tenho outros assuntos para tratar com você.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Primeiro os negócios, depois a diversão. Quero te perguntar uma coisa.","Agora não. Preciso de informações."),pcharrepphrase("Que se dane o seu preço! Primeiro, você vai me contar tudo o que eu preciso saber.","Com prazer. Eu queria te perguntar uma coisa.")),NPCharRepPhrase(npchar,pcharrepphrase("Obrigado pelo conselho, velho assassino. Queria te perguntar uma coisa.","Eu tinha uma pergunta específica."),pcharrepphrase("O ouro pode esperar. Queria te perguntar uma coisa.","Sim, eu concordo. Queria te perguntar uma coisa.")),NPCharRepPhrase(npchar,pcharrepphrase("Acredito que você já sabe o que eu ia perguntar.","Espero que você responda à minha pergunta."),pcharrepphrase("Você consegue pensar em algo além das suas etiquetas de preço? Porque era exatamente sobre isso que eu ia te perguntar.","Isso não me interessa. Preciso de informações.")),NPCharRepPhrase(npchar,pcharrepphrase("Não se empolgue demais, amigo! Eu só ia te fazer uma pergunta.","Não se empolgue demais, ou vai acabar tendo um troço. Só responda uma pergunta, e eu vou embora"),pcharrepphrase("Não espero que você diga nada inteligente, já que tem cérebro de barata. Mas com certeza deve saber de alguma coisa.","Não vou tomar muito do seu tempo. Só uma pergunta.")),npchar,Dialog.CurrentNode);*/
			//link.l3 = "Estou resolvendo outra questão.";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Eu trouxe para você uma lista de preços da cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Gostaria de comprar um lote de vinho europeu com você – cinquenta ou sessenta garrafas. Disseram-me que você tem o suficiente em estoque.."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Olá novamente. Por favor, dê uma olhada nesta carta – talvez você reconsidere sua posição sobre me vender vinho?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Sou eu de novo. Podemos retomar nosso acordo de vinho interrompido? Consegui juntar dinheiro suficiente."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "Escute, monsieur, estou procurando um trabalho. Não uma vaga fixa ou trabalho pesado carregando carga, mas algo mais como fazer alguns serviços, por assim dizer. Por acaso você precisa de alguma ajuda?";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "Terminei sua tarefa. Encontrei Gralam Lavoie.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "Conheça seu novo assistente, monsieur.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "Sou eu de novo, monsieur. Vim buscar minha recompensa.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Dê uma olhada nesses brincos, monsieur. Encontrei-os no corpo de um bandido que foi morto na selva. É claramente obra de um joalheiro de talento, que, tenho certeza, não é daqui. Você pode me dizer algo sobre esses brincos?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Olá, vim a convite do seu filho."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Isto é sobre sua filha...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Até mais, velho bêbado.","Tenha um bom dia, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Não vá a lugar nenhum, eu já volto.","Foi bom ter você aqui, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Adeus!")),NPCharRepPhrase(npchar,pcharrepphrase("Soltem as amarras!","Adeus, meu bom homem."),pcharrepphrase("Ei! O que você está escondendo aí? Rum? Não? Tudo bem, vou ali molhar a garganta.","Me desculpe, mas tenho assuntos urgentes na cidade.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Então, até mais!","Preciso ir. Adeus, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("E nem pense em discutir comigo! Não tenho tempo pra isso!","Talvez eu deva ir ver o que está acontecendo no meu navio. Até logo, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("E aí, velho amigo? Sou eu - "+GetFullName(pchar)+"! Vai dormir, eu volto depois.","Receio que seu fígado vai acabar com você antes que eu tenha a chance de voltar a procurá-lo."),pcharrepphrase("Continue contando suas guinéus e dobrões, seu velho astuto! Eu volto depois.","Fiquei feliz em te ver, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "O que posso fazer por você? Abastecer o Rainbow, vender algum saque? Duvido que esteja interessado nas cargas lucrativas do momento, ha-ha.";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Mostre o que você tem, seu velho pirata!","Só queria dar uma olhada nas suas mercadorias, meu bom homem."),pcharrepphrase("Juro pela forca, "+GetFullName(npchar)+", não vou deixar você me ignorar! Mostre suas mercadorias agora mesmo!","Vamos dar uma olhada nas suas mercadorias, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Com certeza! Os mortos não mordem! Agora, o que você tem no porão?","É melhor você tratar dos seus negócios, meu bom homem. Que tipo de mercadorias pode me oferecer?"),pcharrepphrase("Vai chegar o dia em que você será meu prêmio, heh-heh. Brincadeira. Mostre-me o que tem à venda.","Vamos discutir nossos assuntos comerciais, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("O que eu quero? Quero comprar alguma coisa!","Beber vai te levar pra cova, "+GetFullName(npchar)+". Quero dar uma olhada nas suas mercadorias."),pcharrepphrase("Eu conheço seus descontos! Dois quilos de cacau pelo preço de três! Agora mostre suas mercadorias.","Isso é sempre bom. Então vamos negociar.")),"Mostre-me o que tem à venda. Quanto menos conversa, melhor. Estou com pressa.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Ah, eu adoraria esfaquear alguém. Certo, vamos ao que interessa.","Vamos tratar de outros assuntos, meu caro."),pcharrepphrase("Caramba! Estou aqui por outros motivos!","Quero conversar com você sobre um certo negócio, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Tenho negócios com você, velho pirata!","Vamos direto ao assunto, amigo!"),pcharrepphrase("Juro pelo diabo, você não vai me enganar, patife! Tenho outros assuntos com você!","Concordo plenamente, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", eu queria conversar sobre outros assuntos com você.")),NPCharRepPhrase(npchar,pcharrepphrase("Já está de partida? Tenho assuntos para tratar com você.","Não vim aqui para negociar, meu bom homem. Tenho outros assuntos a tratar."),pcharrepphrase("Que um raio caia sobre você por esses preços! Tenho negócios com você.","Descontos são sempre bem-vindos, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", mas tenho outros assuntos para tratar com você.")),NPCharRepPhrase(npchar,pcharrepphrase("Segure a língua, seu velho bêbado, tenho negócios com você","Você está de ressaca de rum, imagino. Não que eu goste muito de você também. Vamos ao que interessa."),pcharrepphrase("Você já me passou a perna, seu patife! Tenho assuntos a tratar com você.","Sua ironia é inadequada. Tenho outros assuntos com você.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Primeiro os negócios, depois a diversão. Quero te perguntar uma coisa.","Agora não. Preciso de informações."),pcharrepphrase("Que se dane o seu preço! Primeiro, você vai me contar tudo o que eu preciso saber.","Com prazer. Eu queria te perguntar uma coisa.")),NPCharRepPhrase(npchar,pcharrepphrase("Obrigado pelo conselho, velho assassino. Queria te perguntar uma coisa.","Eu tinha uma pergunta específica."),pcharrepphrase("O ouro pode esperar. Eu queria te perguntar uma coisa.","Sim, eu concordo. Queria te perguntar uma coisa.")),NPCharRepPhrase(npchar,pcharrepphrase("Acredito que você já sabe o que eu ia perguntar.","Espero que você responda à minha pergunta."),pcharrepphrase("Você consegue pensar em algo além das suas etiquetas de preço? Porque era justamente sobre isso que eu ia te perguntar.","Isso não me interessa. Preciso de informações.")),NPCharRepPhrase(npchar,pcharrepphrase("Não se empolgue demais, camarada! Eu só ia te fazer uma pergunta.","Não se empolgue demais, ou vai acabar tendo um troço. Só responda uma pergunta, e eu vou embora."),pcharrepphrase("Não espero que você diga nada inteligente, já que tem cérebro de barata. Mas com certeza deve saber de alguma coisa.","Não vou tomar muito do seu tempo. Só uma pergunta.")),npchar,Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Até mais, velho bêbado.","Tenha um bom dia, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Não vá a lugar nenhum, eu já volto.","Foi um prazer ter você aqui, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Adeus!")),NPCharRepPhrase(npchar,pcharrepphrase("Soltem as amarras!","Adeus, meu bom homem."),pcharrepphrase("Ei! O que você está escondendo aí? Rum? Não? Tudo bem, vou ali molhar a garganta.","Me desculpe, mas tenho assuntos urgentes para resolver na cidade.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Então, até mais!","Preciso ir. Adeus, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("E nem pense em discutir comigo! Não tenho tempo pra isso!","Talvez eu deva ir ver o que está acontecendo no meu navio. Até logo, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("E aí, velho camarada? Sou eu - "+GetFullName(pchar)+"! Vai dormir, eu volto depois.","Receio que seu fígado vai acabar com você antes que eu tenha a chance de voltar aqui."),pcharrepphrase("Continue contando suas guinéus e dobrões, seu velho astuto! Eu volto depois.","Fiquei feliz em te ver, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Desculpe, mas estou muito ocupado agora. Muitos clientes! Volte amanhã.";
				link.l1 = "Ah, é mesmo? Então volto mais tarde.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("Tenho balas de canhão, lonas, remédios, madeira de lei e outras mercadorias! O que lhe interessa?","Quer comprar açúcar e especiarias? Ou talvez rum e pólvora?");
			link.l1 = pcharrepphrase(LinkRandPhrase("Tenho um monte de saque no meu porão! Dinheiro não tem cheiro, não é?","Preciso esvaziar meu porão do saque e enchê-lo com o seu ouro. Ha-ha!","Ah, eu sei que você venderia até sua mãe por um saco de dobrões pesados! Mas eu só preciso reabastecer meus suprimentos."),LinkRandPhrase("Quero vender minha carga e reabastecer os suprimentos.","Quero comprar mercadorias para revenda.","Mostre-me as balas de canhão, bombas e coisas desse tipo."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "Meu intendente fará todas as compras necessárias...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("Vou embora sem fechar negócio. Até mais!","Vou ali molhar a garganta. Fique aí!"),RandPhraseSimple("Não, no momento não tenho tempo para negociar. Até logo.","Me desculpe, tenho assuntos urgentes para resolver. Adeus!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "Estou ouvindo.";
			link.l1 = "Trouxe o seu fugitivo.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitão, muito obrigado! Como ela está? Ela se machucou? Já faz um dia que ela fugiu, essa menina teimosa. Eu pareço alguém que faria mal a ela? Arrumei um marido para ela. Um casamento acertado. Um noivo jovem e rico. Pode não ser grande coisa de aparência, mas quem liga pra isso? Não! Ela sempre quer fazer tudo do jeito dela. Igualzinha à mãe, sempre foi assim, droga!\nEmbora, ela nem teria nascido se a mãe não tivesse fugido com algum tolo promissor anos atrás... bem, tanto faz... A juventude é ingênua, tola e cruel.";
			link.l1 = "Claro, você é o pai e cabe a você decidir, mas eu não me apressaria com o casamento...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "O que você sabe? Você tem filhos? Não? Então venha falar comigo quando tiver...\nSim... Eu prometi uma recompensa para quem a trouxesse de volta. Aqui, pegue.";
			link.l1 = "Obrigado. E fique de olho nela. Tenho um pressentimento de que ela não vai parar por aí.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, então você é "+GetSexPhrase("aquele capitão que trouxe","aquela moça que trouxe")+" meu filho pródigo com uma jovem esposa?";
				link.l1 = "Sim, eu os ajudei a escapar.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, aí "+GetSexPhrase("ele é, nosso benfeitor","Ela é, nossa benfeitora")+". Esperando uma recompensa, é isso?";
				link.l1 = "Bem, eu fico bem sem recompensa, mas só o seu agradecimento já basta.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sou muito grato a você por não abandonar meu filho em um momento tão difícil e por ajudá-lo a encontrar uma saída para essa situação delicada. Permita-me agradecer e, por favor, aceite esta quantia modesta e um presente meu, pessoalmente.";
			link.l1 = "Obrigado. Foi um prazer ajudar esse jovem casal.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Obrigado? Que obrigado?! Aquele cabeça-oca está vagabundeando sem trabalho há meio ano – e olha só, ainda arranja tempo pra namoricos! Quando eu tinha a idade dele, já tocava meu próprio negócio! Pff! O governador tem uma filha em idade de casar – e esse paspalho me aparece com uma moça sem família nem raízes e ainda tem a ousadia de pedir minha bênção!";
			link.l1 = "Hmm... Pelo visto, você não acredita em sentimentos verdadeiros?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Que sentimentos? Que tipo de sentimentos você está falando? Sentimentos... como alguém pode ser tão irresponsável na sua idade?! Que vergonha, incentivando os jovens em seus caprichos e agindo como um intermediário! Você não só tirou uma moça de sua casa, como também arruinou a vida do meu novato. Não espere agradecimentos. Adeus.";
			link.l1 = "Certo, pra você também...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...Já está feito. Agora só falta decidir em qual navio carregar.","Seu tesoureiro já cuidou disso. Agora vamos decidir qual navio será carregado.","Sim, "+PChar.name+", eu sei. Ele já veio falar comigo. Agora, em qual navio vamos carregar?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99 = "Mudei de ideia, não preciso de mais nada.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Você está brincando comigo? Cadê o seu navio? Não estou vendo ele no cais!","Juro pelo diabo, você não vai me enganar! Seu navio não está no cais!"),pcharrepphrase("Não vejo seu navio no porto, Capitão "+GetFullName(pchar)+". Espero que ela não seja o 'Holandês Voador'?","Capitão, é muito mais fácil carregar a carga do cais. E eu prefiro fazer assim. Traga seu navio rápido e volte."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Que incômodo! Tudo bem, velho espertalhão, até logo!","Eu não queria te enganar, "+GetFullName(npchar)+", tem um navio do outro lado da ilha."),pcharrepphrase("Não. Meu navio se chama 'Pérola Negra.' Por que ficou pálido? Haha! Só brincando!","Obrigado pelo conselho, vou fazer bom uso dele."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("Então, capitão, em qual navio vamos carregar?","Então, qual navio deve ser carregado, afinal?",PChar.name+", em qual porão de navio devemos carregar as mercadorias?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99 = "Mudei de ideia, não preciso de nada.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Tudo pronto! O carregamento do navio selecionado já começou.","Certo, o carregamento das mercadorias no navio selecionado já começou.","Capitão, o carregamento das mercadorias para o navio selecionado já começou.");
					link.l1 = "Obrigado. Foi um prazer fazer negócios com você.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Capitão, todas as mercadorias solicitadas pelo seu tesoureiro já estão a bordo do navio que você indicou!","Capitão, todas as mercadorias já estão a bordo do navio que você indicou!","Capitão, esse navio não precisa de manutenção, já que todas as mercadorias já estão lá.");
					link.l1 = "É, tá bom.";
					link.l1.go = "exit";
					link.l2 = "Acho que vou ter que escolher outro navio, então.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Receio que um navio desse tipo simplesmente não pode carregar tanto assim.","Capitão, seu navio não consegue carregar tanta carga assim!","Capitão, o porão do seu navio não aguenta tanta carga!");
				link.l1 = "É, você tem razão. Vou precisar escolher outro navio.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "Estive pensando... Não preciso comprar nada.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Você está brincando comigo? Cadê o seu navio? Não estou vendo ele no cais!","Juro pelo diabo, você não vai me enganar! Seu navio não está no cais!"),pcharrepphrase("Não vejo seu navio no porto, Capitão "+GetFullName(pchar)+". Espero que ela não seja o 'Holandês Voador'?","Capitão, é muito mais fácil carregar a carga do cais. Traga seu navio rápido e volte."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Que incômodo! Tudo bem, velho esperto, até logo!","Eu não queria te enganar, "+GetFullName(npchar)+", tem um navio do outro lado da ilha."),pcharrepphrase("Não. Meu navio se chama 'Pérola Negra.' Por que ficou pálido? Haha! Só brincando!","Obrigado pelo conselho, eles vão aproveitar."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "Quanto ao aluguel, você ainda me deve "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Certo, vou pagar o aluguel agora.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Vou voltar mais tarde.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Entre.";
				link.l1 = "Obrigado.";
				link.l1.go = "storage_2";
			}
			link.l2 = "Não, mudei de ideia.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Sim, eu tenho um armazém no porto – ele pode guardar 50.000 centenários de carga. Por "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+" por mês, posso guardar suas mercadorias em segurança. "+"Isso inclui vigilância, proteção contra enchentes e lidar com os ratos. O que me diz? Ah, e... vou precisar de um mês de pagamento adiantado.";	
			link.l1 = "Fato. Posso dar uma olhada? Tem muitos ratos por lá?";
			link.l1.go = "storage_1";
			link.l2 = "Não, só estou perguntando. Posso usar quando for necessário...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Como eu disse, exijo pagamento com um mês de antecedência. E nada de ratos!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Você é... bastante mercantil, devo dizer. Aqui está o seu dinheiro - vou alugar este galpão.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Você é... bem mercantil, devo dizer. Certo, voltarei em breve com o dinheiro.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Já vai embora? Que pena – este lugar é realmente excelente, com condições ótimas. Garanto que não vai encontrar um negócio assim em nenhum outro lugar do Caribe.";
			link.l1 = "Eu disse - quite. Ou está sugerindo que eu pague para guardar ar? Procure outro locatário.";
			link.l1.go = "storage_4";
			link.l2 = "Em lugar nenhum no Caribe, é isso? Tudo bem, vou deixar isso de lado por um tempo, então.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "E quanto ao aluguel, você ainda me deve "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Certo.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Recolha seus produtos, e eu fecharei o armazém.";
				link.l1 = "Certo.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> генератор Сомнительное предложение
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "Oh! Chegou na hora certa, Capitão. Gostaria de lhe pedir um favor.";
					link.l1 = "Vamos ouvir."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "Estou ouvindo, capitão.";
				link.l5 = "Trouxe o seu pedido."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "Oh! Chegou na hora certa, Capitão. Preciso de um favor especial.";
				link.l5 = "Vamos ouvir."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "Estou ouvindo, capitão.";
				link.l5 = "Trouxe os escravos para você."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Escute, você lida com todo tipo de mercadoria... Ontem ou hoje – alguém tentou lhe vender "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block")) 
			{
				dialog.text = "Capitão, gostaria de lhe pedir um favor, e estou disposto a pagar muito bem, caso aceite.";
				link.l1 = "Interessante. Bem, qual é o problema?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Capitão, que bom vê-lo. Já sei que você atendeu ao meu pedido sobre "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Hein! Isso com certeza. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" e a carga - "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+", não pertencem mais ao seu rival."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Meu Deus, Capitão... Por que você matou ele? Eu só pedi pra afundar o navio dele! Santa Virgem, agora tenho o sangue de um homem inocente nas minhas mãos...";
				link.l1 = "Hein! O que há com você, "+npchar.name+"? Quem se importa – ele nunca mais vai te incomodar, e é isso que importa!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Eu tinha um trabalho, mas "+GetFullName(&Characters[iTmp])+" já se comprometeu a fazer isso por mim.";
				link.l1 = "Ah, é mesmo? Então, volto mais tarde.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Que negócio?! Me conte tudo!","Estou ouvindo. Que negócio é esse de que você está falando?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("Tenho um lote de mercadorias para sua loja no porão do meu navio.","Meu navio foi contratado para entregar as mercadorias à sua loja. Os produtos estão sendo descarregados agora.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "Infelizmente, sou obrigado a abandonar meus compromissos. A situação política não me permite entregar as mercadorias.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Posso oferecer meu navio para transporte de carga.","Tenho um ótimo navio e posso entregar qualquer carga onde você precisar.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Gostaria de fretar um navio, "+GetAddress_FormToNPC(NPChar)+"? Tenho um navio confiável e uma tripulação experiente.";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "Estou tratando de outro assunto.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Ah, eu estava realmente exausto no mar... Olha, amigo, dinheiro está sendo um problema sério pra mim agora.","Certo, velho lobo, vamos conversar sobre nossos negócios."),RandPhraseSimple("Gostaria de discutir questões financeiras com você.","Vamos discutir questões financeiras, precisamos falar sobre isso."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("Estou aqui a pedido de um homem. O nome dele é Governador "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" me enviou até você. Disseram que era para eu buscar alguma coisa...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Pode me contar as últimas fofocas? Você passa o dia todo por aqui mesmo.","Não faça drama, seu velho trapaceiro – é melhor me contar as novidades em terra firme?"),RandPhraseSimple("Parece que passei uma eternidade no mar. O que há de novo por aqui?","Você provavelmente está por dentro das últimas novidades? O que de importante aconteceu?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Leve-me até o armazém. Quero ver em que estado ele está.";
						link.l7.go = "storage_0";
						link.l8 = "Decidi liberar o armazém. Não preciso dele agora.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Com licença, meu bom homem – por acaso você aluga armazéns?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Veja, estou tentando encontrar meu companheiro, "+pchar.GenQuest.FindFugitive.Name+" é o nome dele. Em Port Royal, o pessoal da taverna me disse que ele estava vindo para o seu assentamento. Por acaso você chegou a encontrá-lo?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "Mas não temos tempo para conversar agora.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Deixei o navio do outro lado da ilha. Volto mais tarde!","Me desculpe, "+GetFullName(npchar)+", vou voltar depois. Meu navio ainda não chegou ao cais."),pcharrepphrase("Diabos! Esses idiotas não prepararam o navio para o carregamento! Vou voltar mais tarde!","Com licença, preciso dar ordens para atracar meu navio no cais!"));
                link.l1.go = "exit";
				link.l22 = "Estou tratando de outro assunto.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Ah, eu estava realmente exausto no mar... Olha, amigo, dinheiro é um problema sério pra mim agora.","Certo, velho lobo, vamos conversar sobre nossos negócios."),RandPhraseSimple("Gostaria de discutir questões financeiras com você.","Vamos conversar sobre os assuntos financeiros que precisamos tratar."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("Estou aqui a pedido de um homem. O nome dele é Governador "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" me mandou até você. Disseram que era pra eu buscar alguma coisa...");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Veja, estou tentando encontrar meu companheiro, "+pchar.GenQuest.FindFugitive.Name+" é o nome dele. Em Port Royal, o pessoal da taverna me disse que ele estava vindo para o seu povoado. Por acaso, você chegou a encontrá-lo?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Não, eu não preciso dos seus serviços! Pelo menos, não enquanto você for inimigo de "+NationNameAblative(sti(NPChar.nation))+".";
					link.l1 = "Nesse caso, adeus.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear()+"Você é "+GetFullName(pchar)+", não é? Dizem que "+RandPhraseSimple("muitas coisas assustadoras sobre você","muitas coisas feias sobre você")+", e eu não quero lidar com você.";
						link.l1 = RandPhraseSimple("Claro – basta errar uma vez para todo mundo cuspir em você.",RandSwear()+"Bem, há coisas melhores para se fazer no mar, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar,"Heh, "+GetAddress_Form(NPChar)+", hoje não tenho tempo para fretes. Volte amanhã.","Volte amanhã. Talvez eu faça uma oferta vantajosa para você.");
						link.l1 = "Certo, volto amanhã.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar,"O seu barquinho miserável não aguenta o lote inteiro, então hoje não vai ter negócio.","Infelizmente, capitão "+GetFullName(pchar)+", vou precisar de um navio maior para a minha entrega.");
    							link.l1 = NPCharRepPhrase(npchar,"Meu navio é decente, mas entendi o seu ponto. Adeus.","Entendo seu ponto, negócios são negócios. Até logo.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", which is on " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Voc");
                                }
                                dialog.text = "Oh! Eu estava prestes a te pedir um favor. Veja, preciso entregar a carga de "+GetGoodsNameAlt(iTradeGoods)+" no valor de "+FindRussianQtyString(iQuantityGoods)+" para a cidade de "+sNation+sTemp+", e quanto antes, melhor. Se você conseguir fazer isso até "+FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired))+", então ao chegar você receberá "+FindRussianMoneyString(iMoney)+" como sua recompensa. O que me diz?";
    							link.l1 = "Acho que concordo.";
    							link.l1.go = "exit_trade";
    							link.l2 = "Isso provavelmente não é para mim.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "As realidades políticas no arquipélago não me permitem negociar. "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter")+" é hostil com todos e deixou só eu na loja.";
    						link.l1 = "Oh! Me desculpe. Boa sorte.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,"Cai fora, não tenho tempo pra conversa fiada!","Já te disse que não tenho nada para você.");
				link.l1 = NPCharRepPhrase(npchar,"Seja educado, ou eu mesmo vou te ensinar boas maneiras!","Ah, me desculpe!");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear()+"Você não acha que lembrou desse acordo um pouco tarde demais? Tive que encomendar as mercadorias de novo. Adeus.";
				link.l1 = "Me perdoe, mas eu estava com pressa. Talvez se eu cobrir seu prejuízo, minha reputação seja restaurada?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Tudo de bom.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "De fato! Já faz um bom tempo que estou esperando por isso. Você precisa me entregar uma carga de "+GetGoodsNameAlt(iTradeGoods)+" no valor de "+FindRussianQtyString(iQuantityGoods)+" e receber por isso "+FindRussianMoneyString(sti(pchar.CargoQuest.iMoney))+".";
				link.l1 = "Exatamente.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear()+"Preciso lhe pedir desculpas, "+GetAddress_Form(NPChar)+".  Veja, o problema é que eu estava "+RandPhraseSimple("numa situação embaraçosa e não vou conseguir te pagar"," já comprei essa carga de outro fornecedor por um preço melhor")+". Como pagamento pelo seu fretamento, sugiro que fique com toda a carga que estava entregando.";
				link.l1 = RandSwear()+RandPhraseSimple("E eu tenho protegido essa maldita carga de todo tipo de perigo! Matei duzentos ratos por causa disso!","Você me colocou em um impasse, então devo concordar.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "Isso não é o lote inteiro! Pelo nosso acordo, eu preciso "+FindRussianQtyString(iTmp)+" unidades a mais.";
				link.l9 = RandPhraseSimple("Sim, de fato. Vou ter que compensar a falta então. Até mais.",RandSwear()+"Esses malditos ratos estragaram a carga. Vou compensar a falta e devolver.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Excelente! Aqui está sua recompensa, capitão "+GetFullName(pchar)+".";
				link.l1 = "Foi um prazer trabalhar com você.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Certo... A soma de "+FindRussianMoneyString(iMoney)+" só cobrirei os danos causados pela violação dos termos do nosso acordo.";
			link.l1 = "Que droga! Não, assim não dá! Nunca mais vou entregar nenhuma carga! Já tem porcaria demais no mar!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Aqui está a quantia exigida";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Excelente. Agora posso dizer aos meus colegas que você ainda é uma pessoa razoável para se negociar.";
			link.l1 = "Obrigado! Não vou decepcioná-lo de novo.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Hum. Ouvi dizer que você não cumpriu suas obrigações no contrato anterior – e agora está pedindo outro? Era para você ter entregue a carga de "+GetGoodsNameSeaSection(&Goods[iTradeGoods])+" to "+XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony)+".";
			link.l1 = "Sim, de fato! Você está certo!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear()+GetAddress_Form(NPChar)+", você está me decepcionando!!! Talvez pudesse fazer algo para resolver essa situação?";
			link.l1 = "Certo. Vou fazer o possível para entregar a encomenda.";
			link.l1.go = "exit";
			link.l2 = "Não, não posso. Me desculpe";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Espere! Não há mercadorias suficientes a bordo do seu navio! Você não tem "+FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar,iTradeGoods))+" unidades de carga.";
				link.l9 = RandPhraseSimple("Sim, de fato. Vou ter que compensar a falta então.",RandSwear()+"Os ratos estragaram a carga. Vou comprar o que falta e devolver.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Entendi, entendi... Vou levar a carga de volta.";
    			link.l1 = "Obrigado! Eu não vou decepcionar você de novo!";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "Do que você está falando? Com certeza te enganaram – eu nunca negociei vinho europeu em tais quantidades. Uma ou duas garrafas, no máximo. Mas o vinho local é outra história – disso eu tenho de sobra, e vendo por galão, não por garrafa!";
			link.l1 = "Maldição! Mas me disseram...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "Não faço ideia do que te disseram, mas vou repetir: não tenho vinho europeu em estoque. É só isso que tenho a dizer sobre esse assunto.";
			link.l1 = "Certo... Eu vou resolver isso então, então!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Agora, isso já é outra história. Sabe, todo tipo de gente aparece aqui, fazendo perguntas desnecessárias. Então, vamos negociar, certo?";
			link.l1 = "Claro!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "Quantas garrafas você precisa? O preço de cada garrafa é 500 pesos, e o lote mínimo é de 20 garrafas.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "Eu não tenho dinheiro suficiente agora. Vou voltar mais tarde.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "Eu não sou um camelô, capitão. Se bem me lembro, você estava falando de um lote maior?";
				link.l1 = "Me desculpe... Então, vamos reconsiderar o valor.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "Infelizmente, não tenho tanto assim.";
				link.l1 = "Que pena... Então vamos reconsiderar o valor.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" Garrafas? Tudo bem. Isso vai te custar "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Aqui está.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "Não tenho dinheiro suficiente agora. Volto mais tarde.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "Tudo bem, mas tente não demorar muito. Essas mercadorias são bem procuradas por aqui.";
			link.l1 = "Volto já!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Vamos ver... Parece que está tudo certo. Pode retirar sua compra.";
			link.l1 = "Obrigado! Boa sorte!";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("You have received wine");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "Eu planejava fechar um bom negócio, mas ainda preciso de um item específico para isso - "+GetGoodsNameAlt(iCGood)+". O problema é que essa mercadoria é contrabando na nossa colônia, então não posso contar em comprá-la de capitães mercantes\nTudo que eu preciso são "+FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty))+" unidades disso. Talvez você possa me entregar? Vou pagar muito bem, "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price))+" por unidade, o que vai totalizar "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". Ah, e eu preciso disso até, no máximo, "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+". Então, vai me ajudar?";
			link.l1 = "Hmm... Parece interessante. Eu concordo!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Entregar mercadorias de contrabando? Desculpe, não me interessa.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Excelente. Fico feliz que tenha concordado. Então, estarei esperando seu retorno com as mercadorias.";
			link.l1 = "Eu volto já!";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "Está brincando? Você não tem toda a mercadoria que eu preciso!";
				link.l1 = "Desculpe, foi um erro meu...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Vamos ver, então. Você deveria ter entregue uma carga de "+GetGoodsNameAlt(iCGood)+" no valor de "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty)+". Correto?";
				link.l1 = "Exatamente, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Obrigado pelo seu trabalho. Por favor, aceite seu pagamento - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+".";
		link.l1 = "Muito obrigado! Foi um prazer fazer negócios com você.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "Opa... Capitão, parece que temos um problema aqui...";
				link.l1 = "O que é mesmo?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "Eu preciso urgentemente de um lote de escravos - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" cabeças. Estou pronto para pagar "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" moedas por alma, o que dará um total de "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" pesos in total; term - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "Acho que vou concordar. É um negócio trabalhoso, mas muito lucrativo.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "Não estou interessado.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Exatamente - é realmente muito lucrativo. Pois bem, estarei esperando seu retorno com meus escravos.";
			link.l1 = "Não vou te fazer esperar muito. Até logo!";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "Está brincando? Você não tem todos os escravos que eu preciso!";
				link.l1 = "Me desculpe, foi um erro meu...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Vamos ver, então. Você ia me entregar um lote de escravos no valor de "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty)+". Correto?";
				link.l1 = "Exatamente, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Obrigado pelo seu trabalho. Por favor, aceite seu pagamento - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money))+". Além disso, por favor, aceite isto. Tenho certeza de que será útil para você.";
			link.l1 = "Muito obrigado! Foi um prazer fazer negócios com você.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nunca ouvi falar disso antes... O que é, afinal? Nunca ouvi falar de algo assim em todo o meu tempo.";
			link.l1 = "Bem, é uma ferramenta de carpinteiro naval, "+pchar.GenQuest.Device.Shipyarder.Describe+". Alguém já lhe ofereceu algo assim?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Hum... É, apareceu um sujeito estranho. Mas ele não me disse o que era aquilo, só tentou me vender. Mas pra que eu ia querer aquilo, se nem faço ideia pra que serve? Como é que eu ia revender? Então, só recusei.";
				link.l1 = "E como ele era, e para onde foi? Eu preciso muito desse instrumento.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Não, nada disso. Desculpe, não posso te ajudar. Pergunte por aí.";
				link.l1 = "Entendi. Bem, hora de perguntar por aí!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "Concorrência... Não existe negócio sem ela. Uns desgraçados gananciosos que fazem de tudo pra se enfiar no seu comércio e usam todo tipo de artimanha pra roubar sua clientela.\nMas isso é só conversa. Na verdade, queria te pedir pra me ajudar a me livrar de um dos meus concorrentes. Não, não precisa matar ninguém. Só capture ou afunde o navio dele junto com a carga.";
			link.l1 = "Hmm... bem, se você pagar bem, posso providenciar isso.";
			link.l1.go = "Sunplace_1";
			link.l2 = "Não, não vou me meter nas suas disputas comerciais. Vá afundar seu rival sem a minha ajuda.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "Muito bem. Então, o nome do seu homem é "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Recentemente ele havia enviado "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")+"Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"' com uma carga de "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+". Ele pagou uma quantia considerável por essa carga, então perdê-la vai ser um golpe e tanto para o bolso dele.";
			link.l1 = "E poderia me dizer exatamente onde devo procurar esse seu 'amigo'?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "Meu 'amigo' está atualmente em sua casa em "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+". Você não precisa dele - você precisa do navio dele, que, como descobri depois de cerca de "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" vai passar perto "+XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen")+". Você pode afundá-lo ou tomar o navio de assalto – tanto faz. O principal é garantir que o navio e a carga não sejam mais propriedade de "+pchar.GenQuest.Sunplace.Trader.Enemyname+". E não me importa quem vai reivindicar isso - você ou o mar. Por esse serviço, eu vou te pagar "+FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))+".";
			link.l1 = "Entendi. Bem, hora de partir então!";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "Excelente! Eu sabia que podia contar com você. Acho melhor nem perguntar onde está aquele navio e a carga dele. No fim das contas, isso não é da minha conta. E meu amigo vai precisar de um bom tempo pra se recuperar de um golpe desses, heh-heh. Aqui, por favor, pegue seu dinheiro – e obrigado pelo ótimo trabalho.";
			link.l1 = "De nada... Até logo, "+npchar.name+"!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Pobre "+pchar.GenQuest.Sunplace.Trader.Enemyname+", que destino terrível! E mesmo que indiretamente, fui eu quem causou a morte dele! Você não entende, capitão! Eu pedi pra você matá-lo? Eu planejava que, depois do prejuízo com a carga, ele teria que... bem, deixa pra lá... Você...";
			link.l1 = "Ei, escuta aqui – para de reclamar, tá bom? Você me pediu pra dar um fim no seu rival – e eu fiz isso. Melhor ainda – se ele só tivesse perdido a carga, podia acabar ficando rico de novo e continuaria atrapalhando seus negócios. Agora, morto do jeito que está, não pode fazer mais nada.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "Chega! Basta! Não quero mais ouvir esses discursos blasfemos! Pegue seu maldito dinheiro e saia da minha loja agora mesmo!";
			link.l1 = "Oi, "+npchar.name+", calma, está bem? Ou eu mesmo vou esfriar esse seu temperamento – minha espada está sempre ao meu lado! Tudo bem, não se assuste, era só uma brincadeira. Olha, sinto muito que tenha acabado assim – mas foi você quem me enganou primeiro. Adeus.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"Sim, eu conheço ele. Comprou mantimentos para o bote comigo. De dia, costuma pescar em enseadas isoladas, mas toda noite você o encontra na taverna.","Você já me perguntou sobre esse homem, e eu já lhe contei tudo o que sabia!","Você está brincando comigo, ou é realmente um idiota?! Você já está fazendo as mesmas perguntas pela terceira vez!","Só de pensar, como é que um idiota desses virou capitão...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Muito obrigado, você me ajudou demais!","Tá, tá bom.","Calma, calma, não se empolgue tanto. Eu só esqueci.","Bem, ele fez isso, como você pode ver...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Eu não sei o que andaram dizendo na taverna de Port Royal, mas nunca vi esse homem na minha loja. Na verdade, nunca o vi em lugar nenhum. Pergunte pelo vilarejo — talvez alguém possa te contar...","Você já me perguntou sobre esse homem, e eu já disse: não sei!","Você está brincando comigo ou é mesmo um idiota?! Já está fazendo as mesmas perguntas pela terceira vez!","Só de pensar, como é que um idiota desses virou capitão...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Entendi. Bem, obrigado mesmo assim.","Tá, tá, tudo bem.","Calma, calma, não se empolgue tanto. Eu só esqueci.","Bem, ele fez isso, como você pode ver...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		// belamour legendary edition -->
		case "trial":
			dialog.text = "Meu senhor, o que há com você, rapaz! Por favor, seja mais comedido e escolha melhor suas palavras ao falar de pessoas respeitáveis! Gerard LeCroix partiu da Guadalupe em uma expedição para o continente, mas deixou aqui sua recompensa. Está satisfeito agora?";
			link.l1 = "Hm... Por favor, me desculpe, monsieur. Me empolguei um pouco...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Muito bem. Monsieur Lecroix deixou sua recompensa com o faroleiro local – eles são velhos amigos. Basta visitá-lo para receber seu pagamento. Monsieur Lecroix é um homem honesto, então acredito que você ficará satisfeito com sua recompensa.";
			link.l1 = "Entendi, obrigado! Então vou falar com o faroleiro. Agora deixa eu descansar um pouco.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "Sim, ele esteve aqui, esperando por você. Mas talvez a tarefa que ele lhe confiou tenha sido mais difícil do que esperava, então ele não quis esperar e partiu em uma expedição para o continente. Ele deixou sua recompensa com uma pessoa de confiança.";
			link.l1 = "Sim, realmente tive imprevistos, mas consegui concluir a tarefa. Fico feliz em saber que meu pagamento está me esperando. Com quem devo recebê-lo?";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "O Sr. Lecroix deixou sua recompensa com o faroleiro local – eles são velhos amigos. Você só precisa visitá-lo e pegar seu pagamento. Monsieur Lecroix é um homem honesto, então acredito que ficará satisfeito com sua recompensa.";
			link.l1 = "Entendi, obrigado! Então vou falar com o faroleiro. Agora deixa eu descansar um pouco.";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "Boa sorte, monsieur.";
			link.l1 = "...";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- legendary edition
		/*case "trial":
			dialog.text = "Deus do céu, por que você fala tão alto, rapaz! Acalme-se e cuide das palavras ao falar de pessoas respeitáveis! Gerard LeCroix partiu da Guadalupe em uma expedição para o continente, mas deixou um recado para você\nJá se acalmou, senhor? Pronto para me ouvir?";
			link.l1 = "Hm... Por favor, me desculpe, monsieur. Me exaltei um pouco. Estou ouvindo.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Muito bem. Da próxima vez, tente perguntar antes, e só depois grite. Certo... Você conhece um homem chamado Simon Maurois?";
			link.l1 = "Ha! Todo mundo já ouviu falar de Simon Maurois! Claro que eu conheço ele.";
			link.l1.go = "trial_2";
			link.l2 = " Nunca ouvi falar dele. Quem é ele? ";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Excelente. Então vá até ele. Foi ele quem financiou a expedição do monsieur Shoke, então pode receber sua recompensa com ele. Mas me diga, era mesmo necessário se exaltar tanto assim?";
			link.l1 = "Mais uma vez, peço desculpas... Obrigado pela sua ajuda, monsieur. Vou ver o monsieur Maurois imediatamente!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "Ele é o dono da casa bancária Maurois e o chefe da filial em Capsterville. Então você vai precisar ir até Saint-Christopher e visitar o banco de Capsterville. Foi o Monsieur Maurois quem financiou a expedição do Monsieur Shoke, então você pode receber sua recompensa com ele. Então, era mesmo necessário ficar tão nervoso assim?";
			link.l1 = "Mais uma vez, peço desculpas... Muito obrigado pela sua ajuda, monsieur. Vou ver o monsieur Maurois imediatamente!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition на пару с Акулой -->
		case "SharkGoldFleet":
			dialog.text = "Ah, o comerciante empreendedor! Vejo logo que você entende de negócios. Respeito isso. Claro, tenho as mercadorias que você precisa.";
			link.l1 = "Tenho certeza de que consigo vender isso com lucro. Pelo que sei, há boa procura por essa mercadoria em Porto Bello. Quanto vai me custar?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "Mais ou menos... Então, trezentas unidades de café... E a mesma quantidade de cacau... Isso vai te custar..."+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_COFFEE,PRICE_TYPE_BUY,pchar,300)+GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_CHOCOLATE,PRICE_TYPE_BUY,pchar,300))+" pesos!";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Hmm... Com licença, parece que não tenho dinheiro suficiente. Espere um pouco, por favor: vou até o navio pegar mais dinheiro agora mesmo – e já volto!";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Aqui está.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "Espere um pouco, senhor. Parece que não há espaço suficiente no seu navio para uma festa dessas. Esvazie o porão e volte.";
				link.l1 = "Ah, esqueci de descarregar! Espere um instante – já vou aí!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ótimo! Vou dar a ordem imediatamente para que as mercadorias sejam carregadas no seu navio. É um prazer fazer negócios com você!";
				link.l1 = "Mutuamente, señor! Agora permita-me retirar-me: as coisas não esperam.";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = "As mercadorias estão esperando por você. Trouxe o dinheiro?";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Ainda não. Só queria ter certeza de que sua oferta ainda está de pé. E o dinheiro vai chegar em breve.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Aqui está.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "No momento, não preciso dos seus serviços.";
			link.l1 = "Que pena. Vamos mudar de assunto.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
