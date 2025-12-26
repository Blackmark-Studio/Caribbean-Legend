// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Eu devo ir...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "Pelo amor de Deus, quem diabos é você?";
				link.l1 = "Bom dia, don Lope. Embora ainda não tenhamos sido apresentados, agora é tão bom momento quanto qualquer outro. Principalmente agora que estou tão disposto a ajudá-lo a sair dessa situação difícil...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "O que você quer?";
				link.l1 = "Eu devo ir...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Ajuda? Eu? Que reviravolta! Poderia me dizer, senhor, de onde vem tanta generosidade?";
			link.l1 = "Com certeza. Estou procurando seu antigo capitão, Esberdo Cabanas, e não tenho muito tempo... O ideal seria encontrá-lo naquele lugar que ele mantém em segredo. Melhor ainda se eu chegar lá antes dele.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ha-ha! Eu disse pra esse idiota patético ficar de boca fechada! O âmbar azul, não é?";
			link.l1 = "Você está pensando na direção certa, meu bom senhor.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Então vamos nos apressar. Eu adoraria te contar cada detalhe, se você encontrar um jeito de me tirar daqui. Sabe como eu vim parar nesse buraco?";
			link.l1 = "No geral, sim, eu concordo.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "Eu estava completamente bêbado quando aquilo aconteceu. Maldito seja aquele maldito barman! Não lembro de nada. Só me contaram tudo quando acordei no porão do 'Cantavro'. Tudo teria ficado para trás se a gente simplesmente tivesse ido embora, tanto o comandante quanto o alcalde estavam dispostos a fingir que nada aconteceu. Mas aquele maldito Don Esberdo simplesmente me jogou na cadeia. Você acha que ele fez isso 'para fazer a coisa certa'? Quem dera, aquele canalha só queria ficar com a minha parte do âmbar. Fui eu quem comentou que podia ter mais âmbar debaixo d'água do que o que achamos na praia. Fui eu quem descobriu como pegar. Eu ia receber uma boa fatia, mas... ah, aquele filho da mãe! Bah, chega disso. Nem o alcalde, nem o comandante, nem Don de Toledo estão satisfeitos de me ver apodrecendo aqui. Se não fosse por aquele camponês e a vaca da esposa dele, que fizeram o maior escândalo... de qualquer forma, eles não vão se opor se você me ajudar. Fale com o governador, finja que é meu velho amigo da Europa – eu mesmo confirmo isso. Qual é o seu nome, aliás?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", wonderful. Go see don Diego de Toledo and ask him for advice. Remember, you only have three days; chasing the 'Cantavro' would be pointless after that. Set me free and I will give you everything you need to deal with that bastard, Cabanas.";
			link.l1 = "Vou falar com o governador imediatamente, don Lope. Vou fazer o possível para resolver essa situação para o bem de nós dois.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "Então, o vigarista e sua galinha tagarela conseguiram sua vingança, e eu finalmente estou livre deste buraco. Você tem minha gratidão, señor, fez o que precisava. Agora deixe-me fazer a minha parte.";
			link.l1 = "Pode falar, estou ouvindo!";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Good. During our previous patrol, we were caught in a storm that forced us off course. We landed on the beach of the Western Main, not far from the Mosquito Coast, to replenish our fresh water. There, we discovered a rich deposit of blue amber. I did some prospecting and found a pile of it underwater. We needed better equipment to collect it, which is why we decided to return later.\nEsberdo had bought five longboats in Havana for the Indians to dive and gather the amber. You know the rest of the story – the scoundrel got rid of me and sailed away. Find him at the Mosquito Coast, north of Blueweld, and make haste – by my reckoning, you have about seven days to get there. I hope you catch the bastard in the middle of his gathering, take all his amber, and stab his belly repeatedly. Be careful, though; my former captain is a skilled fighter and seaman. Godspeed, señor.";
			link.l1 = "O mesmo pra você, Lope. Adeus!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Gostaria de perguntar algo, senhor?";
			link.l1 = "Sobre Don Montoro. Somos velhos conhecidos, e fiquei realmente abalado quando soube de suas desventuras. Don Diego de Toledo me enviou até você, dizendo que você já tentou libertar nosso amigo em comum...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Hm... señor, isso é um pouco... inesperado, mas fico feliz em conhecer um amigo do Lope! Ele já anda sem sorte faz um bom tempo, e agora isso...";
			link.l1 = "O que podemos fazer por ele? Não é certo que um nobre hidalgo apodreça entre a escória da sociedade!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "Um homem de negócios! Ajudar o pobre Lope é ao mesmo tempo fácil e difícil. Conversei com o agiota com quem o pobre Lope teve o azar de discutir. Ele topou negociar se pagarmos quinhentos dobrões. Uma bela quantia pelo 'sofrimento' dele e da esposa. Infelizmente, só consegui juntar metade do valor pedido – duzentos e cinquenta dobrões.";
			link.l1 = "Então, se eu trouxer mais duzentos e cinquenta dobrões, o Don Lope vai ser libertado?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Sim. O desgraçado ganancioso me prometeu que espalharia a notícia de que Lope o compensou por todos os prejuízos. Ele também vai pedir ao governador que o perdoe.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Tenho a quantia necessária comigo agora mesmo. Aqui, que esse burguês ganancioso engula isso.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Vou fazer o possível para conseguir o dinheiro o quanto antes.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Não acredito no que estou ouvindo! Senhor, o senhor deve ter sido enviado por Deus!";
			link.l1 = "Quando vão libertar o nosso homem?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Fico feliz em ouvir isso, señor. Você é um verdadeiro amigo do Lope e um verdadeiro cavalheiro.";
			link.l1 = "Adeus!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Trouxe o dinheiro?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Tenho a quantia exigida comigo agora mesmo. Aqui, que esse burguês ganancioso se engasgue com isso.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Ainda estou cuidando disso.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "Vou levar o dinheiro para aquele canalha sorrateiro hoje à noite. Acredito que até o meio-dia eles já terão uma ordem para soltar nosso amigo. E espero que a gente se reúna depois para comemorar, não é?";
			link.l1 = "Pode deixar, don Rosario. Preciso ir agora. Até mais!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Logo nosso amigo estará livre!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Ei, que diabos você está fazendo no meu navio? Não me lembro de ter te convidado, hein?";
			link.l1 = "Calma, Geffrey. Eu sou de Tyrex, vim tratar do negócio da seda do navio.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "A-ah, well, let's talk then. What's he planning? I've already spoken to the smugglers; if you ask me, they offer a fair price for the goods...";
			link.l1 = "E quanto, se me permite perguntar?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1.300 pesos por um rolo. Acho que é um bom preço.";
			link.l1 = "É, e o Tyrex quer 4 moedas de ouro por um rolo. Nem uma moeda a menos. E estou falando de dobrões. Ele me deu a tarefa de encontrar o comprador certo por esse preço.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ha-ha-ha, garoto, você é mesmo sortudo! O Marcus tem um apetite e tanto! Então vai lá, encontre um comprador desses, seria glorioso ver você tentando.";
			link.l1 = "É, tudo isso é mesmo muito engraçado, hilário pra caramba. Eu pareço feliz? Não pareço. Então sugiro que pare de rir e me ajude.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Tá bom, tá bom, camarada... Jesus, você não gosta muito de piadas, né? Mas eu entendo, não é sua culpa as fantasias do Tyrex, todos nós vamos acabar pagando por isso, pode acreditar. E como é que eu posso te ajudar? Não dá pra vender isso em loja, alfândega também não rola, só restam os contrabandistas. Quem mais ia querer isso? Tem alguma ideia?";
			link.l1 = "Tenho pensado nisso desde Hispaniola... Tanto faz. Tenho só dois meses para encontrar um comprador fixo. Preciso resolver isso. Suas ordens são desembarcar na baía mais próxima e fazer os reparos.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Dois meses?! Mas que diabos? Ah, dane-se. A 'Cobra' realmente precisa de reparos e limpeza, senão não vai conseguir nem alcançar uma barcaça. Ei, francesas! A tripulação do Careca Geffrey vai ficar em Capsterville por dois meses! Ha-ha-ha!... Boa sorte aí, camarada, nessas suas buscas inúteis. Se encontrar algum idiota disposto a pagar o preço do Marcus por essa droga de seda – já sabe onde me achar.";
			link.l1 = "Espere! Me dê um rolo dessa seda. Preciso mostrar a mercadoria para possíveis compradores.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Claro, sem problema. Você pode levar isso com você no bote... Ei, rapazes! Joguem um fardo de seda no barco do capitão!";
			link.l1 = "Ótimo. Bem, te vejo quando eu encontrar o comprador!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Mais alguma coisa, camarada?";
			link.l1 = "Nada no momento...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "Como você está, camarada?";
			link.l1 = "Está indo bem. Consegui um comprador para nós. 5 dobrões por rolo. Acho que Tyrex vai gostar.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "Não acredito! Você é mesmo um filho da mãe cheio de recursos! Como conseguiu isso, hein?";
			link.l1 = "É uma longa história, Geffrey. Agora escute. Você deve chegar ao Cabo Negril, na Jamaica, entre os dias 10 e 15. Eles vão estar te esperando lá à noite. A senha é 'Um mercador de Lyon'. Entendeu? Repita.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "A merchant from Lyons. Got it. I should tell my purser to write it down; he's the only man here who can write. Ha-ha!";
			link.l1 = "Você tem cem rolos no porão de carga?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "Eu tenho ainda mais.";
			link.l1 = "Excelente. Então está na hora de zarpar. Não me decepcione!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Relaxa, camarada, tudo vai ser feito como deve ser feito.";
			link.l1 = "Boa sorte, Geoffrey. Talvez a gente se encontre de novo.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ho-ho-ho! Charlie Prince, o astuto, em pessoa! Que bom te ver de novo, camarada!";
			link.l1 = "Geffrey Careca! Charlie Prince, foi isso que você disse? Ha!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = " Nunca ouvi seu sobrenome antes? É assim que te chamam em La Vega agora.";
			link.l1 = "Entendi de onde veio o Charlie, mas por que Príncipe?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Bem, você é o único filho da mãe nobre em La Vega! Ha-ha-ha! Como vai? Já passou na loja do Pasquale? Comprou mantimentos com aquele velho canalha?";
			link.l1 = "Nunca mais!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha! Ora, você não gostou dele? Ele te vendeu carne salgada pelo preço do rum?";
			link.l1 = "Pior ainda! Ele me deu uma pista sobre uma caravana holandesa carregada de ébano. Não foi fácil encontrar, abordar o mercante e depois proteger aquela madeira maldita de umas dezenas de ratos! E adivinha só, o desgraçado me pagou 150 pesos por peça. Por uma peça de ébano, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "Isso acontece o tempo todo, camarada, pode acreditar. Lavoisier já enganou uma dúzia de bons rapazes como você. Na verdade, ele até te pagou alguma coisa, o que é raro vindo dele. A gente não aceita as 'dicas' dele nem passando fome.";
			link.l1 = "Obrigado, meu amigo, pelo menos agora sei que não fui o primeiro e único idiota! Mas dessa vez o desgraçado se ferrou. Vou garantir que ele se arrependa do dia em que me viu.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Ei, ei, ei! Calma aí, Príncipe, se acalma um pouco. O mascate aqui é intocável. Se ousar roubá-lo, o Marcus vai atrás de você. Me diz, foi o Tyrex que te mandou ao Lavoisier?";
			link.l1 = "Hm. Sim... Por quê?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Escute... (abaixando a voz) Dizem que Quatro-Olhos divide com Marcus. Agora entendeu? Por isso nenhum pirata jamais ousa atacar os navios do Lavoisier, senão estão acabados.";
			link.l1 = "Entendido. Obrigado pelo aviso, Geffrey. Adeus e que Deus te acompanhe!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "O mesmo pra você, camarada.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "Ho-ho-ho, Príncipe! Eu estava me perguntando quem tinha feito o espetáculo de fogos! Trouxe um grupo de mosqueteiros caso fossem os espanhóis.";
			link.l1 = "Geffrey? Você também está aqui? Mas como? Você também comprou o mapa do tesouro?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "Amigo, não gasto meu dinheiro com essas porcarias. Me entregaram um diário de um viajante que escreveu sobre uma passagem segura para essas masmorras.";
			link.l1 = "Quem trouxe isso para você?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Um viciado qualquer. Tudo que ele queria era cem pesos pra uma bebida.";
			link.l1 = "Aconteceu em Tortuga?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Não. Foi em Barbados? Príncipe, por que você está tão preocupado? Quanto mais gente tivermos, mais rápido vamos conseguir carregar os tesouros!";
			link.l1 = "Não gosto disso. Não acredito em coincidências assim. Será que foi o pai da Camilla quem escreveu este diário?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Quem é Camilla?";
			link.l1 = "Aquela vadia que me vendeu um mapa deste lugar por duzentos pesos!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Heh... Príncipe, você pensa demais. Vamos caçar tesouros. Vamos lá!";
			link.l1 = "Não precisa. Eu já os encontrei... Eles estão lá embaixo, no calabouço, atrás das grades de ferro. Vamos ter que tirá-los de lá. Escuta, Geffrey, tem mais uma coisa! Pelly Cutelo também esteve aqui!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Cutelo? Então hoje é nosso dia de sorte! Mas onde ele está agora?";
			link.l1 = "Lá embaixo... morto. Eu o encontrei perto do tesouro. Ele enlouqueceu, começou a gritar de ganância. Então ele e os companheiros dele me atacaram.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly sempre teve azar com dinheiro. Deve ter enlouquecido ao ver aquela pilha de ouro.";
			link.l1 = "Pode ser... mas Geffrey, você não entende! Nós três chegamos aqui! E todos nós seguimos a mesma pista! Você acha que foi por acaso? Alguém claramente quer todos nós no mesmo lugar, e este lugar realmente parece um túmulo.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Mas você viu o ouro mesmo?";
			link.l1 = "Eu vi com meus próprios olhos. Vários baús enormes cheios de moedas e lingotes.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "Então por que se preocupa, Príncipe? Mostre o caminho, vamos dar uma olhada nessas barras suas. Depois dividimos o ouro.";
			link.l1 = "Ah, talvez você tenha razão, tanto faz... Vamos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            //PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "Que espetáculo! Isso é uma montanha de ouro! Agora entendo por que o Cutlass enlouqueceu. Somos muito sortudos, príncipe! O que acha, quanto ouro será que vamos encontrar aqui?";
			link.l1 = "Muito. Saberemos com certeza quando lidarmos com essas grades.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Sim, a grade é muito resistente, não vamos conseguir quebrá-la só com as mãos ou com espadas. Você tem razão, precisamos encontrar algumas ferramentas ou bastante pólvora. Ei, olha! O que é aquilo!?";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"Que droga, que confusão!";
			link.l1 = "Seu maldito traidor!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "Que eu seja engolido por um tubarão se isso já aconteceu no 'Peixe Voador' este ano... rapazes, temos uma visita aqui! O que foi tão ruim na sua vida, camarada, pra você decidir aparecer no meu velho barco?";
			link.l1 = "Saudações! Você é quem chamam de Husky Billy, não é?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Não consegue adivinhar pela minha voz, capitão? Antigamente, ela fazia mercadores britânicos e espanhóis se cagarem de medo. Foram tempos gloriosos!... Agora o velho Billy só espera a vida acabar, perto das margens da sua ilha favorita, no seu querido bote...";
			link.l1 = "Tenho uma proposta de negócio para você, Billy. Disseram-me que você sabe tudo o que acontece aqui por perto da Jamaica. É verdade?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "Se te disseram isso, então deve ser verdade, não acha? Não fique enrolando, fale logo. O que você quer comigo?";
			link.l1 = "Muito bem. Há um construtor naval em Port Royal. Ele oferece serviços especiais aos clientes e precisa de seda naval para sua produção e esses serviços. Como negociar essa mercadoria é ilegal aqui, ele arranjou um fornecedor clandestino. Quero saber quem está fornecendo a seda naval para ele, e como.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Ho-ho-ho, olha só isso! Trabalhando para o Coronel D'Oyley, garoto?";
			link.l1 = "Lá vamos nós de novo! Não, eu trabalho com Marcus Tyrex. Ele quer uma fatia do mercado de seda dos navios e esse construtor naval está morrendo de medo de lidar com gente 'desconhecida'...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Oh, so you're working for the Code Keeper! That's great news... if you're not lying, of course. I don't give a damn about shipbuilders; arrest one and another will take his place. But I do give a damn about my old girl. The 'Flying Fish' is in a bad way. Do you understand me?\nBring me another longboat, a new one, and a roll of ship silk—the same kind you're talking about. Billy will make a proper sail out of it, so he can outfox the patrols, ha-ha-ha! In return, Billy will tell you everything about the shipbuilder and his source of silk. Trust me, son, I know everything you want to know. I just need to make sure you're an honest pirate and not some arse-licking redcoat!";
			link.l1 = "Um novo bote? Que tal se eu te der dinheiro suficiente pra você mesmo comprar um? Ainda te dou um extra.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "Heh, capitão, o velho Billy não é bem-vindo na cidade. Eles ainda se lembram muito bem de mim em Port Royal e não gosto nem um pouco da ideia de ser enforcado entre meus velhos conhecidos naquela pedra. Então, rapaz, estou esperando que você me traga um escaler novinho em folha. Vou te esperar por três dias no Cabo Negril. E não se esqueça da seda!";
			link.l1 = "Muito bem, Billy. Você vai ter seu bote e um rolo de lona de vela. Eu volto já.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = " Muito bem, Billy vai estar esperando por você na praia, capitão. Até logo!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "O quê? Já trouxe um bote para mim?";
			link.l1 = "Você é um brincalhão, hein, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "Então, capitão, e o meu barco novo?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "Está feito, Husky. Ela foi entregue junto com um rolo de seda naval no porão. Você está livre para afundar sua velha sucata.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = " Ainda estou cuidando disso. Espere. ";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Caramba! Essa é a melhor notícia que o velho Billy recebeu em cinco anos! Heh, um ótimo motivo pra abrir essa garrafa...";
			link.l1 = "Vou deixar passar. Então, sobre o fornecedor de seda?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Que pena, poderíamos ter brindado ao meu novíssimo 'Flying Fish'! Deixa pra lá... Escuta aqui, rapaz\nUm brigantine sob bandeira inglesa chega a Portland Cove todo mês, sempre entre os dias 10 e 15. Não bebo mais rum até morrer se aquele navio for mesmo inglês! O nome dele é 'Utrecht' e ele vem do sudoeste, lá de onde fica Curaçao. Dá pra ver claramente que é um capitão holandês\nSempre o mesmo grupo de pessoas vai ao encontro deles na praia, liderados pelo mestre daquele astuto construtor de navios. Ele é quem recebe a seda de navio que os holandeses descarregam ali. Tenho certeza de que é seda de navio, porque só os holandeses embalam desse jeito.";
			link.l1 = "Todo mês, você disse?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "De fato, meu rapaz, não perdi um único mês no ano passado. Se quiser conversar com aquele grupo soturno e barbudo, sugiro que espere por eles em Portland Cove, do dia 10 ao 15 de cada mês, à noite. Juro pelo velame novo de seda do meu bote!";
			link.l1 = "Hein! Parece que meu dinheiro foi bem gasto. Boa sorte, Billy, trate de manter esse seu traseiro velho longe das patrulhas, senão você vai me deixar realmente irritado.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ha, o velho Billy está prestes a aprontar das suas pelas praias da Jamaica! Boa sorte, capitão! Que tenha uma boa caçada!";
			link.l1 = "Pra você também, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Ei, marinheiro, acabou de chegar à Jamaica, né?";
			link.l1 = "Hm. Isso mesmo. O que houve?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Viu alguma coisa acontecer no mar por aqui?";
			link.l1 = "Sim, vi sim. Um brigantim estava em combate com uma corveta de patrulha inglesa. Os britânicos atacaram forte, e os holandeses jogaram a carga ao mar tentando escapar.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Por que você tem tanta certeza de que ela era holandesa? Nenhum holandês em sã consciência pensaria em chegar tão perto de Port Royal...";
			link.l1 = "Ela hasteava a bandeira inglesa, mas o nome... 'Utrecht'. Não soa muito britânico, né? Eles eram holandeses, te digo, talvez até contrabandistas. A patrulha certamente os esperava.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Porra!";
			link.l1 = "Parece que você não está exatamente feliz com isso...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Você estava esperando por este brigantino aqui?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Por que eu estaria?";
			link.l1 = "Vamos lá. Eu sei quem você é. Você é o capataz do estaleiro de Port Royal, e está esperando uma carga muito especial que será entregue pela escuna.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "Está estampado na sua cara, bem aí!";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh! Rapazes, isso é uma patrulha disfarçada! Acabem com eles e sumam daqui!";
			link.l1 = "Merda! Espera, você está en...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Está sendo grosso, 'lobo do mar'? Cuidado com o que fala ou...";
			link.l1 = "Vamos lá. Dá pra ver que você está chateado. Você realmente estava esperando esses holandeses chegarem?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "Ou o quê? Vai me dar uma lição sobre a vida?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "E se eu fosse? Por que isso te importa?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "Na verdade, não. Quem está esperando aqui é você, não eu. Você tem a eternidade pela frente.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Ah, eu tenho todo motivo pra me importar. Eu sei o que tinha no porão do brigantino. Seda da Companhia. Você está aqui por causa disso, não é?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Hm... Eternidade?";
			link.l1 = "Leva uma eternidade pra voltar do fundo do mar. Sua brigantina foi afundada por uma corveta de patrulha, camarada. Assim mesmo. Ainda assim, a guerra traz tanto prêmios quanto perdas. Vou ganhar um bom dinheiro com aquele holandês afundado.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "E como exatamente, hein?";
			link.l1 = "Vou vender o que eles jogaram ao mar enquanto tentavam fugir. Quase tudo se perdeu, mas a seda preciosa do navio ficou boiando como... cortiça. Consegui resgatar a maior parte, então amanhã vou à cidade procurar um comprador. Nunca se sabe onde se ganha e onde se perde.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Espere!";
			link.l1 = "Caramba! E agora?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "Quanto de seda você conseguiu juntar?";
			link.l1 = "E por que você se importa? Essa seda é minha! Ou você é o cão do governador? Você é um...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Guarde sua espada, marinheiro. Não sou cachorro e muito menos dedo-duro. Trabalhamos no estaleiro local... Essa seda era para a gente e, pelo que entendi, agora está com você. Eu compro tudo de você, precisamos dessa seda, camarada.";
			link.l1 = "Sério? Interessante... Quanto?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Dois mil e quinhentos por um rolo. É um bom preço, não vai encontrar melhor.";
			link.l1 = "Parece que dei sorte! Eu tenho "+FindRussianQtyString(i)+". Mostre-me o dinheiro e eu mando entregar na praia agora mesmo.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Fechado!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... O Joachim devia entregar só oitenta rolos – não tem como você ter conseguido tanto assim... isso significa que ou você está tentando me passar a perna, ou... é um dedo-duro! Rapazes, matem ele e sumam daqui!";
			link.l1 = "Porra!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "Um ótimo negócio, camarada! Por que essa cara fechada? Preocupado com os holandeses no fundo do mar? Essas coisas acontecem, não esquenta!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "É, claro... Eles eram nosso fornecedor habitual. E agora, onde vamos conseguir seda? Sempre falta e todo o comércio está sob o controle direto do Coronel D'Oyley. Bah, droga...";
			link.l1 = "Hm... Escuta, amigo, acho que posso te ajudar com isso.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Ah, é mesmo? E como você acha que pode nos ajudar? Vai entregar um lote de cem rolos todo mês?";
			link.l1 = "Eu? Hmm, provavelmente não, mas Marcus Tyrex saberia. Já ouviu falar dele?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "K-ha! Então, você é um pirata?";
			link.l1 = "Não, eu só faço negócios com eles em ocasiões especiais. Sei com certeza que o Marcus recebe lotes de seda de navio regularmente e vende para quem puder pagar. E não estou falando de 2.500 pesos por rolo aqui. Diria que, se você puder pagar 5 dobrões de ouro por cada rolo, ele vai te afogar em seda, pode apostar nisso.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "Isso é uma notícia interessante... Marcus Tyrex, você disse? Só em dobrões?..";
			link.l1 = "Vamos lá, amigo, faz mesmo diferença pra você de quem compra a seda? E dinheiro é dinheiro, dá pra trocar pesos por dobrões no banco. Então, quer que eu fale umas palavrinhas sobre você pro guardião do código? De qualquer jeito, vou pra La Vega.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Muito bem. Vamos fazer um acordo. Estes são os nossos termos: um lote de cem rolos todo mês, entre os dias 10 e 15. Estaremos esperando aqui... espere, vamos mudar o ponto de encontro, este lugar está comprometido agora. Estaremos esperando no Cabo Negril, perto de Maroon Town, deve ser mais seguro lá. A senha - 'Um mercador de Lyon'.";
			link.l1 = "Fechado, amigo. Que viagem foi essa, hein! O Tyrex vai me pagar um ou dois dobrões por um comprador desses! Ha-ha! Muito bem, vou indo. Espere pelo navio do Tyrex no mês que vem. Boa sorte pra você e sua família!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "Depois que a gente te ensinar um pouco de respeito, você não vai precisar de lição de vida nenhuma.";
			link.l1 = "Tá se achando, carpinteiro? Tudo bem, pode continuar esperando por esse seu brigantim, mas vai demorar.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Ei, professor, eu também tenho umas lições pra você!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Carpinteiro? Puta merda, como você sabe disso? K-ha! Droga, rapazes, isso é uma patrulha disfarçada! Matem ele e caiam fora daqui!";
			link.l1 = "Merda!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Deixa a gente em paz, seu escama de peixe, não temos tempo pra você. Cai fora!";
			link.l1 = "Está esperando ocupado por algum navio holandês? Boa sorte com isso. Você tem a eternidade pela frente.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "Do que diabos você está falando?";
			link.l1 = "Entendi. Mas, caso você esteja, esqueça. Ela não vem, graças a uma corveta de patrulha. Vi pelo telescópio o fim da luta. Aconteceu tão rápido e não muito longe daqui";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "De novo, não estamos esperando por nada nem por ninguém, e...";
			link.l1 = "Olha, pra falar a verdade, não tô nem aí. Não faço parte da patrulha da cidade e não me importo com o que você faz, também não sou nenhum santo. Se você tá contrabandeando, isso é problema seu. Só queria te dar um aviso. Boa sorte pra você, camarada.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Espere... Tem certeza de que o 'Utrecht' afundou?";
			link.l1 = "Com certeza. Ela tentou fugir, jogou fora tudo que tinha nos porões, nem sequer poupou a seda preciosa do navio, mas nem medidas tão drásticas ajudaram contra a vantagem de velocidade de uma corveta.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "Que pena... e o que vamos fazer sem a seda? Droga!";
			link.l1 = "Você está precisando de seda para navio?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Por que está perguntando, está querendo vender?";
			link.l1 = "Eu não sou, mas conheço um homem que é. Ele está procurando por um comprador generoso e frequente. Acha que pode se encaixar?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "E quem é aquele homem?";
			link.l1 = "Marcus Tyrex, o barão de La Vega, mais conhecido como o Guardião do Código. Ele recebe carregamentos de seda naval regularmente, então sempre tem um pouco para vender. Acho que ele também consideraria vender para você, se o seu preço for bom o bastante.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "Então, você é um pirata?";
			link.l1 = "Por que você se importa? Posso arranjar um acordo entre você e Tyrex, se tiver coragem pra isso. Se não – então adeus.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Tá bom, tá bom, não precisa ficar bravo. Claro que quero. Quero fazer um acordo com o Tyrex. Mas o que você ganha com isso?";
			link.l1 = "Se você oferecer um bom preço pela carga, provavelmente vou conseguir uma quantia decente do Marcus pela minha ajuda. Então, o que vai ser?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "5 doblões por uma jogada. Esse é o melhor preço que você vai encontrar, pode confiar.";
			link.l1 = "5 moedas de ouro? Hm. Nada mal. Acho que o Tyrex vai me dever muito por trazer um comprador assim. Muito bem, está feito, vou avisá-lo. Mas se você mentiu pra mim sobre o preço, é o seu pescoço que está em jogo.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Não se preocupe, somos gente honesta. Nossos termos são estes: um lote de cem pães todo mês, entre os dias 10 e 15. Estaremos esperando aqui... espere, melhor mudar o ponto de encontro, este lugar já não é seguro. Vamos esperar no Cabo Negril, perto de Maroon Town, lá deve ser mais seguro. A senha é: 'Um mercador de Lyon'.";
			link.l1 = "Entendido. Espere o primeiro lote no mês que vem.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Avise ao Tyrex que ele pode trazer mais carga desta vez, pois ficamos sem seda para este mês.";
			link.l1 = "Eu vou. Que Deus te acompanhe, amigo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "O que te traz a bordo do meu navio, amigo?";
			link.l1 = "Ei, Cutlass. Marcus Tyrex me enviou. Uma marcha até Maracaibo nos espera.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, finalmente. Então você deve ser meu novo chefe para esta viagem. Ótimo. Qual é o nome do meu novo almirante?";
			link.l1 = "Capitão "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Ordens, Almirante "+GetFullName(pchar)+"?";
			link.l1 = "Navegaremos até o Lago Maracaibo separadamente. Você deve chegar à noite e desembarcar discretamente na Baía de Guajira. Espere por mim lá e, enquanto isso, monte um pequeno acampamento. Quanto a mim, vou desembarcar no porto espanhol.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Sim senhor, Almirante!";
			link.l1 = "Quanto tempo você vai levar para chegar lá?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Hmmm... Deve levar cerca de uma semana. Um dia a menos, um dia a mais, tudo depende do vento.";
			link.l1 = "Ótimo. Então não vamos perder tempo. Te vejo na Baía de Guajira, amigo.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Sim, senhor, Almirante!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Ordens, Almirante?";
			link.l1 = "Nada no momento. Estou ocupado com a nossa operação.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Prepare um grande baú na praia. Vamos juntar armas nele para nossos irmãos presos.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "Então, qual é a do Bonitão? Estou doido pra derramar o sangue desse Don!";
				link.l1 = "É mais complicado do que pensávamos. Ele disse que os guardas da plantação estão muito atentos. A única maneira de entrar com armas é escondê-las entre as mercadorias. Vamos precisar urgentemente conseguir uma carga de café, copra ou baunilha – o fazendeiro local só negocia com isso e nada mais.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Leave the camp and assemble a storm squad. It's time to march; we attack under the cover of darkness.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "Escute, Almirante, estive pensando...";
			link.l1 = "O que é isso, Terrax te paga pra pensar em vez de balançar esse seu sabre, hein, Cutlass?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "Ho! Uma rebelião na plantação, não é mesmo, Almirante? Chamas! Vamos tirar algum ouro disso!..";
			link.l1 = "Preciso de um baú na praia, Cutlass.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "Já vou, Almirante!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "Imediatamente, Almirante!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Os homens estão prontos e preparados, Almirante!";
			link.l1 = "Avante!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Almirante, parece que o amigo do Tyrex que deveríamos salvar está... meio morto.";
			link.l1 = "Yes, but nothing could be done there. You saw the guards; we were lucky to stay alive.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Almirante, Marcus vai ficar furioso com você. Não vá falar com ele agora. Eu estou indo embora. Você também deveria.";
			link.l1 = "É...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Más notícias, Almirante. Um esquadrão espanhol está vindo do leste em nossa direção. Não temos tempo para fugir.";
			link.l1 = "Quantos deles?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Três navios. Muitos canhões. Estamos ferrados."; // лесникПОСЛЕДНЕЕ
			link.l1 = "Vamos ver.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Jean, você vai para o navio do Cutlass.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Cutlass, você devia hastear a bandeira espanhola e dar o fora daqui. Eu vou distraí-los por você. Vejo todos vocês em La Vega.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "Mas...";
			link.l1 = "Sem desculpas! Cutlass, é o seu pescoço em jogo se o Picard não chegar ao lugar do Tyrex. Todos a bordo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Ordens, Almirante?";
			link.l1 = "Prepare-se para lutar. Ataque quando eu ordenar!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Sim, senhor, Almirante... às suas ordens!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Ho-ho! Olá, Príncipe. O que te traz a Tortuga?";
			link.l1 = "A tarefa do Marcus de novo. Escuta, Cutlass, por que o desgraçado que mora nessa casa não me deixa entrar?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Dentes de Ouro? Ele só trabalha com gente de confiança. Outros precisam de uma indicação para fazer negócio com ele. Quer vender umas bugigangas brilhantes? Posso te recomendar, se quiser...";
			link.l1 = "Então ele é um agiota? Qual é o interesse dele?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Irmão, você está enganado. Gaspard não é agiota, você deveria ir para "+GetFullName(characterFromId("Tortuga_usurer"))+" se precisar. O Dentes de Ouro compra pedras preciosas e joias de todo tipo. Aliás, ele paga bem e nunca faz perguntas tolas. Todo capitão pirata é cliente dele.";
			link.l1 = "Entendo... Disseram-me que alguns até confiam o dinheiro a ele...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha! Quem te disse isso é um mentiroso, vá cuspir nos olhos sem vergonha dele. Gaspard só mexe com joias, sempre foi assim. Por que ele iria querer confusão com o dinheiro dos outros?";
			link.l1 = "Entendi. Obrigado, Cutlass, até nos encontrarmos no mar!";
			link.l1.go = "Pelly_27";
			link.l2 = "Hmm, de fato. Então, ele compra bugigangas? Interessante... Você disse que pode me recomendar?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "Até mais, Príncipe.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "Claro! Agora você faz parte do nosso grupo, hehe! Espere aqui um instante.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "Está tudo resolvido! Agora o Dente de Ouro já sabe que Charlie Prince pode procurá-lo para vender bugigangas. Só lembre que o preço dele, embora bom, ainda é menor do que pagam aqueles agiotas miseráveis. Mas ele compra tudo em grandes quantidades! E sem perguntas desnecessárias, como eu já disse.";
			link.l1 = "Esse é o meu rapaz bonito! Muito bem, Paul! Agora tenho onde descarregar todo o saque!";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "Não, Jean Picard é o 'Belo', eu sou o 'Cutelo', haha! Adeus, Príncipe!";
			link.l1 = "Obrigado, Cutlass, boa sorte no mar!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "Tenho três passarinhas pra você, Príncipe. Encontrei-as escondidas em guarda-roupas e debaixo de uma cama. Bonitas, não acha? Ha-ha-ha!";
			link.l1 = "Eu diria que são mesmo. E ainda estão bem cuidados. Dom Teimoso deve se importar muito com eles.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "Salve! Que diabos você está fazendo aqui, Príncipe?";
			link.l1 = "Cutlass?.. Eu estava seguindo as vozes e o barulho, mas nunca imaginei que fosse você. Como diabos você veio parar aqui?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "Não, por que você está aqui! Você está sempre por perto! O Tyrex deve ter te mandado atrás desse tesouro, não é? Caramba, cheguei atrasado de novo...";
			link.l1 = "Tyrex? Não... Comprei um mapa de uma vadia qualquer. Aposto que ela te vendeu uma cópia também, né? Lá em Tortuga? Que mulher esperta. Mas não mentiu – olha só esse monte de ouro! Vou voltar com mais gente pra carregar tudo iss...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Claro que sim, é uma pilha de ouro! Mas não é sua nem do Tyrex! Fui eu que encontrei primeiro! É meu! Não importa como fiquei sabendo disso! Não é da sua conta!";
			link.l1 = "Calma, Cutlass, por que você está tão bravo? Olha só esse monte — deve ter um milhão aqui. Talvez até mais! Dá pra nós dois!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "Você sempre fica com a melhor parte, Príncipe! Mas desta vez não! O tesouro é meu! Fui eu quem encontrou primeiro!";
			link.l1 = "Porra, Paul, o que deu em você? Não dá pra gente chegar a um acordo aqui? Mesmo metade desse ouro já é uma fortuna. Você nunca teve tanto dinheiro assim nas mãos antes. Além disso, um dia eu posso encontrar uma oportunidade boa e te contar.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Quer me ferrar, Príncipe? Nem pensar! Não vou te dar uma moeda, nem um tostão! Chegou tarde demais!\nAh, já saquei o seu jogo! Você não vai pôr as mãos nesse ouro, nunca!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "Hilário. De verdade. Você é um comediante, Almirante. Mas é verdade – Marcus não gosta de quem tenta ser mais esperto do que ele, como você. Mas ele valoriza homens inteligentes.";
			link.l1 = "Certo, certo. Então, o que você tem em mente?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "Algo que você e o Handsome claramente não pensaram. Vocês estão planejando uma revolta na plantação. Ótima ideia — se o objetivo fosse saquear ou causar confusão. Mas...";
			link.l1 = "Mas o quê? Você é contra a revolta? Tá com medo?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "Eu? Ha! Nunca. Mas pensa no que acontece se o Bonito morrer durante a carnificina. O que vamos dizer pro Marcus? Vou te contar uma coisa – não importa o que a gente diga. Ele vai arrancar nosso couro do mesmo jeito.";
			link.l1 = "Hmm. Então qual é o seu plano genial? Precisamos dar um jeito de tirar ele de lá.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "Sim, nós temos. Por isso mesmo... por que não comprá-lo? De forma... oficial, quero dizer. Um punhado de ouro compra qualquer um desses canalhas – até as próprias mães deles. O que dizer então do pobre Jean?";
			link.l1 = "Ha! Cutlass, você está mesmo sugerindo que eu entre numa plantação e peça para comprar o Picard? Quer que eu diga também para quem trabalho, só por diversão? Você ficou maluco?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "Não precisa dizer isso. Na verdade, é o contrário – finja que é um comerciante. É claro que você não tem o jeito para o papel, mas também não parece um pirata. Sem ofensa, Almirante, mas é a verdade. Apenas entre nessa plantação, aja com confiança e peça para falar com Jean. O dono pode até desconfiar de quem você é, mas não vai demonstrar. Como eu disse – um punhado de ouro cala qualquer boca.";
			link.l1 = "E quanto custaria essa... mão de ouro para nós? A montanha inteira?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "Pode ser. Mas é melhor perder o ouro do que a cabeça. Não fiquei parado enquanto você estava em terra – troquei de roupa para algo menos de pirata e fui perguntar sobre a plantação e seu humilde dono.";
			link.l1 = "E o que você encontrou, Cutlass?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "Preços de mercado, por assim dizer. Não é a primeira vez que um prisioneiro valioso cai nas mãos dele. Normalmente, eles acabam na forca ou pior ainda – nas masmorras da Inquisição.";
			link.l1 = "E por quanto ele vende isso?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "Para alguém importante? Quinhentas moedas. Em dobrões, é claro.";
			link.l1 = "QUINHENTOS?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "Plantadores, o que vocês esperavam?";
			link.l1 = "Por esse preço, eu poderia equipar um pequeno exército! Por que diabos estou acumulando um arsenal no meu navio para uma revolta então? Isso já é suficiente para uma pequena guerra.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "As armas vão ser úteis para sua tripulação mais tarde, de qualquer jeito. Então, o que me diz?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(Confiável) Só vou dizer que seria engraçado se a recompensa do Terrax fosse menor do que o que gastamos aqui. Mas você tem razão – nossas vidas valem mais. Eu tenho os dobrões.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "Eu não tenho esse monte de ouro agora.";
				link.l2.go = "Pelly_44_1";
				Notification_Perk(true, "Trustworthy");
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "Sabe de uma coisa, Cutlass? Esquece. Somos piratas ou não? E o Jean? Ou será que o rostinho bonito dele é tudo o que ele tem? Prepara um baú – vamos seguir com o plano original.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "Eu ficaria surpreso se você conseguisse – é uma quantia enorme. Tudo bem, quando estiver pronto, ou se pensar em algo melhor, venha me procurar.";
			link.l1 = "Pode deixar. Espere aqui.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "Então, Almirante, já conseguiu juntar ouro suficiente para salvar o Picard?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Sim, finalmente consegui. Vamos torcer para que isso funcione.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "Ainda estou trabalhando nisso, Cutlass.";
			link.l2.go = "exit";
			link.l3 = "Não vou dar o meu dinheiro suado para esses fazendeiros gananciosos! Prepare o baú – vamos agir como verdadeiros cavalheiros de fortuna. Essa é a minha decisão.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "Opa. Você acabou de entrar na nossa tripulação e já está esbanjando esse tipo de dinheiro!";
			link.l1 = "Dinheiro não é tudo. Mas se banhar na glória de Terrax? Isso não tem preço.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "Não posso discordar disso. Mas como você disse, não se trata só de dinheiro – tem outra coisa importante nisso, Almirante.";
			link.l1 = "Agora fiquei curioso. O quê?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "Eu já te disse que pesquisei tudo sobre a plantação. Inclusive quais mercadorias estão em alta por aqui e circulando no mercado. Se quiser se passar por um comerciante de verdade, é melhor trazer essas mercadorias em vez de simplesmente jogar um monte de ouro na mesa do fazendeiro.";
			link.l1 = "Faz sentido. Que tipo de mercadoria estamos falando?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "Bem, além de mercadorias vivas, heh-heh, o dono da plantação local compra, troca e revende café, copra e baunilha. Então...";
			link.l1 = "Preciso encontrar um lugar para reabastecer isso rápido. Ou atacar uma caravana e torcer para que ela tenha o que preciso.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "Não é qualquer caravana. Odeio me desfazer dela, mas reservei uma pista só pra mim. Uma caravana trazendo exatamente o que você precisa vai chegar em breve. Mas tem um porém...";
			link.l1 = "Ah, o que foi agora?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "Está sob a bandeira francesa.";
			link.l1 = "O quê?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "Eu entendo a sua frustração, ha-ha. A decisão é sua... Almirante. Quer saber os detalhes?";
			link.l1 = "Droga... Tá bom, fala logo. Não temos muito tempo – se nem eu nem você pegarmos eles, alguém mais vai.";
			link.l1.go = "Pelly_52";
			// link.l2 = "Eu não me meto com franceses a menos que não tenha outra opção. Fim de papo.";
			// link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "Então é melhor você começar a juntar todas essas mercadorias sozinho, e rápido, antes que o Bonitão seja vendido para outra pessoa. Eu também não posso ficar aqui esperando para sempre.";
			link.l1 = "Já imaginava.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_52":
            dialog.text = "Assim é que se fala! Eu sabia que você tinha isso em você... Almirante. Então, é o seguinte: meu contato de confiança me informou recentemente que, em cerca de duas semanas, um comboio francês carregado de café e especiarias vai aparecer nas águas perto de Guadalupe. É grande e bem armado, então se prepare direito.";
			link.l1 = "Que outra escolha eu tenho?";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "Você está cabisbaixo, Almirante. Cadê o Bonitão? Foi tudo por água abaixo?";
			link.l1 = "De fato. Ganhei um bom dinheiro, mas aquele teimoso se recusou a me vender o Picard – nem por uma pilha de dobrões!";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "Que idiota! E agora?";
			link.l1 = "Já acertei com o fazendeiro para descarregar a mercadoria. Vamos ter que voltar ao plano original – é agora ou nunca!";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "Mas nós nem preparamos nada para o Handsome e os outros!";
			link.l1 = "Sem tempo! Embarquem nos navios – vamos contrabandear armas e remédios dos nossos porões para os sacos de mercadorias. E não se esqueçam de hastear a bandeira espanhola!";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "Parece um bom plano.";
			link.l1 = "De qualquer forma, não temos tempo pra mais nada. Anda! A descarga vai acontecer em breve.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "Olha só quem apareceu! Bonitão! E pelo seu rosto inteiro e esse jeito confiante de andar, imagino que deu tudo certo, não foi?";
			link.l1 = "Suave é pouco — não só evitei uma briga e comprei o Jean de volta, como ainda ganhei um dinheiro. Seu plano funcionou perfeitamente, Paul. Tudo tranquilo no horizonte?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "Silencioso como sempre. Vai voltar para o Marcus?";
			link.l1 = "Certo.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_PlantSuccessfulRedemption");
		break;
		
		case "Pelly_62":
            dialog.text = "Hum, como quiser, Almirante. Mas se acontecer alguma coisa com o Bonito, vou garantir que o Terrax saiba que você ignorou meu conselho. Está tudo pronto para a fuga?";
			link.l1 = "Deixe-me conferir e contar o que tenho no baú.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "Pode ter certeza. Posso ajudar por uma pequena taxa para compensar meu esforço, heh-heh.";
			link.l1 = "Que tal assim?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "Tenho um contato, um traficante de armas em Maracaibo. Vou me disfarçar, entrar escondido, pagar a ele e combinar para que as armas sejam contrabandeadas até aqui. Mas vai te custar – dobrões de ouro, para ser exato.";
			link.l1 = "E por que você não me apresentou esse homem antes? Quanto isso vai me custar?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "Quer que eu te apresente a todos os meus informantes também? Tudo bem. Com despesas, riscos e a minha parte... vai sair quase o mesmo que o resgate do Handsome.";
			link.l1 = "Cutelo, tema a Deus...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "Não temo nem a Deus nem a você, Almirante. Mas a fúria do Marcus se não salvarmos o Jean? Aí já é outra conversa. E então, o que vai ser? Precisa de ajuda com o baú?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Certo, vai em frente – já perdemos tempo demais. Aqui, isso deve ser o valor certo.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Isso é muito dinheiro, Paul. Preciso pensar a respeito.";
			link.l2.go = "Pelly_67";
			link.l3 = "Isso está caro demais por um pequeno lote de armas que eu poderia comprar por atacado por muito menos! Não, obrigado, eu mesmo vou resolver isso.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "Pode pensar o quanto quiser. Mas lembre-se — enquanto você pensa, o número de hematomas no rosto e no corpo do Handsome só aumenta a cada hora, heh-heh-heh.";
			link.l1 = "Eu vou conseguir os dobrões pra você...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "Não é sobre o tamanho da carga—é sobre o momento e os riscos. Mas faça como quiser.";
			link.l1 = "Confia em mim, eu sei. Só deixa o baú pronto – daqui pra frente eu cuido.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "Pronto, Almirante? Precisa de ajuda com as armas, ou ainda está sem ouro?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Finalmente consegui o suficiente! Pegue isso e resolva logo – isso já está me irritando.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Fale direito, Cutlass. Estou pronto, mas preciso de mais tempo para conseguir o dinheiro.";
			link.l2.go = "Pelly_67";
			link.l3 = "Isso está caro demais por um lote pequeno de armas que eu poderia comprar por muito menos no atacado! Não, obrigado, vou resolver isso sozinho.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "Ah, que montanha de dobrões é essa! Mas não se preocupe – cada moeda vai para o plano. Caso contrário, o Marcus ia me desenterrar do túmulo depois, heh-heh. Agora, vá até o Handsome, Almirante, e diga que está tudo pronto.";
			link.l1 = "Sou eu quem dá as ordens aqui. Agora, anda logo.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "Sim, isso é um problema. Qual é o seu plano, Almirante?";
			link.l1 = "Preciso encontrar esses suprimentos rápido em algum lugar. Ou atacar uma caravana e torcer para que ela esteja carregando o que eu preciso.";
			link.l1.go = "Pelly_49";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "O que você quer de mim?";
			link.l1 = "Meu amigo, estou procurando por Jean Picard. Por acaso esse é o seu nome?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "Existe uma chance. No entanto, não me lembro do seu rosto.";
			link.l1 = "Não seja tão bruto, Jean. Fui enviado aqui pelo Marcus Tyrex. Minhas ordens são tirar você daqui.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Tsh-sh... Silêncio. Me desculpe, amigo, eu não sabia disso. Mas não devemos conversar aqui, esses malditos guardas estão por toda parte e sempre ouvindo... Vejo que você é bem-vindo entre os espanhóis, me encontre em uma das cabanas à noite e conversaremos. Estarei te esperando, irmão.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Bem, aqui é seguro... Qual é o seu nome, irmão?";
			link.l1 = "Capitão "+GetFullName(pchar)+". Agora me diga, como você foi parar nessa encrenca. Tyrex quer saber de tudo.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "Fui abordado por um desconhecido numa taverna em Willemstad... Ele me convidou para ser seu parceiro no saque de uma caravana holandesa. Eu tinha uma brigantina, ele tinha uma polaca, e era uma bem diferente, por sinal. Caçamos a caravana perto de Caracas e a saqueamos... Era noite, estávamos dividindo o butim quando um enorme galeão espanhol surgiu na escuridão\nMeu parceiro fugiu, e eu também. Mas não havia como minha brigantina avariada escapar de um galeão e mais dois navios. Eles nos abordaram e venderam todos os sobreviventes para este lugar como se fôssemos gado.";
			link.l1 = "Entendi. Você acha que foi um acidente? Estou falando do galeão.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "Sei lá. Talvez tenham ouvido um tiroteio, não foi longe da rua principal.";
			link.l1 = "Hum. É possível. Você já encontrou seu antigo companheiro antes? Quem é ele?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Never met him before. Said his name was Ignacio Marco, a privateer in service of England. He struck me as a serious man, that's why I agreed to take part in this endeavour. He's a seasoned sailor and a captain, that's for certain; he's got a dashing crew behind him, and his polacre is a beauty. You don't see a ship like that every day.";
			link.l1 = "Ignacio Marco? Um corsário inglês? Ele é espanhol?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "Ele é português, não espanhol. Qual o problema com uma carta de corso britânica? Temos muitos espanhóis entre nós, você sabe disso.";
			link.l1 = "Entendi. Tudo bem, vamos falar sobre como você vai sair daqui. Alguma ideia?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "Quais são os seus números?";
			link.l1 = "Meu navio, uma barquentina, e os homens de Pelly Cutlass. Minha embarcação está ancorada no porto de Maracaibo. Cutlass desembarcou na Baía de Guajira e montou acampamento por lá.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hmm...";
			link.l1 = "O quê, você achou que o Tyrex ia mandar um navio de linha pra cá?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "Eu não esperava nada. Na verdade, estou surpreso que o Marcus não tenha se esquecido de mim.";
			link.l1 = "Ele não fez isso, obviamente. Então, alguma ideia?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "No chance of escaping from here – this plantation is too well guarded, and there are wild jungles all around. No point in storming it either; you don't have enough men, plus there's a fort nearby.";
			link.l1 = "Talvez você e seus homens possam nos ajudar por dentro? Ataquem eles com força pelas costas.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "Com o quê? Mãos nuas e facões enferrujados?";
			link.l1 = "E se você tivesse armas?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "Bem, nesse caso, a gente teria dado o troco neles. Mas tem um problema: eles revistam tudo o que você leva pra dentro, não tem como entrar com armas escondidas. Então eu sugiro esquecer essa ideia.";
			link.l1 = "E ainda assim, essa é a nossa melhor opção no momento. Vou pensar em como conseguir armas para você e seus homens... Me diga, quantos de vocês sabem lutar?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Trinta cabeças, eu diria.";
			link.l1 = "Trinta sabres então... Pistolas também fariam diferença, acredito.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Capitão, você está falando sério sobre isso?";
			link.l1 = "Sou eu. Vim aqui de propósito, e não estou para brincadeiras. O que mais você precisa?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Very well... Let's give it a try at least. We need simple cold steel - my boys are not trained to work with fancy rapiers and the like. The same goes for handguns, the cheapest will do just fine. If you can get us a musket or two, that would help us a lot as well; I have a couple of lads who are good with muskets. Bullets, gunpowder. Healing potions are most welcome.";
			link.l1 = "Entendido. Espadas e machados podem ser pegos no arsenal do navio. O resto é mais difícil de conseguir. Aviso quando tiver tudo.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Por favor, anda logo, irmão. Não temos meio ano aqui, esse maldito trabalho com o gado está nos matando um por um. Se precisar de mim, me procure à noite.";
			link.l1 = "Entendi, camarada. Aguenta aí, vou tentar não te deixar esperando. E cuidado, não dê motivo pra te descartarem tão cedo.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Alguma novidade, camarada? Conseguiu juntar as armas?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Sim. Um baú de munições está na Baía de Guajira. Só falta encontrar um jeito de levar isso discretamente para a plantação.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "Pode deixar. Espere.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Muito bem, capitão. Eu já estava pensando em como fazer isso.";
			link.l1 = "Que bom ouvir isso. O que você tem em mente?";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "They produce sugar and grow cocoa beans on this plantation. Sometimes its head sells the goods himself; it's more profitable that way. Make him an offer. Pay him not with money, but with goods. Something you can pack into boxes, like copra, vanilla, or coffee. Put some effort into bargaining, but don't overdo it\nStash weapons in one or two boxes and mark them. Arrange an exchange in the evening so they will have to leave the boxes outside overnight\nAt night, we will find your marked boxes, arm ourselves, and give hell to the Spanish. With your help, of course.";
			link.l1 = "Boa ideia, irmão! Muito bom, gostei desse plano. Vamos manter assim.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "Mais uma coisa - ofereça apenas um tipo de mercadoria para troca. Quanto mais tipos de mercadorias, mais caixas os guardas vão marcar.";
			link.l1 = "Concordo. Então vou escolher só um tipo. Café, baunilha e copra, foi isso que você disse?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Sim. Isso vai soar como um bom acordo para o chefe da plantação.";
			link.l1 = "Entendi. Aviso você quando o acordo estiver fechado.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "Vá, meu amigo, o tempo é ouro e não temos nenhum...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "...";
			link.l1 = "(em voz baixa) O acordo está feito. As caixas serão entregues na plantação amanhã à noite. As caixas que você precisa estão marcadas com a letra 'W'. As outras têm o restante do alfabeto. Prepare seus homens. Vamos atacar antes do amanhecer, por volta das três horas.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "Vamos começar ao seu sinal...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Finalmente! Estou prestes a ver o mar de novo! Quase tinha esquecido como ele é e como cheira. Muito bem, capitão! Estou em dívida com você.";
			link.l1 = "Não se preocupe com isso, a gente resolve depois... Agora vamos embarcar e sair daqui!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Saudações "+pchar.name+".   Fico feliz em te ver de novo, e também estou contente por ter você como meu companheiro nesta aventura. Este trabalho vai ser difícil, mas tenho certeza de que vamos conseguir superar juntos.";
			link.l1 = "Nice to see you again, Picard. I'm all ears; tell me about this adventure of yours.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "Já contei para o Marcus, e agora vou contar pra você. Quando eu era escravo na plantação em Maracaibo, aprendi uma coisa com os espanhóis. Eles falam demais quando estão bêbados... Escuta, a sudeste da baía de Maracaibo tem uma vila pequena. Ela fica escondida entre duas montanhas, bem no meio da selva. O nome é um inferno de comprido: Santiago-de-Los-Caballeros-de-Merida. Vamos chamar só de Merida\nAinda não parece grande coisa, né? Mas as montanhas ao redor da vila são cheias de pedras preciosas. Esmeraldas, opalas e as lendárias opalas de fogo\nPelo que entendi, os colonos de Merida não contaram nada sobre essas pedras ao governador-geral. Mas logo ele vai descobrir, por isso precisamos ir até Merida antes que os oficiais coloniais espanhóis cheguem.";
			link.l1 = "Você quer saquear o povoado?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Exatamente. Fica perdida entre selvas e montanhas, com uma pequena guarnição – presa fácil para um grupo de corsários. Além disso, estão longe do mar, não esperam ser atacados por ninguém além de selvagens com lanças e arcos.";
			link.l1 = "Quão certo você está de que o povoado tem pedras preciosas?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "Se a nossa aventura acabar sendo uma pista falsa, eu mesmo vou servir no seu navio como oficial ou marinheiro. Vou limpar o convés e lutar em incontáveis abordagens até que minha dívida com você e Marcus esteja paga.";
			link.l1 = "Entendi... Muito bem, você sabe como chegar a Mérida?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Claro que eu não sei o caminho exato pela selva, mas vamos contratar um guia dos índios locais. Devemos desembarcar ao sul do Lago Maracaibo, encontrar uma aldeia indígena e procurar quem conheça o caminho.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Captain, I am deeply sorry for my language, but why the actual fuck are we not in Merida yet? Huh? You have spat on our common cause! Leprechaun and I are leaving without you. I will explain everything to Tyrex, and you should go. Here, take 50,000 pesos for your help in Maracaibo; I borrowed them from friends. Farewell, damn shame, I thought better of you.";
			link.l1 = "Hmm... Me desculpe.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Aqui estamos. A selva está logo à frente. Primeiro, devemos encontrar uma aldeia indígena e perguntar por um guia.";
			link.l1 = "Vamos nessa. Luke, você tem algo a dizer... ou talvez algum conselho?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "A guarnição de Mérida está pronta. Não espero muita resistência na vila. Vamos!";
			link.l1 = "Avancem!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "Está feito! Não sobrou nenhum herói. Agora devemos falar com o governador desta 'cidade'. Espero que ele seja do tipo que se deixa convencer.";
			link.l1 = "Concordo, vamos 'convencê-lo'!.. Jean! Venha comigo!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "Mandou bem, "+pchar.name+"! Hora de dividir o saque. Já tenho os números. Havia quase 2000 gemas no baú: 1560 esmeraldas, 1032 opalas e 363 opalas de fogo. Sua parte é um terço: 350 esmeraldas, 244 opalas e 63 opalas de fogo. Aqui, pegue.";
            }
            else
           	{
           	dialog.text = "Mandou bem, "+pchar.name+"! Hora de dividir o saque. Já tenho os números. Havia quase 2.000 gemas no baú: 1.050 esmeraldas, 732 opalas e 189 opalas de fogo. Sua parte é um terço: 350 esmeraldas, 244 opalas e 63 opalas de fogo. Aqui, pegue.";
           	}
			link.l1 = "Legal!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "Agora vamos falar sobre a minha dívida com você por ter me resgatado. Sei que você teve despesas consideráveis. Que compensação você acha justa? Vou pagar com a minha parte das gemas.";
			link.l1 = "Um terço da sua parte já basta. Você também precisa de dinheiro – para comprar e equipar um navio, para pagar sua tripulação...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "Obrigado, amigo! Achei que você fosse pedir pelo menos metade. Estou mesmo precisando de dinheiro agora. Aqui, fique com as joias.";
			link.l1 = "Que saque, Jean! Vamos para Hispaniola, para Tyrex.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "Oh, que encontro! É um prazer ver você, "+pchar.name+". Como você está?";
			link.l1 = "Bem, até que estou indo bem. Achei o tesouro do Lobo Vermelho faz pouco tempo. Agora estou indo pra Martinica encontrar um amigo em comum nosso. Quer ver o Tyrex?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Sim. Quero falar com ele sobre o Pasquale Lavoisier. O Marcus me mandou até aquele sujeito, meio bandido, meio comerciante. Fiz o que ele pediu, e ele me pagou com uma porcaria, dizendo que era um pagamento e tanto. Eu teria matado o desgraçado ali mesmo, mas o Marcus pediu pra eu tratar ele com respeito... então agora é com ele pra resolver essa confusão.";
			link.l1 = "Desculpe, mas o Marcus não vai fazer nada. O Quatro-olhos está em negócio com ele.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "Que diabos?";
			link.l1 = "É, mas eu não te contei sobre isso, tá? O Lavoisier também me ferrou há pouco tempo. O Tyrex me pediu ajuda, do mesmo jeito que pediu pra você. Me avisaram lá na Isla Tesoro que mexer com o quatro-olhos é a mesma coisa que mexer com o Marcus. Então, meu conselho é esquecer isso. Você não é o primeiro nem vai ser o último nessa história.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "Entendi. Aqueles dois também passaram a perna em você?";
			link.l1 = "Bem, sim. Eu também pensei em arrumar confusão com o quatro-olhos antes de saber mais sobre ele. Não vale a pena.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Você tentaria se vingar do desgraçado se soubesse que ninguém jamais descobriria?";
			link.l1 = "Ha! Claro que eu toparia! Mas não faço ideia de como. Ataque as flautas do Lavoisier e, mais cedo ou mais tarde, seus marujos vão se embriagar e contar tudo. Você não sabe como essas coisas funcionam?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Você está indo para Martinica agora? Quando vai chegar em La Vega de novo?";
			link.l1 = "Marcus me deu três semanas.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Tente fazer isso em dois dias. Vou pensar melhor... Me encontre na Baía de Gonaïves em 14 dias. Vá direto para lá e não entre em La Vega.";
			link.l1 = "Eu vejo que você está aprontando alguma coisa, haha. Tudo bem. Vou tentar.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "É melhor você fazer isso. Até mais!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Onde está seu navio? Você veio de La Vega? Merde! Eu pedi pra você vir aqui discretamente, em segredo. Agora meu plano está arruinado. Droga!..";
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Aí está você, "+pchar.name+". Que bom que você está aqui. Mande seus companheiros voltarem para o navio. É uma conversa particular.";
				link.l1 = "Muito bem.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Aí está você, "+pchar.name+". Que bom que você está aqui. Tenho uma proposta de negócio para você. Pronto para ouvir?";
				link.l1 = "Claro!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Já te disse - mande seus oficiais saírem!";
				link.l1 = "Sim, sim, entendi.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Ótimo. Agora podemos conversar à vontade. Tenho uma proposta de negócio para você. Pronto para ouvir?";
				link.l1 = "Claro!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Você conhece bem La Vega?";
			link.l1 = "Bem... Acho que sim. Por que está perguntando?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "Já reparou no armazém à direita da loja local? A única casa grande entre os barracos.";
			link.l1 = "Aquela que está sempre fechada? Sim, já vi. Por que pergunta?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Bem observado – está sempre fechada. Enquanto você estava em missão na Martinica, nosso amigo em comum, Lavoisier, ficou aqui por três dias como hóspede de Marcus Tyrex. Eles passaram o tempo nesta casa bebendo rum e se divertindo.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Depois, os homens do Lavoisier arrastaram algumas caixas e pacotes para dentro da casa. Em seguida, ele foi embora. Quanto ao Marcus, ele fica lá todos os dias por várias horas.";
			link.l1 = "Alguma sugestão?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "Que sugestões? Tenho certeza de que esta casa deve ser a base do Lavoisier em La Vega. Não vi muito pela janela, mas tem mercadorias guardadas lá. Acho que o quatro-olhos tem como pagar o que nos deve.";
			link.l1 = "Então, então... Quer mesmo arrombar? E a porta trancada? Ela é pesada e resistente, não tem como entrarmos sem fazer barulho.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", você acha que eu sou idiota? Já resolvi isso. Mandei fazer a chave usando uma impressão de cera da fechadura. Custou caro, mas esse é o meu problema.";
			link.l1 = "Hein! Então por que esperar por mim?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "Vai ser mais seguro assim, além disso, você é a única pessoa em quem posso confiar. Uma cabeça pensa bem, duas pensam melhor, e quatro olhos enxergam mais do que dois.";
			link.l1 = "Bem, sim, enfrentar o Lavoisier vai exigir tantos olhos quanto ele tem, ha-ha-ha! Mas e o Tyrex? E se ele entrar na casa enquanto estivermos vasculhando as coisas do Pasquale?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "Ele não vai. Ele sempre volta pra casa dele antes da meia-noite. Pronto pra ir pra La Vega amanhã à noite? Eles nunca vão descobrir quem acabou com eles: você ainda está na Martinica e eu saí de La Vega faz uma semana.";
			link.l1 = "Eu adoraria pegar aquele desgraçado de quatro olhos. Mas me diz, Jean, como é que a gente vai carregar os barris e baús da casa?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "Tenho certeza de que vamos encontrar coisas mais valiosas lá do que baús e barris de mercadorias, e ainda por cima bem mais leves. Então, vai topar?";
			link.l1 = "Com certeza que sim!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Ótimo, ainda bem que não me enganei sobre você. Vamos descansar agora, partimos para La Vega à meia-noite.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Hora de ir. Vamos roubar esse desgraçado e cair fora daqui antes do amanhecer.";
			link.l1 = "Em frente!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "Silêncio... Agora vá devagar até a casa do Pasquale. Siga-me.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Olha só isso – tanta coisa espalhada por aí. Vamos começar. Veja o baú perto da porta, depois suba e dê conta de um dos quartos. Eu fico aqui: sei como esconder coisas de valor no meio da bagunça. Fique atento e não chegue perto das janelas.";
			link.l1 = "Certo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", o que você tem? Alguma coisa interessante?";
			link.l1 = "Venha ver. Isso é interessante.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Maldição! Agora entendo por que o Tyrex vem aqui todo dia. Isso aqui não é só o depósito do quatro-olhos, mas também um bordel.";
			link.l1 = "Parece que ela é uma escrava aqui.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Claro. Olha pra ela – é uma prostituta de porto, isso tá na cara... Péssima sorte pra gente. Vamos ter que matá-la.";
			link.l1 = "Sério mesmo?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "Ela viu nossos rostos e ouviu seu nome. Ela vai contar tudo para o Tyrex.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "É sua escolha. A vida dela pode custar a sua.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Nem pense em confiar nessa vadia. Amanhã Tyrex vai saber de tudo. Quer receber uma marca negra?";
			link.l1 = "Não, eu não quero. E também não quero matar a garota – ela ainda me serve. Ela vem comigo.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Não seja tolo! Ela vai fugir assim que tiver uma chance. Olhe para a testa dela, está vendo a marca? Ela é ladra.";
			link.l1 = "Hm. Você provavelmente está certo, Jean. Muito bem, acabe com ela e vamos sair daqui.";
			link.l1.go = "rocur_82";
			link.l2 = "Não pretendo mantê-la no meu navio. Tenho um lugar para ela de onde nunca vai escapar, e lá ninguém vai ouvir seus gritos. Ela também vai continuar fazendo o que sabe... Uma prostituta particular, de graça, he-he!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "É isso, agora ela não vai dizer nada para o Marcus...";
			link.l1 = "Pobre garota... hah, bem, como dizem, a sorte é uma desgraçada...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "Você é um homem bondoso, "+pchar.name+". Por que você quer se incomodar com ela? Ah, tanto faz, é sua escolha. Só garanta que ela fique quieta enquanto saímos.";
			link.l1 = "Se ela não for - ela está morta.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "O que você encontrou?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "A sorte está do meu lado de novo. Aqui, pegue sua parte. Eu nunca conseguiria levar tudo isso para a terra sozinho. O quatro-olhos pagou a gente direitinho.";
			link.l1 = "Excelente! Muito bem, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Agora vá!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "Ótimo. Está feito. Tudo tranquilo. Agora, vamos voltar para os navios.";
			link.l1 = "Hah, boa ideia.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "Bem, "+pchar.name+". Chegou a hora de seguirmos caminhos diferentes. Não sei se vamos nos encontrar de novo, mas saiba que foi um prazer te conhecer, amigo.";
			link.l1 = "Ah, venha, nós vamos nos ver com frequência em La Vega.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "Não. Chega de Tyrex pra mim. Essa confusão com o Lavoisier foi a gota d’água.";
			link.l1 = "Hum... Entendi, deixa pra lá. Conseguimos o que era nosso por direito. O Tyrex sempre indica bons negócios, não é? Da última vez, tirei mais de meio milhão do tesouro do Lobo Vermelho.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Então me diga, você se esforçou muito para encontrar isso?";
			link.l1 = "Bem... Não foi fácil. Pensei muito, viajei e lutei bastante. Mas acho que valeu a pena.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "Quanto você pagou para o Tyrex?";
			link.l1 = "Um terceiro.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "Qual foi o papel dele nessa história? O que exatamente o Marcus fez?";
			link.l1 = "Hm... Ele me deu o diário do Lobo Vermelho...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "E é só isso? Certo?";
			link.l1 = "Bem... Eu nunca teria ouvido falar do Capitão Wulfric de outra forma...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", você não percebe que o Tyrex sempre faz os outros sujarem as mãos por ele? Você realmente acha que ele te daria a missão de encontrar aquele tesouro se pudesse fazer isso sozinho? Claro que não! Aposto que ele tentou primeiro, e quando estragou tudo, chamou você pra consertar a bagunça. E enquanto você quebrava a cabeça, passava semanas no mar, lutando e arriscando a própria vida, aquele desgraçado e o nojento do amigo de quatro olhos estavam se divertindo com a prostituta em La Vega. E por isso, ele ainda embolsou um quarto de milhão de pesos. Assim, do nada Você acha que ele mandou o cachorro dele, o Leprechaun, pra nos ajudar no ataque a Mérida? Não, ele só queria garantir que os interesses dele estivessem protegidos. Tudo que o Marcus consegue fazer sozinho, ele faz, seja sozinho ou com ajuda dos Cutlasses, Carecas, Leprechauns e outros idiotas que trabalham pra ele por trocados. Gente como eu e você, a gente pega as pontas que o Marcus é burro demais pra resolver sozinho Lembra de todas as tarefas que você fez pra ele? Conta quanto ele já lucrou às suas custas. Cansei disso. Agora eu tenho dinheiro, uma bela corveta e uma tripulação fiel... de agora em diante, sou freelancer. Estou indo pra Jamaica—quem sabe eu consiga uma carta de corso por lá.";
			link.l1 = "Não acho que você esteja totalmente certo sobre o Tyrex... Mas te desejo sorte, Jean! Espero que encontre sucesso na Jamaica.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "I will. Best of luck to you too, and think about what I've said. Being Marcus' lackey is not the best role for you; I know you are capable of much more. Well... farewell, brother! Godspeed!";
			link.l1 = "Boa caçada, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", me diga, como é que a gente acabou passando tanto tempo na selva? Agora meu plano foi por água abaixo. Eh... Tchau, camarada...";
			link.l1 = "Heh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "Hora de partir, rapazes. Caramba, Príncipe, você me surpreendeu. Queimou uma cidade inteira, mas se recusou a sujar as mãos quando realmente importava.";
				link.l1 = "Eu não mandei incendiar a cidade!";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "Hora de partir, rapazes. Lucas, você perdeu essa. O Príncipe resolveu tudo com maestria – e ainda saiu no lucro!";
				link.l1 = "E a cidade, bonitão?! Eu dei minha palavra!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "Pelo menos você não tentou salvá-lo. Caso contrário, nossos homens teriam te esfaqueado primeiro. Foi um dia difícil pra eles. Eles mereciam extravasar um pouco. Você vai se acostumar. Você tem tudo pra isso.";
			link.l1 = "Obrigado pelo conselho, mas não me lembro de ter pedido. Vamos.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " Eu achei que você estava brincando. Bem... você foi apressado demais. A cidade acabou. Sempre é assim quando os Irmãos da Costa entram em ação. Você vai se acostumar.";
			link.l1 = "Não tenho certeza se vou. Tudo bem, vamos.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "Cara... o que foi aquilo agora há pouco?";
			link.l1 = "O quê, não entendeu? Eu te comprei. Você mesmo disse que eu tinha acesso aos espanhóis, então aproveitei isso.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "Eu entendi isso – não sou idiota. Mas a gente não estava com outro plano?";
			link.l1 = "Bem, eu e o Cutlass achamos que não seria certo se você acabasse morto numa revolta ou numa perseguição, então decidimos comprar sua liberdade de uma vez.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "Hah, não me insulte. Afinal, sou um dos capitães do Terrax. Eu sei como manejar uma lâmina.";
			link.l1 = "Eu não duvido disso, mas você está mesmo chateado por estar livre?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "Não, não – eu agradeço. É só que... não foi um exagero gastar tanto ouro assim? Só de pensar nisso já me dá um aperto no estômago. Já o fazendeiro, por outro lado, parecia tão reluzente quanto uma bandeja de prata polida.";
			link.l1 = "É, 'O Negócio do Século', de fato. Dói um pouco, claro. Mas o tempo vale mais do que ouro, Jean. Procurar pistolas e remédios para todos vocês...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "Eu agradeço, mas, amigo, você é um tolo – sem ofensa. Eu te disse que meus rapazes não são bons com espadas. Mas qualquer um pode puxar um gatilho. Você podia ter trazido qualquer pistola e remédio do porão, como fez com as espadas e machados – eles não são exigentes.";
			link.l1 = "Hum, pra ser sincero, eu não tinha pensado nisso... Enfim, vamos – o Cutlass provavelmente já está ficando impaciente.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Saudações, capitão "+GetFullName(pchar)+". Luke, o Duende, ao seu dispor! Disseram que estamos indo para as selvas do sul do continente.";
			link.l1 = "Exatamente. Embarquem nos botes, estamos partindo agora mesmo.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Deixe um velho bucaneiro te dar um conselho, capitão. Já que vamos entrar na selva, com certeza vamos encontrar os índios. Leve presentes para eles. Os guerreiros indígenas adoram pistolas boas, especialmente as de duelo. Também gostam de bússolas e lunetas, que consideram objetos mágicos.\nAs mulheres deles preferem bijuterias baratas e bugigangas como espelhos e pentes. Se acabarmos brigando com eles, use bacamartes e arcabuzes: chumbo grosso em geral é muito eficaz contra inimigos que não usam armadura. Quanto ao povoado em si, sugiro armas que possam usar cartuchos de papel.";
			link.l1 = "Muito bem, Luke. Suas palavras foram anotadas. Bem-vindo a bordo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "See the chieftain as soon as we reach the village. And bring gifts, it's pointless otherwise. Make sure to ask if anyone among his people knows about secret passages in the jungles ahead, and ask for those who have no fear of travelling. I am coming with you; address me if you face any difficulties.";
			link.l1 = "Vamos! Jean, Luc - venham comigo!";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Alguma dúvida, capitão?";
			link.l1 = "Por enquanto, nada, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Sim! Falei com o chefe deles, dei presentes, e depois ele reuniu o povo para uma reunião. Alguns sabem como chegar a Merida, mas ninguém quer ir—eles têm medo de uma outra tribo chamada Capongs. Esses Capongs deixam os locais apavorados. O desgraçado diz que não temos chance de achar o caminho sozinhos e que não existe guia que possamos contratar. E agora, o que a gente faz, hein?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "Tenho antídotos comigo.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hmm, entendo... Capitão, saiba que muitas vezes a cobiça vence a covardia. Prometa uma recompensa tão generosa que qualquer homem topará o trabalho... Sabe de uma coisa? Tente uma abordagem mais astuta – as mulheres deles. Dê presentes e pergunte sobre seus maridos, e é bem provável que encontre o guia que precisamos. Prometa montes de contas e espelhos pela ajuda do marido dela. Seja generoso e prometa muito, convença-os.";
			link.l1 = "Heh! Bem, o mínimo que posso fazer é tentar, embora eu não tenha certeza se vai funcionar...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "Bem, tem outra opção... Mas não é exatamente das melhores, se é que você me entende.";
			link.l1 = "Outra opção? Manda ver! Não estou nada animado para ir até as índias e implorar para que convençam seus maridos a se juntarem a nós.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "Essa opção é tão antiga quanto o tempo. Mostre a eles que devem temer você mais do que temem os Kapongs. Sabe... Você poderia dizer ao chefe o que seus piratas seriam capazes de fazer com todas as mulheres da aldeia, especialmente com a esposa e as filhas dele. Poderia até ameaçar com tortura.  Enfim, tenho certeza de que você vai encontrar um jeito de fazer esses índios te temerem. Pessoalmente, não gosto desse caminho, e tenho meus motivos para isso.";
			link.l1 = "Razões? Tipo quais? Pra mim, parece uma solução bem eficaz e direta.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "Para começar, não vamos ser exatamente bem-vindos na cidade depois disso. Podemos acabar caindo numa armadilha ou em outra situação desagradável. E, além disso, bem... isso simplesmente não parece certo. Uma coisa é enfrentar inimigos armados, outra bem diferente é ameaçar mulheres. Eu sugeriria encontrar uma forma de lidar com os índios de maneira mais... diplomática.";
			link.l1 = "Entendi, vou pensar nisso. Talvez eu tente conquistar alguma moça com miçangas... Ou quem sabe invente umas maneiras criativas de atormentar as filhas do chefe, haha!";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "Mais uma coisa, Capitão, de acordo com o chefe, podemos encontrar uma tribo hostil de índios nas selvas. É bem provável que sejam apenas um pequeno grupo de canibais, mas é melhor prevenir do que remediar. Se for uma tribo guerreira, eles vão envenenar suas armas, então certifique-se de fornecer antídotos aos seus homens.   Meus homens e eu sempre carregamos muitas poções conosco. Quanto aos seus piratas... Apenas traga os antídotos para mim e eu vou distribuí-los entre seus homens. Vou precisar de pelo menos uma dúzia de poções para isso. Não se esqueça de trazer algumas para você e seus oficiais também.";
			link.l1 = "Certo. Eu vou trazer os antídotos.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Muito bem. Me entregue eles. O resto é comigo.";
			link.l1 = "Lá...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Quarenta e duas poções serão suficientes. O resto você deve guardar para si.";
			link.l1 = "Certo...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Capitão, seus índios - Hayami e Tagofa - já esperaram demais pelos presentes que você prometeu e foram para outra aldeia dançar e beber kasheeri. Tenho a impressão de que seu jeito de negociar não vai nos trazer nada de bom. Sinto muito, mas você está fora dessa. Picard vai liderar a expedição.";
			link.l1 = "Então vão todos se ferrar!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Capitão, que diabos? Já perdemos tempo demais à toa! Tenho a impressão de que seu jeito de conduzir as coisas não vai nos levar a lugar nenhum. Sinto muito, mas você está fora dessa. Picard vai liderar a expedição.";
			link.l1 = "Então vão todos se ferrar!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Capitão, que diabos? Você teve dez dias para encontrar couro e tábuas. Tem a cidade de Maracaibo não muito longe daqui! Tenho a impressão de que seu jeito de fazer negócios não vai nos levar a lugar nenhum. Sinto muito, mas você está fora dessa. Picard vai liderar a expedição.";
			link.l1 = "Então vão todos se ferrar!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Captain, I'm sorry, but I was supposed to be in La Vega long ago, as were you, actually. You must have forgotten about Marcus and me. Anyway, I'm leaving. You should keep doing whatever it is you're doing, and I'll explain everything to Marcus. Farewell, it's a pity; I thought better of you.";
			link.l1 = "Hmph...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "Então, pelo que entendi, vocês brigaram. Não conseguiram dividir o saque, não é, Charlie Prince?";
			link.l1 = "Leprechaun? Você está aqui... Mas não é nenhuma surpresa. Sim, aqueles bastardos gananciosos cuspiram no Código e tentaram me matar.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "É, eles te deram uma bela surra, Príncipe. Você está parecendo um trapo molhado O que foi que você disse sobre o Código? Deixa eu te explicar: eu já trabalhei com o Marcus, que dizem ser o Guardião desse Código. Já vi homens cuspirem nele tantas vezes que perdi a conta. Alguns desses homens pagaram um preço terrível. Outros, não Você pode fazer o que quiser, se a recompensa valer a pena. Principalmente se ninguém estiver olhando.";
			link.l1 = "Então... você também está aqui pelo tesouro?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Que pergunta idiota. O que mais eu estaria fazendo aqui, tão longe da minha terra em Hispaniola? Embora, no fim das contas, eu seja mais esperto que todos vocês: conheço bem essa natureza podre de pirata. Só esperei, deixando vocês, ratos, se destruírem uns aos outros, sobrando apenas um inimigo vivo, mas ferido e exausto.";
			link.l1 = "Inimigo? É assim que você segue o Código do seu patrão?! Ele mata pessoas por causa disso!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "Eu não estou sujeito ao Código Príncipe, não sou um pirata. Nem sequer tenho um navio – precisei alugar uma sucata para chegar aqui. Não passo de um bucaneiro, no fim das contas. Sou caçador, caço búfalos e faço buccan. Malditos espanhóis, que dizem que nós, bucaneiros franceses, acabamos com o sustento deles, me obrigaram a buscar apoio e proteção com Marcus. Por isso às vezes ajudo nos negócios dele.\nApesar de não ser pirata, meus homens e eu lutamos bem, você já nos viu em ação.";
			link.l1 = "Nós saqueamos e lutamos juntos, Leprechaun. Sempre cuidamos um do outro, arriscando a vida para nos salvarmos. Isso não significa nada pra você?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "Vou ser honesto com você, Príncipe: nunca gostei de você. Você é um arrivista. Um garoto insolente, amante da bebida e de mulheres perdidas, que fez uns trabalhos lucrativos para o Tyrex e já se acha um grande pirata\nAlém disso, você é carniceiro por instinto. Acha mesmo que Cartagena te deu mais respeito entre os Irmãos? Ha-ha, de jeito nenhum, só entre monstros como você.";
			link.l1 = "Ah, isso é hilário! Ha-ha-ha, dito por um verdadeiro anjo! Seu velho safado!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "Acho que já resolvemos tudo por aqui. Hora de acabar com essa farsa. Os demônios estão te esperando no inferno faz tempo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "Você gosta, hmm?";
				link.l1 = "Afaste-se!";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "E então, o que você acha?";
				link.l1 = "Isso não tem graça, Leprechaun. Que diabos?! Eu não mandei fazer um massacre! Você não acha que isso é exagero?! Terrax não vai gostar nada disso!";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "Por que essa cara de culpa, então? Não está gostando? Vou te dizer uma coisa – as coisas só vão piorar. Acha que o massacre de hoje aconteceu só porque o dia estava assim? Hah, sei. Isso é rotina. Picard nem piscou. Pra eles, é só mais um dia fazendo o que amam.";
			link.l1 = "E você? Só está de passagem?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "Eu não sou pirata. E preferia não ter feito parte dos acontecimentos de hoje. E... se você fica tão perturbado ao ver corpos de mulheres no solo enegrecido de Merida, por que agiu daquele jeito com os índios, Príncipe?";
			link.l1 = "O que eu deveria ter feito? Largar tudo e rastejar até Marcus pedindo desculpas?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "Eu achei que você já tinha abraçado isso de vez, começado a pensar e agir como os capitães do Tirax. Mas não, ha! Você é mole demais pra esse tipo de trabalho. Era melhor entregar sua parte pro Marcus e sair daqui de cabeça baixa. Isso não é pra você.";
			link.l1 = "Não cabe a você decidir por mim, Leprechaun. E você certamente não tem o direito de me insultar. Não vou abrir mão da minha parte para ninguém. Vou dividir de forma justa com o Terrax.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "Claro. Mas é melhor a gente ir antes que você desmaie.";
			link.l1 = "Isso não tem graça, droga.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "Então você não o conhece tão bem assim. Ainda assim, já que os acontecimentos de hoje não te alegram, ouça o que tenho a lhe oferecer.";
			link.l1 = "O que mais você poderia oferecer depois disso?!";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "É melhor você se esforçar para ouvir, garoto.";
			link.l1 = "Hum, não gostei do seu tom, Lucas, mas tudo bem, vá em frente.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "Eu posso me dar a esse luxo – já vivi mais do que você, Príncipe. Por isso, tenho um olhar afiado, não só pra atirar. Quer saber o que eu percebi?";
			link.l1 = "Fala logo!";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "Você está fora do seu lugar. Sim, você é bom. Está avançando. Mas só porque é um capitão forte, não porque isso seja realmente o seu destino. Não sei como você acabou indo para Terrax, ou por quê, mas acredite, esse não é o seu caminho.";
			link.l1 = "Eu tenho... um objetivo. Não posso te dizer qual é.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "E você chegou mais perto disso?";
			link.l1 = "Ainda não.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "Bem, se nem hoje isso aproximou vocês, não há mais nada a ganhar aqui. Você é um bom homem, Príncipe. Tratou os índios como gente. É irônico você ter acabado aqui conosco. Meu conselho: entregue sua parte ao Terrax para evitar problemas e fique longe de tudo isso – salve sua alma enquanto ainda pode.";
			link.l1 = "Vou pensar nisso.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa te saúda, filho do mar. Quer que eu te mostre o caminho para o assentamento espanhol nas montanhas?";
			link.l1 = "Certo. Vejo que você se dá bem com o nosso idioma, diferente do resto do seu povo.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofa costumava negociar com os Yalanaui... Na maior parte da nossa viagem, vamos seguir pelo rio. Você vai precisar de barcos pequenos. Você tem algum?";
			link.l1 = "É mesmo? Podemos pegá-los emprestados por um tempinho...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Nossa vila é pequena, temos poucas canoas e todas servem só para pescar. Agora, precisamos de boas canoas, daquelas que aguentam uma viagem longa, como as dos seus navios.";
			link.l1 = "Hum... Então vamos precisar de seis botes. O navio não tem tantos assim.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Então construa-os. Vocês, brancos, conseguem consertar seus navios enormes em terra, com certeza podem fazer alguns botes também.";
			link.l1 = "Heh, parece que você está certo, Tagofa. Leve-nos até o rio, espero que não esteja longe daqui?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "Não é. Me siga.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Aqui está o rio de que te falei. Vamos começar nossa jornada daqui. Você constrói os barcos e então partimos.";
			link.l1 = "Entendi, Tagofa. Aviso quando estiver pronto.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Os barcos estão prontos, chefe branco?";
			link.l1 = "Sim. Meus homens estão prestes a abordá-los.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Muito bem. Venha comigo no primeiro. Tagofa vai mostrar o caminho.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "A parte do rio já ficou pra trás. Não estamos longe do assentamento espanhol daqui. Ali está a trilha, siga por ela e não vamos nos perder. Conseguimos contornar uma floresta cheia de caçadores Capong, mas essa terra também é deles. Precisamos ter cuidado.";
			link.l1 = "Não se preocupe. Vamos acabar com eles assim que mostrarem essas caras feias e pintadas.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "Ei! Tagofa! Olha! O que é aquilo... bem no meio do caminho? Alguma coisa de índio.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "É um sinal dos Capongs. Um aviso. Diz para você parar e não seguir adiante. Os Capongs já nos viram.";
			link.l1 = "E se a gente for mais longe? Eles vão atacar a gente?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Sim, chefe branco. Você deve parecer ameaçador para eles, já que ainda não nos atacaram. E mesmo assim, colocaram um aviso para você.";
			link.l1 = "Que se dane o aviso. Vamos em frente... Atenção, todos! Às armas! Preparem-se! Fiquem atentos! Se esses selvagens aparecerem, vamos acabar com todos eles!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "O chefe branco e seus homens derrotaram os capongas, Tagofa está impressionado. A cidade espanhola está perto. Há um vale onde você verá uma cachoeira. Tagofa não irá até os espanhóis. Estarei esperando por você perto da cachoeira.";
			link.l1 = "Muito bem. Em frente!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "Voltamos, chefe branco. Tagofa fez o que prometeu.";
			link.l1 = "Obrigado, Tagofa. Você fez um bom trabalho.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofa deve ir. Hayami está me esperando. Adeus, filho do mar.";
			link.l1 = "Boa sorte, filho da selva. Mande lembranças à sua esposa. E obrigado por nos ajudar.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Ei! Quem é você e o que quer?";
			link.l1 = "Precisamos chegar a Mérida e conversar com o seu governador, ou seja lá quem estiver no lugar dele...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "Não deixamos estranhos entrarem em Mérida. Vá embora!";
			link.l1 = "Amigo, remamos feito loucos por dois dias e depois lutamos contra hordas de índios, não vamos embora assim tão fácil. Repito, quero falar com o chefe da sua aldeia! Temos uma... proposta de negócio para ele, sim! E se todos concordarmos, sua aldeia ficará intacta.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Está me ameaçando, ladrón?";
			link.l1 = "Como você descobriu isso? Ah, sim, de fato, estou fazendo ameaças. Ou conseguimos o que viemos buscar de forma pacífica, ou pela força, e você tem a honra de decidir o destino da sua vila.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "Você nunca vai entrar em Mérida, seu maldito pirata! Alarme! Inimigo nos portões!";
			link.l1 = "Um cavalheiro tão irracional...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Malditos ladrões! O que vocês querem de nós?! Esta é uma vila pequena e modesta. Não temos nem ouro nem prata! Como é que vocês nos encontraram?";
			link.l1 = "Ah, não se faça de inocente e desentendido, Sua Excelência. O mundo inteiro já está cheio de boatos sobre suas opalas.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "E vocês causaram esse massacre sem piedade por... rumores?! Não pouparam ninguém! Animais... Saibam disso: os depósitos ficam bem longe daqui. Não há nada para vocês ganharem aqui. Vão embora.";
			link.l1 = "Você começou esse massacre sem alma. Os civis lutaram ao lado dos seus soldados. Nunca vou acreditar que um heroísmo tão sem sentido seja possível só para proteger algumas paredes vazias.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Você faz ideia de quanto esforço foi preciso para erguer essas paredes? Não contratamos construtores de fora — fomos nós mesmos que levantamos, tijolo por tijolo. Cada morador participou. Até eu, com estas próprias mãos.";
			link.l1 = "Que história comovente... E quanto aos móveis? Vocês também fizeram tudo isso? Que cadeira lindamente entalhada. E a mesa. E os armários. Isso é carvalho tingido? Ou ébano? Um pouco luxuoso demais para uma 'colônia modesta', não acha?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "A ganância nublou sua mente, ladrón.";
			link.l1 = "Não complique as coisas, Señor Governador. Ou vai se arrepender.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "Vai me torturar, seu maldito pirata? Que pena pra você – eu acredito em Deus Todo-Poderoso. E serei mártir se passar dos limites.";
			link.l1 = "Hm-m...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "Meu amigo, ele não vai falar assim. Deixa que eu resolvo.";
			link.l1 = "Oh?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "Eu me lembro de tudo que aqueles espanhóis arrogantes fizeram comigo naquela maldita plantação. Vou te mostrar, Príncipe. E ainda te conto umas histórias enquanto isso. Você não vai se entediar.";
			link.l1 = "E se você se empolgar demais?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "Ele não vai falar com educação. Eu conheço o tipo dele.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(Confiável) (Honra) (Liderança) Já chega de sangue por hoje, Jean. Eu mesmo vou cuidar disso.";
				link.l1.go = "merida_head_dobro_1";
				Notification_Perk(true, "Trustworthy");
				Notification_Reputation(true, 50, "low");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) Notification_Reputation(false, 50, "low");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "Faça isso. Não vou me envolver. E também não vou assistir.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "Se eu não te devesse nada, teria algumas palavras pra você... Droga. Vai lá. Agora é hora do trabalho de verdade.";
			link.l1 = "Não se esforce demais.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "Como quiser, meu amigo. Vai ser divertido assistir.";
			link.l1 = "Não sorria antes da hora.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "Você diz que vai resolver isso sozinho, sem derramamento de sangue, seu maldito ladrão? Não tem nada que você possa dizer pra fazer pedras aparecerem do nada!";
			link.l1 = "É melhor que apareçam, Governador. Caso contrário, vamos arrasar a cidade e matar todos, menos você. Não gosto dessa solução, mas estou disposto a comprometer minha honra pela minha causa. Seu dever, por outro lado, é proteger os civis, soldados sobreviventes e trabalhadores de Mérida. Ou prefere 'ascender como mártir' às custas do sofrimento deles? Isso não me parece nada divino.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "Maldito seja...\nAli... no baú. Só poupe o povo da cidade!";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(Furtivo) Está tudo dentro do baú?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "Eu cumpro minha palavra. Adeus, Governador.";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "Maldito seja!\nO baú também tem um fundo falso. Pegue tudo!!";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "Mandou bem, Príncipe. Desculpe por ter subestimado você.";
			link.l1 = "Satisfeito?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "Mandou bem, Príncipe.";
			link.l1 = "Satisfeito?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "More than. But... you'll see for yourself. You go ahead; I'll dig around a little more.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "Você prometeu que iria embora da cidade assim que tivesse as joias... Agora elas estão com você e seus ladrões incendiaram nossas casas! Você é um mentiroso e um pirata cruel! Espero que as chamas do inferno sejam tão quentes assim para você!!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", bom senhor. O que o traz aqui?";
			link.l1 = "Eu sou de Tyrex. Fui designado para escoltar seu navio até Bridgetown. Está pronto?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Finalmente! Sim, minha tripulação está pronta para zarpar imediatamente!";
			link.l1 = "Excelente. Prepare as velas, capitão. Vamos zarpar!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Obrigado por me ajudar, capitão! Com você ao meu lado, me senti tão seguro quanto se estivesse atrás dos muros do forte.";
			link.l1 = "Hah, deixa disso, camarada! Tudo por conta do Marcus. Boa sorte pra você, amigo!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "Saudações ao bravo capitão! Permita-me apresentar – Ignacio Marco do Torero, corsário a serviço da Inglaterra.";
			link.l1 = TimeGreeting()+", amigo. Capitão "+GetFullName(pchar)+" às suas ordens. Como posso ajudar?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Ah, eu conheço você! Monsieur "+GetFullName(pchar)+"! Ouvi rumores sobre seus recursos e aliados por todo o Arquipélago. Acredito que minha proposta vai te interessar bastante.";
			link.l1 = "Que oferta?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Vamos até uma taverna tomar um drinque. Eu te conto tudo lá. Isso não é conversa pra se ter na rua.";
			link.l1 = "Muito bem... Vamos!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "Uma rodada, capitão?";
			link.l1 = "Claro!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Heh, aqui eles realmente não misturam rum com água...";
			link.l1 = "E não sirva peixe podre pros clientes, tá bom? Então, qual é o lance?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "Gosto da sua franqueza, monsieur. Diga-me, você está ciente da guerra comercial entre os ingleses e os holandeses?";
			link.l1 = "Sou sim. Tive o prazer de participar disso.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Então não precisa explicar. Como corsário inglês, estou lutando essa guerra do lado deles. Você é mais um freelancer, o que te deixa indiferente sobre contra quem lutar...";
			link.l1 = "Quase. Eu não atravesso a França, me desculpe.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "Com certeza, capitão! Então, direto ao assunto: existe uma pequena ilha habitada entre Curaçao e Trinidad, que não aparece nos mapas... Bem recentemente, eu diria que muito recentemente, os holandeses começaram a usá-la como ponto de parada temporário para reabastecimento e consertos. Parece que eles acham que só eles conhecem essa ilha. Estão enganados. He-he\nHá alguns dias, uma caravana de prata foi pega por uma... tempestade, e agora os holandeses estão consertando seus navios nessa ilha. O navio-almirante perdeu o mastro, então o conserto vai demorar um pouco. Os holandeses estão ocupados com os reparos, e as tripulações estão quase todas espalhadas pela ilha...";
			link.l1 = "E então, de repente, a gente aparece para salvar o dia?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Exatamente, capitão. Eu não consigo fazer isso sozinho, mas com você – é outra história. Vai arriscar? Tenho um bom navio, a tripulação é excelente, e tenho bastante experiência. Suas habilidades... também são dignas de elogio.";
			link.l1 = "Quanto tempo nós temos?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Muito, se não desperdiçarmos e partirmos imediatamente.";
			link.l1 = "Então vamos reabastecer com munições e armas, Capitão Ignacio Marco, e zarpar. Quais são as coordenadas exatas da ilha?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 Norte, 64'11 Oeste. Entendido?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ha! Déjà vu... Entendi.";
			else link.l1 = "Entendi.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "Indo para o 'Torero'. Vou te esperar, capitão!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "Que luta danada, hein, capitão? Agora vem a parte boa: vamos dividir o saque. Metade fica comigo e meus homens.";
			link.l1 = "Muito bem, vamos nessa...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Capitão, o que foi? Onde está nossa prata? Você afundou nosso prêmio?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "De algum jeito a prata foi desperdiçada, mas pelo menos conseguimos um pouco de pau-brasil. Vamos dividir.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Hm... Isso é pouco. Achei que teria muito mais.";
				link.l1 = "Temos o que temos.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Nada mal, nada mal. Embora eu achasse que haveria mais.";
				link.l1 = "O que temos é o que temos.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Muito bem feito, Monsieur. Este é um belo prêmio...";
			link.l1 = "Não posso discordar de você nisso, capitão.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Parece que você está com um problema sério na cabeça. Vamos embora! Rapazes!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "Pelo menos conseguimos alguma coisa com isso... Rapazes! Vamos embora!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "É alguma coisa. Vamos cada um para o seu lado.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Já é alguma coisa. Vamos cada um pro seu lado. No fim das contas, deu certo, heh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Tivemos um encontro muito lucrativo. Talvez esta não seja a última vez que fazemos negócios juntos, capitão!";
			link.l1 = "Me chame se encontrar mais algum mercador gordo, he-he!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "Imagino que isso não seja um acidente, Capitão?";
			link.l1 = "Você não seria esperto se não percebesse isso. Você me deve pelo esquema. Você sabe do que estou falando. E também me deve por ter armado contra meu amigo Jean Picard. Ele foi vendido para uma plantação por causa do seu plano... Você perdeu o Ignacio. Eu vou te enforcar, mas você pode aliviar sua punição...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "Eu até me pergunto – o que eu poderia fazer para te fazer sentir pena de mim?";
			link.l1 = "Preciso de informações. Vou te colocar no meu porão de carga, onde vamos conversar sobre seus negócios em Havana...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Eu não esperava por isso! Nem pense nisso. Barbazon vai descobrir minha traição rapidinho. É melhor você nem saber o que ele faz com quem o trai. Eu vi.";
			link.l1 = "Então, ser enforcado é uma opção melhor?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "Prefiro morrer em combate!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Capitão! Capitão! Depressa! O esquadrão militar espanhol está atrás de nós!";
			link.l1 = RandSwear()+"Eu já esperava por isso... Aconteceu a mesma coisa com o Picard. Você viu quantos deles estavam lá fora?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Sim, capitão. Três navios. A nau capitânia deles é um galeão, o maior que já vi, e está vindo rápido. Os outros dois são uma corveta e um xebec.";
			link.l1 = "Todos a bordo. Ainda podemos estar em posição de fugir.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Haya! Maldito yalanaui, invadindo nossa floresta! Matem ele! Haya!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Ei! Que diabos você está fazendo aqui? A-ah, roubando as coisas dos outros? Pois é, agora você se ferrou!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Ei! Todo mundo, parem aí! Ou eu derrubo todos vocês com uma rajada de balas de canhão! "+RandSwear()+"";
			link.l1 = "Não vamos a lugar nenhum agora. Mas escuta aqui, camarada – não tem como você matar todos nós de uma vez. Enquanto recarrega, alguns de nós vão te cortar em pedaços. É melhor conversarmos agora.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "Você é o responsável aqui? Responda!";
			link.l1 = "Eu sou o capitão "+GetFullName(pchar)+". E você deve ser o braço direito do Lobo Vermelho enquanto ele está longe daqui, estou certo?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "O que você está fazendo aqui, capitão "+GetFullName(pchar)+"? Nós não recebemos visitantes neste lugar!";
			link.l1 = "Qual é o seu nome? Quero saber com quem estou falando.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Meu nome é Rodgar Janssen.";
			link.l1 = "Eu vejo que vocês estão perdidos aqui. Não têm mais capitão. E a corveta de vocês também se foi. A 'Freyja' foi destruída pelos espanhóis não muito longe de Hispaniola. Toda a tripulação foi morta até o último homem...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" Wulfric... Aahhh-ghhhhh!!! ... Mas como posso saber se está dizendo a verdade?";
			link.l1 = "Eu tenho o diário do seu ex-capitão! Pegamos alguns itens dos destroços da Freyja. Graças ao diário, encontrei esta ilha e esse... tesouro seu.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Hein! Você ainda me deve uma resposta: por que está aqui nesta terra desconhecida?";
			link.l1 = "I'm not going to lie, pal. They say Red Wolf possessed quite a fortune. I'm here to find it, since no such treasure was found on his ship. I believe it should belong to good people; it has no use for Wulfric now, anyway.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ha! Amigo, vou te decepcionar: nem eu, nem ninguém da tripulação jamais viu os tesouros do Wolf. Era arriscado demais perguntar pra ele.";
			link.l1 = "Então é melhor eu procurá-los na sua aldeia. Vai abaixar a arma ou quer que eu invada a vila? Você não tem chance, Rodgar. Se for preciso, trago mais armas e homens.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Antes de morrermos, vamos levar muitos de vocês, seus desgraçados, pro inferno junto com a gente! Talvez até você!";
			link.l1 = "Tem certeza? Você não tem capitão, não tem navio, e ninguém vai vir te salvar. Mesmo que eu simplesmente vá embora, todos vocês vão acabar morrendo de fome em breve!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Hmm... tem alguma sugestão?";
			link.l1 = "Sim, eu sei. Afaste-se da arma e mantenha seus homens sob controle. Juro que não farei mal a você nem a eles. Se quiser, pode se juntar à minha tripulação, ou nós o levaremos de volta à civilização.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Jure isso diante dos seus homens, alto e claro!";
			link.l1 = "Eu juro! Dou minha palavra: você e seus homens não serão machucados.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "Espero que cumpra sua palavra, capitão.";
			link.l1 = "Eu sempre faço isso. Quantos de vocês ainda restam?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "Você está vendo todos nós. Três. O resto morreu na selva tentando te atacar. Eu disse pra não fazerem isso, mas não me ouviram...";
			link.l1 = "Entendi...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "A comida estava acabando. Começamos a caçar papagaios. O 'Freyja' estava ausente há tempo demais. Tínhamos nossas suspeitas, e elas se confirmaram.";
			link.l1 = "Ainda bem que resolvi sair em busca de tesouros. Onde você acha que ele escondeu eles?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "Já te disse: ninguém jamais os viu. Wulfric era cuidadoso com a parte dele, nunca deixava nada se perder. Ele foi justo conosco, mas todos que tentaram encontrar o esconderijo dele desapareceram. Você pode procurar pela vila se quiser.";
			link.l1 = "Esse é o meu plano. Onde fica a casa do Lobo Vermelho?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "O único prédio de dois andares que temos aqui.";
			link.l1 = "Ótimo. Aliás, qual é a sua profissão?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = GetIslandNameByID("IslaMona");
            dialog.text = "Sou carpinteiro e esses dois são meus assistentes. Antes, fazíamos os reparos e carenagem da 'Freyja'. Podemos ser úteis na sua tripulação.";
			link.l1 = "Entendi. Muito bem, você está dentro, depois conversamos sobre os detalhes. Pegue essa arma na entrada. E Rodgar, não saia da vila enquanto eu estiver procurando o esconderijo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Ordens, capitão?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Sim. Os tesouros do seu capitão foram encontrados. Ele os escondeu bem, mas eu fui mais esperto que ele!";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, o que você acha, tem mais alguma coisa que a gente possa fazer com essa base?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, eu trouxe as ferramentas. Elas já deveriam ter sido entregues para você.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "Bem-vindo! Este é Rodrigo Jimenez, o líder de uma pequena, mas muito trabalhadora comunidade de Cádiz. O senhor Jimenez concordou gentilmente em se instalar temporariamente em nossas terras e nos ajudar com a construção.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgar, como você está? Tem algum bom conselho pra mim?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, preciso de um favor.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && PCharDublonsTotal() >=600)
			{
				link.l1 = "Trouxe os dobrões pra você, só não vai gastar tudo em bebida de uma vez.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, confira o armazém. Trouxe os remédios e mantimentos.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "Olá, Rodgar, como estão as coisas no novo assentamento?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, meu navio precisa de reparos. Você e seus homens estão prontos?";
				link.l2.go = "repair";
			}
			link.l3 = "Rodgar, eu gostaria de deixar um dos meus navios aqui.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, eu gostaria de recuperar um dos meus navios.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Olha, tem algum prédio vazio que eu possa usar como armazém?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, quero ver o armazém.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, quero deixar parte da equipe na ilha.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "Rodgar, quero levar meus marinheiros comigo de volta ao mar.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "Ainda nada...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Parabéns, Capitão. O que fazemos agora? Vamos partir?";
			link.l1 = "Você está aqui há muito tempo?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "Tempo demais. Já faz um ano desde que o Wulfric me deixou no comando aqui.";
			link.l1 = "Eu decidi que essa base secreta é valiosa demais para ser desperdiçada. A vila agora é minha. Posso deixar você e seus homens aqui, se quiser. Rum, mantimentos, remédios – tudo de vocês.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "Seria ótimo, capitão. Já me acostumei com a vida nesta praia, nesta ilha.";
			link.l1 = "Excelente. Aliás, qual é o nome da ilha?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Talvez um dia a gente construa mais casas e estruturas por aqui... Mas isso fica pra depois. Por enquanto, você vai continuar com a mesma função aqui, só que sob um novo capitão.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Fechado. Só cuide-se, capitão, e não se esqueça de nos abastecer com mantimentos.";
			link.l1 = "Claro, Rodgar. Boa sorte, preciso zarpar para La Vega.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "É difícil dizer, capitão. O falecido Wulfric nunca deixou mais de duas dúzias de pessoas aqui. Agora, somos só três."+sTemp+". Não há muito o que possamos fazer.";
			link.l1 = "Quer dizer que, se mais pessoas morassem aqui, você poderia transformar este lugar em um assentamento de verdade?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "A ilha é pequena, então não dá pra construir uma colônia aqui, mas um assentamento é totalmente possível! Dá pra pescar, caçar pássaros e cabras, colher frutas. A gente consegue se virar, mas não vai ficar rico com isso.\nMas tem uma coisa que eu não entendo direito, capitão. Pra que você quer isso?";
			link.l1 = "Esta é minha casa e minha terra, meu povo. O que eu seria se não cuidasse deles?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "Quero investir dinheiro em um negócio que valha a pena.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "Esta pequena ilha fica no coração desta região. Seria sensato transformá-la em uma base militar completa e secreta.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "Estou preocupado com você, Rodgar, todos vocês já perderam completamente o controle a essa altura.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "Você é bem estranho. Bom, deixa pra lá. Pelo menos vai ter algo pra fazer...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "Você é bem estranho. Bom, deixa pra lá. Pelo menos vai ter algo pra fazer...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "Você é meio estranho. Bom, deixa pra lá. Pelo menos vai ter algo pra fazer...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "Você é meio estranho. Bom, deixa pra lá. Pelo menos vai ter algo pra fazer...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "Antes de tudo, você vai precisar encontrar pessoas muito especiais. Gente que possa ser convencida a se mudar para este lugar isolado e viver e trabalhar aqui por anos, completamente afastada do resto do mundo. É esse tipo de pessoa extraordinária que você deve procurar. E, de preferência, mais de uma. Afinal, você não pode simplesmente ordenar que sua tripulação se estabeleça aqui, pelo menos por enquanto. Os colonos não vão querer abandonar suas casas e empregos estáveis. E, com certeza, não precisamos de vagabundos ou desajustados por aqui.\nAlém disso, a questão do sigilo sobre esta ilha sempre vai existir. Se você contar para alguém, logo haverá o risco de caçadores vindo investigar.";
			link.l1 = "Entendi, alguma sugestão?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "Não, Capitão. Já estou aqui há tempo demais e perdi completamente o contato com a vida civilizada.";
			link.l1 = "Ótimo, isso ajuda!";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "Eu trabalho com madeira, não com gente. E fico muito feliz com isso, ha-ha! Aliás, além das pessoas, você também vai precisar trazer um conjunto de ferramentas de forja e construção de alta qualidade pra cá. Só são feitas na velha Europa, então vão te custar uma boa grana. Pergunte aos donos dos estaleiros, dos maiores.";
			link.l1 = "Está tudo claro. Vamos resumir: se eu quiser transformar esta base em algo maior, preciso trazer mais colonos e ferramentas para cá?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "Isso mesmo!";
			link.l1 = "Vou ver o que posso fazer.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "Sim, Capitão! Conjunto de primeira, estamos prontos para construir uma colônia! Custou caro?";
			link.l1 = "Custou-me uma fortuna, espero mesmo que tenha valido a pena!";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "Alguns anos atrás, eu diria que era muito caro. Mas agora... nem sei mais.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "Você não conseguiu se contentar com o que já tinha, não é? De qualquer forma, prepare-se: seus gastos só vão aumentar. Já resolveu a questão com os colonos?";
			link.l1 = "Não, Rodgar. Ainda não descobri onde encontrá-los. Afinal, não tenho o direito soberano de fundar assentamentos nessas águas.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "Você não conseguiu se contentar com o que já tinha, não é? De qualquer forma, prepare-se para ver seus gastos só aumentarem. Já resolveu a questão com os colonos?";
			link.l1 = "Não, Rodgar. Ainda não descobri onde encontrá-los. Afinal, não tenho o direito soberano de fundar assentamentos nessas águas.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "Nessas águas, Capitão, o caos reina todos os dias. Ouça o que as pessoas dizem, talvez encontre uma oportunidade escondida. Eu cuido das ferramentas por enquanto.";
			link.l1 = "Certo, vou ficar de olho nesse tipo de informação.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "Espanhóis? Só pode estar brincando, Capitão. Achei que você fosse trazer vagabundos de Le Francois, não esses aí...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "Você é da Europa? Hehe, dá pra perceber fácil. Fica tranquilo, logo você se acostuma.";
			link.l1 = "Jimenez, você vai ficar na minha casa por um tempo. Tem um porão lá, espaço de sobra. Rodgar, trouxe as ferramentas e também os colonos. E agora, o que fazemos?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "Até amanhã, Capitão. Conversaremos em um dia, quando esses... colonos estiverem acomodados com seus tesouros.";
			link.l1 = "Certo, continuamos amanhã.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "Capitão, fale com o espanhol. Ele já está totalmente concentrado no trabalho dele.";
			link.l1 = "Entendido, eu cuido disso.";
			link.l1.go = "IslaMona_19";
			link.l2 = "Tem alguma coisa errada?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "Capitão, já faz alguns anos que estou à toa com os rapazes aqui. Agora, essa agitação dos espanhóis está me tirando do sério.";
			link.l1 = "Sem confusões! E eu proíbo você e seus homens até de olharem para as mulheres deles! Pelo menos, por enquanto... Se as coisas esquentarem, pegue um bote e vá... pescar por alguns dias.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "Sim, senhor!";
			link.l1 = "Perfeito. Certo, vou ver o que ele está aprontando.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "Já sei, Capitão. O espanhol quer que a gente explore a ilha? Ficar pulando nas pedras com um mapa feito um bando de idiotas?";
			link.l1 = "Está certo, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "Seiscentos dobrões e eu faço isso.";
			link.l1 = "Você ficou louco? Foi picado por uma aranha daqui ou por uma cobra venenosa? O que vai fazer com um baú de ouro numa ilha deserta? Vai enterrar?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "Vamos lá, Capitão. Um dia vamos deixar este lugar, e quem vai precisar da gente no mundão sem um tostão? Claro, temos um pequeno esconderijo guardado, mas está longe de ser suficiente. O Wulfric nunca acertou as dívidas comigo e com os rapazes pelas últimas aventuras dele.\nUma coisa é ficar deitado na praia por meses e cuidar da sua frota de vez em quando. Mas trabalhar duro em terra firme todo santo dia, feito um maldito bucaneiro — aí já é outra história! Isso é trabalho, e trabalho tem que ser pago. O senhor paga sua tripulação, não é, Capitão?";
			link.l1 = "Parece justo. Vou conseguir os 600 dobrões pra você. Espero que não esteja esperando pagamento adiantado, certo?";
			link.l1.go = "IslaMona_23";
			link.l2 = "Tenho outra proposta. Você trabalha em terra, não raspando cracas de navios no mar. Agora mesmo, estamos precisando muito desse tipo de serviço.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "Capitão, estou pronto para começar agora mesmo, mas meus homens vão se esforçar muito mais quando virem os dobrões em suas mãos. Prometo que não vamos deixar nenhum pedaço desta ilha sem explorar.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "Certo. Aqui está o seu ouro. Só não vá gastar tudo em bebida de uma vez.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "Certo, vou trazer seus dobrões.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ha-ha! Você tem razão nisso, Capitão! Ah, e quase me esqueci. Agora já tem bastante gente morando aqui, e eles precisam de algo para comer. Viu aquelas senhoras? Elas não estão acostumadas a sobreviver e tirar sustento da terra. Não vão ajudar em nada.";
			link.l1 = "Só não me diga que vou ter que encontrar mais bucaneiros pra te ajudar.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "Sim, senhor, Capitão! Estamos prontos para trabalhar em terra! Ah, e mais uma coisa, quase me esqueci. Agora tem bastante gente morando aqui, e eles precisam de algo para comer. Viu aquelas senhoras? Elas não estão acostumadas a sobreviver e tirar sustento da terra. Não vão ajudar em nada.";
			link.l1 = "Não me diga que vou ter que sair por aí procurando bucaneiros pra te ajudar também...";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "Não, por que faríamos isso? Vamos treinar e preparar os mais capazes entre eles para uma nova vida. Mas até esse momento chegar, você vai ter que nos fornecer comida. Umas duas mil provisões de navio já bastam. E uma centena de arrobas de remédios para o futuro. Descarregue tudo isso dos navios no nosso armazém na ilha.";
			link.l1 = "Pode deixar. Quanto tempo você precisa para a missão de reconhecimento?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "Vamos terminar em dois ou três dias, já encontramos algumas coisas interessantes.";
			link.l1 = "Ótimo!";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "Assim que terminarmos, vá direto até aquele espanhol risonho. O maluco precisa tirar conclusões do nosso trabalho.";
			link.l1 = "Vejo que vocês já estão quase amigos. Então, vou visitá-lo daqui a três dias. Bem, vamos ao trabalho. Boa sorte para todos nós!";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "Caramba! Obrigado, Capitão. Agora temos tempo para preparar as moças para essa vida agitada.";
			link.l1 = "Só tome cuidado para não transformá-los em piratas! Obrigado, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "Capitão! Preciso dizer, comecei a me sentir um tanto desconfortável morando aqui.";
			link.l1 = "Por que isso, Rodgar? Sentindo falta do charme da pobreza e da ruína?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "Pode-se dizer que sim. Agora até aqui a civilização está chegando. E pessoas como eu não têm lugar nela.";
			link.l1 = "Compre um jabô e uma bengala. Você vai se encaixar direitinho.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "Melhor, vamos ver seu espanhol e discutir os resultados do reconhecimento. Tenho mais uma ideia maluca...";
			link.l1 = "Acabei de falar com ele! Tudo bem, vamos, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "Você gosta de trabalhar com ele?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "Gente muito instruída e trabalhadora! E o Jimenez é realmente um mestre. Antigamente, dava pra conseguir um bom dinheiro por pessoas assim. E as mulheres deles também são lindas...";
			link.l1 = "Não quero ouvir nada disso, Rodgar! Vamos falar com o nosso mestre";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "Se eles não derem conta do trabalho, vamos vendê-los. Mas as garotas ficam, ha-ha! Vamos falar com o patrão... ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "Sério, Capitão? Eu só estava brincando, vamos embora...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "Eu sabia que você me apoiaria, Capitão! Vamos...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "Ele não está rindo, capitão...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "Isso também, capitão. A gente conversa sobre isso depois...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "O cavalheiro tem razão, Capitão. Nenhum de nós vai se acabar na selva. O negócio pode ser sujo, mas não há outro jeito de transformar este lugar em algo além de um covil de piratas.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "Captain, when you build the factory, the slaves will need protection. My guys will take care of that. One of them even shoots like Thor with lightning. Nothing motivates work like a hunting scope. We already have one gun; now we need a second. Any musket will do.";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "E meus homens vão precisar da mesma quantia em ouro e mais uma dúzia de garrafas de rum de qualidade.";
			link.l1 = "Quanto de madeira você pode fornecer em cada remessa? E por que você precisa de ouro?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "Bem, antes de tudo, a vida sem lazer não faz sentido, e logo até os mais devotos, hehe, católicos vão começar a enlouquecer. E em segundo lugar, se houver uma taverna na ilha, você vai poder deixar parte da tripulação aqui de prontidão. Veja, convencer as pessoas a viver como selvagens de graça em cabanas na praia por um ano inteiro não é nada fácil. Mas se houver um povoado com uma taverna, comida quente, música e diversão por perto... O que mais um marinheiro precisa quando está de folga em terra?";
			link.l1 = "Prostitutas?";
			link.l1.go = "IslaMona_49";
			link.l2 = "Bebidas?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "Você tem razão, mas vamos resolver os problemas um de cada vez. Primeiro, vamos reconstruir sua casa...";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "Ele nem pensou nisso, capitão.";
			link.l1 = "Obrigado, Rodgar. Então agora vou poder atender mais navios nessa baía pequena, certo?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "Saudações, Capitão! Veio conversar sobre o trabalho?";
			link.l1 = "Não, de jeito nenhum. Só senti falta dos seus traços do norte.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "Vamos caminhar? Vou te mostrar sua fábrica.";
			link.l1 = "Mostre o caminho.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "H-hic! Cap, estamos comemorando!";
			link.l1 = "Rodgar! Rodrigo! Ora, droga!";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "O que foi, c-c-capitão? Não gostou da cor das paredes?";
			link.l1 = "Só agora percebi que vocês dois têm o mesmo nome! Ha-ha-ha! Um espanhol e um pirata, com o mesmo nome, construíram uma taverna numa ilha deserta e estão bebendo juntos como se os deuses índios fossem devorar todo mundo e acabar com o mundo ao amanhecer! Ha-ha! Estou com vocês!";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "Ha-ha-ha! É verdade! Saúde!";
			link.l1 = "Saúde!";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "Quer um drink, Capitão?";
			link.l1 = "Está virando dono de taverna, Rodgar?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "Temporariamente! Os espanhóis, em especial, adoram ter um pirata servindo no bar — para eles, é puro exotismo e aventura. Mas, no geral, aqui é um lugar agradável. Se quiser deixar alguém da sua tripulação de reserva nesta vila, é só me avisar — eu cuido disso.";
			link.l1 = "Onde eles vão morar, então?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "Simples - vamos construir algumas cabanas na praia. Assim, eles vão correr da taverna direto para a areia. Só lembrando, esta ilha não comporta mais de trezentas pessoas, então tenha isso em mente para o futuro. De vez em quando vamos pedir para você trazer rum e vinho, então seria ótimo se você, Capitão, pudesse abastecer o armazém com antecedência.";
			link.l1 = "Vou me lembrar disso. Então, compadre. Divirta os espanhóis e aproveite um descanso. Só, por favor, não beba tanto a ponto de incendiar a vila inteira – eu não suportaria ver uma cena dessas!";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "Capitão! Que bom te ver, por Freyja! Você chegou bem na hora!";
			link.l1 = "É, nos metemos em outra bela enrascada. Hola, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "Sem baixas. Os espanhóis sobreviventes chegaram até nós primeiro, avisaram que há possibilidade de encontrarmos mais visitantes, e conseguimos trazer quase todos os mantimentos e equipamentos da área para o assentamento. A situação com os escravos, claro, não saiu muito bem.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "E se eles nos arrastarem para um ataque aberto?";
			link.l1 = "Então vamos sem armas. Como numa parada, marchamos juntos até os portões e depois atacamos por trás. Você segura os portões e dá cobertura. É isso, boa sorte pra nós!";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "Viva, Capitão!";
			link.l1 = "Combinado! Isso foi incrível, até eu fiquei com vontade de me deitar. Gente, o que vocês colocaram aí dentro?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "Carregue duas vezes, Capitão. Assim, um disparo só já desanima eles de continuar lutando!";
			link.l1 = "Você não ficou preocupado que a arma explodisse com um manuseio tão delicado?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "Eu tenho um talismã especial deixado por Wulfric. Uma lembrança da nossa terra natal, a Dinamarca. Vamos todos para a taverna, Capitão? Estamos todos cansados depois de hoje.";
			link.l1 = "Sim, seria ótimo. Vamos jogar cartas – apostamos no seu talismã milagroso.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "Ha-ha, depois de uma apresentação tão divina hoje, Capitão, talvez eu até considere essa opção!";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "Capitão, você ouviu isso? Ainda estou com um zumbido nos ouvidos. De quem é essa voz tão triste?";
			link.l1 = "Isso, Rodgar, é um problema em aberto. Leve-o para a fábrica, coloque-o em correntes e aguarde novas instruções.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "Sim, capitão!";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "Capitão, você veio resolver a situação com o prisioneiro? Já estou cansado de fazer guarda aqui.";
			link.l1 = "Vamos ter que matá-lo. O risco é grande demais, não temos escolha. Caso contrário, é melhor eu nem aparecer nas colônias francesas.";
			link.l1.go = "IslaMona_79";
			link.l2 = "Não posso deixá-lo ir, senão é melhor eu nunca mais aparecer nas colônias francesas. Coloquem-no em correntes e façam-no trabalhar na fábrica. É melhor do que matá-lo.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "Entendido! Vamos resolver isso rápido. Vá em frente, Capitão. Até amanhã.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "Vixe Maria. Você é mesmo um gênio do mal. Eu não queria estar no lugar dos seus inimigos. Bom, primeiro vamos ter que dar umas explicações pra ele. Vá em frente, Capitão. Até amanhã.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "Que carnificina! Pena que não pudemos disparar o canhão, mas eles correram direto pra sua emboscada – foi uma cena e tanto de se ver!";
			link.l1 = "Sim, já derramamos muito sangue nesta terra. Mas, ao que parece, não há outro jeito de construir um lar neste mundo.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "Não se preocupe tanto com isso, Capitão. O próprio destino trouxe eles para Isla Mona. E vou te dizer, o destino pode ser uma bela de uma peste!";
			link.l1 = "O destino, ou a ilha?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "Ambos cumpriram seu papel.";
			link.l1 = "Haha! E as duas são lindas! Muito bem, bravo Viking. Recolha os troféus e retire esses corpos. Enterre-os com dignidade. Afinal, são dos nossos...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "Sim, Capitão. Isso mesmo! Rodrigo falou de um jeito tão bonito que até me fez chorar. Agora entendo por que os padres querem enfiar o traseiro dele numa estaca!";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "Rodrigo, e não é que eu dei de cara com o nosso prelado no boudoir... E olha, é o melhor estabelecimento de Santiago!";
			link.l1 = "O melhor lugar se você também gosta de prelados.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "É, transformei aquele canalha e herege Rodrigo em um verdadeiro pirata, de fato.";
			link.l1 = "Aliás, me esclareça uma coisa, Rodgar. Por que há tão poucos piratas espanhóis?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "Why so few? Ah, you mean pirate captains? Well, there are plenty of them; they just mostly operate under the Casa de Contratación in Seville. It's like military intelligence, but for some reason they call it a trading house...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "Sim, por que não mandar uma mensagem e convidá-los para cá? Bem, todos eles têm patentes, e também são idealistas. Normalmente não roubam os seus, só se a expedição não deu certo, ha-ha! Só aparecem em Puerto Principe e vivem se desentendendo com o Pastor.\nUltimamente, um deles se destacou... Diego de Montoya. Na última vez que saí em campanha com Wulfric, ouvi muitas histórias sobre as aventuras dele. Você, capitão, tem algo em comum com ele. E ao mesmo tempo, são bem diferentes... Enfim, do que eu estava falando mesmo? Vamos pedir mais uma rodada e jogar umas cartas.";
			link.l1 = "Você não tem dinheiro nenhum. Não vai apostar com dobrões, vai?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "Apostamos um peso cada. Vamos jogar até vinte? Hymenes, você entra?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "Vamos jogar, capitão?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "Comece!";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "Eu também vou passar, Rodgar. Com ou sem pesos, gente perde navio desse jeito. E até ilha. Se diverte aí, eu vou dar mais uma olhada por aí.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Passa! Ora, ora, não brinco mais com você! Tenho certeza que você trapaceou, Capitão! E deixar um trapaceiro sair assim, de graça, não seria certo!";
				link.l1 = "Estou ouvindo, Rodgar.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Eu venci, capitão. Mas não posso deixar você sair de mãos abanando assim, haha!";
					link.l1 = "Certo, seu canalha. Isso vai me servir de lição...";
				}
				else
				{
					dialog.text = "Eu venci, Capitão. Mas não posso deixar você sair de mãos abanando assim, haha!";
					link.l1 = "Tá certo, seu canalha. Que isso me sirva de lição...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "Ah, qual é! Você deu a mim e à minha tripulação uma chance de ter uma vida de verdade, longe dos aposentos apertados, da água parada e do risco de levar uma lasca... no crânio. Aqui. Esse amuleto foi trazido pelo Wulfric da distante Dinamarca e depois passado pra mim pra que eu... heh, não precisasse fuçar tanto no porão dele. Não preciso mais disso, mas você – ah, você vai achar bem útil.";
			link.l1 = "Obrigado, Rodgar. Realmente, um item útil. E bonito também...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "Fique com isso, Rodgar. Sem você, este lugar nem existiria. Que isso sirva de lembrança da sua terra natal.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "Fico feliz que tenha gostado, Capitão. Mais uma rodada?";
			link.l1 = "Vocês fiquem aqui tranquilos, eu vou dar mais uma olhada ao redor.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "Como quiser! Então vou brindar à Senhora Sorte, haha! Mais uma rodada?";
			link.l1 = "Vocês fiquem aqui, e eu vou dar mais uma olhada por aí.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "Pois bem, Capitão. Você resolveu as coisas com o espanhol, já comemoramos, e a ressaca já passou um pouco. A vida está boa!";
			link.l1 = "O que você está aprontando, Rodgar?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "Vou caçar como sempre, cuidar da minha... nossa taverna, dar uns chutes nos escravos da plantação. Aposentadoria perfeita.";
			link.l1 = "Você só é cinco anos mais velho do que eu, Rodgar. E você, Rodrigo? Como vão as coisas?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "Com certeza, capitão! Só precisamos de tábuas e lona de vela. Vá até o local de desembarque e mande a tripulação preparar os materiais.";
				link.l1 = "Estou indo. Seja rápido.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Certamente, capitão, mas pelo que vejo, seu navio não precisa de reparos no momento.";
				link.l1 = "Só perguntei...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "É possível, capitão. Mas há algumas limitações: só existem dois lugares nesta ilha adequados para isso. Além disso, você só pode deixar um oficial por navio aqui, mais ninguém. Simplesmente não temos recursos suficientes para manter tripulações aqui. Ainda não. E, por fim, não há espaço para navios de primeira linha.";
			link.l1 = "Entendi. Estou pronto para deixar o navio aqui.";
			link.l1.go = "shipstock";
			link.l2 = "Muito bem, vou prepará-la.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "Capitão, já há três dos seus navios ancorados no cais. Não há mais espaço disponível.";
					link.l1 = "Você tem razão, eu esqueci.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "Capitão, já tem um navio de primeira classe atracado no cais. Não há mais espaço disponível.";
						link.l1 = "Você tem razão, eu esqueci.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "Capitão, dois dos seus navios já estão ancorados no cais. Não há mais espaço disponível.";
					link.l1 = "Você tem razão, eu esqueci.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Capitão, você tem apenas um navio.";
				link.l1 = "Hm... Eu devia beber menos...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "Qual navio você quer deixar aqui?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Espere, mudei de ideia.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Vamos ver...";
			Link.l1 = "Muito bom.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Espere, mudei de ideia.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Vamos ver...";
			Link.l1 = "Muito bom.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Espere, mudei de ideia.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Vamos ver...";
			Link.l1 = "Muito bom.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Espere, mudei de ideia.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Vamos ver...";
			Link.l1 = "Muito bom.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Espere, mudei de ideia.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "Capitão, já mencionei antes que nosso ancoradouro só comporta um navio de primeira linha. Ele é grande demais para o espaço disponível.";
					Link.l1 = "Você tem razão, eu esqueci.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "Capitão, navios de primeira linha são grandes demais para as nossas costas. Já te disse isso.";
					Link.l1 = "Você tem razão, eu esqueci.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0 && !CheckAttributeEqualTo(pchar, "questTemp.IslaMona.Tavern", "complete"))
			{
				dialog.text = "Capitão, leve toda a tripulação dela para sua nau capitânia, exceto um oficial.";
				Link.l1 = "Ah, certo! Vou fazer isso!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "Então, vamos ficar aqui um"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" chamado de '"+chref.Ship.Name+"'. Certo?";
			Link.l1 = "Certo.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Espere, mudei de ideia.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            LeaveShipIslaMona(&NPChar);
			dialog.text = "Muito bem, vamos garantir que ela chegue a um porto seguro.";
			Link.l1 = "Excelente!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Qual navio você vai escolher, capitão?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Espere, mudei de ideia.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Capitão, você não tem espaço na sua esquadra para mais um navio.";
				link.l1 = "Hum. Parece que você está certo.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "Capitão, parece que não há espaço para mais um oficial na sua tripulação.";
				link.l1 = "Pode ser que você tenha razão. Vou passar aqui mais tarde—enquanto isso, fique de olho para que nenhum novo dono coloque as mãos no meu navio.";
				link.l1.go = "exit";
				break;
			}
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Você vai levá-la?";
			link.l1 = "Sim.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Espere, mudei de ideia.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Aqui? Não. Mas o Wulfric construiu um celeiro enorme não muito longe daqui. É uma construção sólida, bem coberta com folhas de palmeira e lona de vela alcatroada. Tem uma tranca e espaço para carga suficiente para encher uma dúzia de navios mercantes\nAgora está vazio, mas eu tenho a chave se quiser dar uma olhada. Vamos?";
			link.l1 = "Com certeza! Aliás, e quanto aos ratos nesta ilha? Eles vão estragar minhas mercadorias no celeiro?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "O Wolf pensou em tudo também: trouxe dois gatos do continente. Só esqueceu de trazer machos, então essas malucas fazem um escândalo toda vez que entram no cio. Mas caçam ratos e camundongos muito bem. Não se preocupe com isso, capitão. Suas mercadorias vão ficar protegidas de pragas e do vento.";
			link.l1 = "Ótimo! Vou fazer bom uso disso. Guarde sua chave com você e me mostre este armazém.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Me siga, capitão.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = "Ora, ora... Uma garota... O que está fazendo aqui?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Oh...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "Senhor! Senhor "+pchar.name+" não me mate, por favor! Eu imploro! Não vou contar nada para o Tyrex! Eu odeio aquele monstro! Eu suplico, por favor!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Ei, moça! Ouviu isso? Você vem comigo, ou esse brutamonte vai te matar.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "Eu vou com você, señor, para onde quer que esteja me levando!";
			link.l1 = "Muito bem, então. Fique de boca fechada, ou eu te mato se começar a gritar ou chamar pelo Tyrex. Qual é o seu nome?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Comporte-se, Mirabelle, e tudo vai acabar bem para você. Fique perto de mim e não faça nenhum barulho.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "Eu juro que não vou, señor.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "Senhor?";
			link.l1 = "Você foi bem, garota, gostei disso. Agora vamos para o meu navio, onde você vai ficar em uma cabine pequena por um tempo. Me desculpe, mas não quero que você corra até Tyrex e conte alguma coisa para ele.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "De jeito nenhum, señor! Eu jamais iria até Tyrex, esse bastardo! Eu odeio ele! Lo odio!!!";
			link.l1 = "Eita! O que ele fez com você?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "Muito... Eu odeio ele, eu odeio ele!";
			link.l1 = "Entendi. Assim que chegarmos, você vai morar numa casa bem elegante. Sozinha. Me mantenha de bom humor e ninguém jamais vai te machucar. Agora vá para o bote... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Já chegamos, senhor?";
			link.l1 = "Sim, querida. Esta é a minha vila e a minha casa. O lugar é meu. Mas sou uma visita rara por aqui — trabalho demais lá fora. Mantenha minha casa limpa enquanto morar nela, ou vou te entregar para o Rodgar e os carpinteiros dele. Pode andar pela ilha à vontade, ela é linda, mas de qualquer jeito não tem como fugir daqui.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "Bem, aqui estamos. Esta é a minha casa. Tudo nesta ilha me pertence. Não venho aqui com frequência – afinal, moro no navio – mas, ainda assim, alguém precisa cuidar da casa. Rodgar, generosamente, concordou em passar esse papel honorário para você. Pode andar por aí o quanto quiser, até mesmo pelas selvas ou pelas praias, mas certifique-se de ter alguém como companhia – ainda há animais selvagens por aqui. De qualquer forma, você não pode sair daqui sem um navio.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "Não tenho para onde fugir, señor "+pchar.name+". Eu não tenho ninguém, e ninguém precisa de mim. A não ser que você me venda para um bordel...";
			link.l1 = "By the hearth, there's a hatch that leads underground. Do not go there; you'll fall into the cave and break your bones, or you won't be able to get back and might die of hunger. And then it would be a pity that I saved you for nothing.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "Não tenho para onde ir, señor "+pchar.name+". Não tenho família nem propósito. Posso acabar voltando para um bordel.";
			link.l1 = "Tem uma escotilha que leva para a caverna, fique longe dela. Lá embaixo é escuro e perigoso.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "Vou ficar longe, señor.";
			link.l1 = "Também tem um quarto no andar de cima. Me siga.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "Pronto. Te mostrei a casa toda. Não é pior do que o lugar do Tyrex onde você morava antes. Espero que goste.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Sim, señor. Você tem uma bela casa. Prometo cuidar bem dela na sua ausência.";
			link.l1 = "Fico feliz que você esteja colaborando comigo. Espero que esteja sendo sincera. Seja honesta comigo ou vai se arrepender se não for. Seja uma boa moça e não me deixe triste, e eu vou ser bom com você. Charlie Prince honra sua palavra!";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "Eu acredito em você, querida. Acho que você vai estar mais segura aqui do que amarrada naquele depósito escuro onde o Tyrex te deixou.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "Obrigado, señor "+pchar.name+". Obrigado por não deixar seu... compañero me matar. Você é tão gentil comigo...";
			link.l1 = "Heh, e você é engraçado... E seu rosto também é bonito, mesmo com essa marca na testa. Espero que o resto também esteja no lugar... Agora mostre ao seu capitão do que é capaz. Vamos relaxar por algumas horas depois do balanço do mar.";
			link.l1.go = "mirabelle_21";
			link.l2 = "Muito bem. É isso, tenho muito trabalho a fazer. E você, vá se acomodando, conheça o Rodgar e o pessoal. Quando eu voltar, conversamos mais.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "Obrigado, señor "+pchar.name+". Obrigado por não deixar seu... companheiro me matar. Você é muito gentil.";
			link.l1 = "Heh, você é uma gracinha engraçada... E ainda por cima tem um rosto bonito, mesmo com a marca. Espero que o resto também esteja no lugar... Agora mostre ao seu capitão do que é capaz.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "Muito bem. É isso, tenho muito trabalho a fazer. E você, vá se acomodando, conheça o Rodgar e o pessoal. Quando eu voltar, conversamos mais.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Senhor "+pchar.name+" você é tão doce... Você é um verdadeiro cavalheiro. Deve ter chegado da Europa há pouco tempo.";
			link.l1 = "Não me venha com bajulação, sua mentirosa, não caio nessa. Heh, você é boa mesmo, Mirabelle! Tyrex tem bom gosto, heh-heh...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "Eu não sou. Você é um cavalheiro. Mas está fingindo ser grosseiro por algum motivo. Mhmm... Gostei muito disso. Vou esperar para te ver de novo...";
			link.l1 = "Ah sim, um cavalheiro... um cavalheiro de fortuna, ha-ha! Muito bem, querida, fique por aqui por enquanto.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Adeus, señor.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", senhor "+pchar.name+"! Fico muito feliz em te ver. Como você está?";
			link.l1 = RandSwear()+""+RandPhraseSimple("Que me partam ao meio, que me levem a alma!","Oh, melhor viver e morrer sob a ousada bandeira negra que eu ergo!")+" Charlie Prince está bem, querida.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Querida, que tal deixar um capitão um pouco mais feliz?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Qualquer coisa por você, señor!";
			link.l1 = RandPhraseSimple("Preparem os ganchos!","Abordem!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mhm... Señor, você é um mágico! Espero que tenha gostado também? Eu dei o meu melhor.";
			link.l1 = "Você mandou muito bem, querida.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "Isso não é verdade, não é verdade! Señor "+pchar.name+" é bom e generoso! Ele só finge ser um pirata malvado! Você é, señor "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", senhor "+pchar.name+"! Que bom te ver. Como você está? Por que esse olhar tão triste?";
			link.l1 = "Olá, Mirabelle. Por que você acha que estou triste?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Bem, eu percebo. Você não está como de costume. Quer que eu anime você? Vamos lá! Colhi umas frutas bem doces na mata, e o peixe que o Rodgar e os rapazes pescaram ontem está assado e ainda quentinho.";
			link.l1 = "Espere. Quero falar com você.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Claro, señor, o que você mandar. Estou todo ouvidos";
			link.l1 = "Me conte, como você caiu nas mãos do Tyrex, e por que tem uma marca de ladrão na sua testa? Não tenha medo, eu nunca vou te machucar. Só quero ouvir a sua história.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ah, señor! My story is brief and dull. I was born in Puerto Rico; my father was a white gentleman, my mother an Indian. I've never seen my pa. When I was a child, I was a servant, and when I grew up, I made the foolish mistake of stealing my master's jewellery. I had never had any of my own, and I wanted some so badly, just to try wearing it for a day. Of course, they found out everything\nThere was a trial, I was whipped, branded, and put in the jail of San Juan. I didn't stay there for too long: one of the officers made a deal with the chief, and I was sold to a brothel in Philipsburg for a handful of golden doubloons\nI spent about a year there. One unfortunate day, we were paid a visit by Tyrex and his wretched friend with glasses.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Sim, sim, o nome dele era senhor Pasquale Lavoisier. Não faço ideia do que viram em mim, mas logo depois da visita deles, Tyrex me comprou da Madame Johanna e me trancou numa casa cheia de baús e mercadorias. Foi a pior época da minha vida, até pior do que os dias na prisão de San Juan. Tyrex me visitava todos os dias, a não ser quando estava no mar, e aí eu podia respirar em paz, mas toda vez que o senhor Lavoisier aparecia eu... eu... Era o pior de tudo. Senhor "+pchar.name+", por favor, será que eu posso não falar sobre isso?\nNão sei quanto tempo fiquei lá. E então você apareceu e me tirou daquela casa horrível. Tive muita sorte de você ter sido tão gentil.";
			link.l1 = "Bondosa? Mirabelle, mas eu fiz exatamente a mesma coisa com você: levei você para uma ilha e te tranquei dentro de uma casa.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "Não, señor, isso não é verdade. Estou presa aqui? Dou uma volta pela ilha todos os dias. Este lugar é maravilhoso e tranquilo. Tenho que fazer muito trabalho doméstico? Nem um pouco, e já me acostumei com isso mesmo. E você não é como Tyrex, nem como o amigo comerciante dele. Sempre fico feliz em te ver, você é tão jovem e bonito. E ainda por cima, um cavalheiro...";
			link.l1 = "Mirabelle, você quer que eu te leve para alguma cidade? Eu posso te dar dinheiro suficiente. Para onde? Escolha qualquer colônia.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Senhor, o senhor quer me enxotar? Por favor, não faça isso, eu lhe suplico!";
			link.l1 = "Bem... Achei que você quisesse voltar à vida normal...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ah, senhor "+pchar.name+", and what is there for me? How will I ever marry, being a marked half-blood? I'll be sold to a brothel again. Please, don't send me away. I like it here; I've never felt so peaceful and safe anywhere else. Rodgar and his boys are good men, we're friends, and they've never hurt me—each of them would risk his life for me. I enjoy spending time with them, it's always fun! Sometimes we make a fire on the beach and I dance samba. Please, señor, I'll do anything for you, just let me stay!";
			link.l1 = "Tudo bem, Mirabelle, fique aqui se gosta tanto desse lugar. Só saiba que você não é prisioneira aqui, pode me pedir para te tirar daqui quando quiser.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "Meu querido senhor, muito obrigada! Muito obrigada! Muito obrigada! Nunca mais vou te pedir algo assim – quero continuar prisioneira desta ilha... e sua prisioneira, hihi... Você é tão bondoso, mas hoje está tão triste! Não canta nem xinga como costuma fazer.";
			link.l1 = "Talvez eu cante, mas chega de palavrões, Mirabelle. E... me desculpe se alguma vez fui grosseiro com você.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Você vai ser severo e rígido como um lorde inglês?.. Ah... señor, quer que eu dance e cante hoje à noite? Só pra você. Agora venha comigo! Não há remédio melhor pra tristeza do que o amor. Senti tanta saudade de você.";
			link.l1 = "Hah! Bem lembrado, minha querida... Vamos.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Ah, senhor "+pchar.name+", você foi tão carinhoso hoje, mhm... Está satisfeito comigo, meu querido capitán?";
			link.l1 = "Foi tudo maravilhoso, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", senhor "+pchar.name+"! Estou tão feliz em te ver! Como você está?";
			link.l1 = ""+LinkRandPhrase("Também estou feliz em te ver, minha garota.","Oi, Mirabelle. Você continua a mesma – alegre e linda, é sempre um prazer te ver.","Oi, linda. Você está deslumbrante!")+"Estou indo muito bem. Espero que você também esteja bem.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, já estou com saudades de você e do seu furão. Vai dar um beijo no seu lobo do mar?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ah, meu doce capitão, eu também senti sua falta! Vamos, estou à flor da pele!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "Senhor Capitão! Capitão "+pchar.name+"! Estou tão feliz! Você vai nos salvar!";
			link.l1 = "Também estou feliz em te ver, Mirabelle. Então, e as perdas?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "Capitão, Capitão, obrigado! Você é o melhor, o mais generoso! Você não só me salvou desses monstros, como também me deu uma nova vida! Para todos nós!";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "Senhor Capitão!";
			link.l1 = "Olá pra você também, beleza. Não está entediada, né?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "Ah, Capitão! Desde que você me resgatou daquela casa terrível, minha vida ganhou cor e alegria.";
			link.l1 = "Você está feliz?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "Claro! E eu gostaria de compartilhar essa felicidade com você... Estarei esperando por você no seu quarto, lá em cima.";
			link.l1 = "Que mulher...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "Senhor Capitão!";
			link.l1 = "Oi pra você também, beleza. Não está entediada, né?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "Ah, Capitão! Desde que você me salvou daquela casa terrível, minha vida ganhou cor e alegria.";
			link.l1 = "Você está feliz?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "Muito! Exceto...";
			link.l1 = "Entendi, você quer me perguntar alguma coisa?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "Sim, Capitão! Eu gostaria de... compartilhar minha felicidade com um certo homem...";
			link.l1 = "Será que ele vai se importar?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "Não, não, Capitão. Eu sei que seríamos felizes juntos, tenho certeza disso. Só... você permitiria?";
			link.l1 = "Você mais do que ninguém merece isso. Mas eu não vou casar vocês dois, então nem pense em pedir!";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "Ha-ha! Meu bom senhor! Obrigado, Señor Capitão. Não sei o que dizem sobre você pelo mundo afora, mas sempre te vi como a pessoa mais gentil e honrada.";
			link.l1 = "Boa sorte pra você, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Malditos ladrões! Tanto faz, nosso mensageiro já está a caminho de Porto Bello. Logo nosso esquadrão vai chegar e...";
			link.l1 = TimeGreeting()+", alteza. É um prazer vê-lo em uma mansão tão bonita. Espero que continue com ela depois que partirmos. Se eu fosse você, não contaria com o esquadrão, e não vamos ficar aqui por mais de três dias. Ousaria dizer que entende que os nobres dons de Porto Bello não vão chegar tão cedo para ajudá-lo. Então, vamos direto ao assunto, certo?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Já quer falar de negócios? Olhe pela janela! Veja o que seus bandidos estão fazendo nas ruas e nas casas!";
			link.l1 = "Oh, Alteza, isso não é nada comparado ao que eles vão fazer se você não colaborar. Espero que entenda com quem está lidando...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "Eu sei do que aquele pirata Charlie Prince é capaz, um verdadeiro canalha! Eu sei quem é o chefe dele! Mais cedo ou mais tarde, vamos acabar com o covil de vocês em Hispaniola! Quanto?";
			link.l1 = "Não desperdice palavras, meu caro Governador. É melhor você me arranjar 250.000 pesos.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "O quê?! Sua insolência não tem limites! Isso é um assalto!";
			link.l1 = "É roubo, claro. O que mais poderia ser? Junte seus melhores, seus mercadores e comerciantes, acumule ouro em um grande baú, porque senão... Eu vou tornar tudo muito pior para você e seu povo.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Maldito pirata! Bastardo! Herege! Vai se foder!";
			link.l1 = "Por causa da sua língua suja, vou aumentar o resgate para 300.000.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "QUEIME NO INFERNO, FILHO DA PUTA!!!";
			link.l1 = "350.000. Você quer continuar?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "Não existe esse dinheiro na cidade!";
			link.l1 = "Você mente. Isso simplesmente não pode ser verdade. Aqui poderíamos juntar pelo menos um milhão, mas receio que não temos tempo suficiente para isso. Portanto, serei bondoso e generoso. Você sabe o valor. Vá e consiga.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "Estou te dizendo de novo, Charlie Prince: esse dinheiro não existe em Cartagena!";
			link.l1 = "Oh... como você pode ser tão lerdo. Cutlass! Vasculhe tudo e traga todo mundo que encontrar até aqui. Procure direito! E nós vamos esperar aqui por enquanto, excelência...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Ei, senhor 'Teimoso'! Ainda não mudou de ideia sobre coletar dinheiro na bela cidade de Cartagena?... O que foi, por que ficou tão sério de repente?! Está bem? Quer que eu traga um pouco de água?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "Se entendi direito, essas duas senhoras são sua esposa e sua filha, estou certo? A terceira moça parece ser uma criada, você não liga muito pra ela, então não vamos fazer nada com ela. Mas essas duas belezas podem chamar a atenção do meu camarada, senhor Cutlass. Ele parece ter gostado delas, senhor. E então? Vai pagar o resgate?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "Eu... Eu vou precisar de um tempo.";
			link.l1 = "Aha! Agora sim, está falando sério! Então quem é o bastardo aqui? Você não ligou nem um pouco pros meus homens aterrorizando seus cidadãos, mas suas duas mulheres são outro assunto, né? Teve coragem de negociar comigo, seu idiota? Vou te mostrar o que acontece quando se mete com Charlie Prince!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Vá e reúna o maldito resgate. 350.000, e nem um peso a menos. Você tem um dia. Vamos ficar aqui bebendo vinho e aproveitando a companhia dessas belas mulheres... Seja rápido, amigo, ou eu e meu amigo aqui, o senhor Cutlass, podemos acabar nos apaixonando por suas belezas, e aí você vai ter que pagar resgate por elas também. Em frente! Marcha!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Pegue seu dinheiro sujo de sangue, Charlie Prince!";
			link.l1 = "Conseguiu juntar o resgate? Excelente! Mas você está uma hora atrasado, meu caro governador. Essa hora extra me fez perceber, junto com o Cutlass, que nossas vidas seriam entediantes demais sem essas belezas, que foram tão gentis e falantes conosco...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "Você... você!";
			link.l1 = "Ah, você está nervoso demais por causa do seu trabalho, meu amigo. Eu estava brincando... Cutlass! Vamos, estamos de saída!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Oh, então este é Charlie Prince, o famoso pirata, o terror do Sul Espanhol!";
			link.l1 = RandSwear()+"Heh, eu não fazia ideia de que era tão popular em Tortuga. Qual é o seu nome, garota bonita?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "Meu nome é Camilla.";
			link.l1 = "Camilla... Eu conheci uma garota com esse nome lá na França. Faz tanto tempo!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(vomitando) ... merda... Me desculpe, princesa, mas o Príncipe está bem bêbado esta noite. Então... hum... por que veio até mim?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "Por vários motivos. Ou talvez por motivo nenhum.";
			link.l1 = "Deus, isso é complicado demais. Você parece um mistério, moça.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Toda moça precisa de um mistério.";
			link.l1 = "Parece que você quer que eu resolva esse mistério. Não é? Sou mestre em desvendar mistérios de damas, juro! Que tal irmos a uma taverna tomar um vinho? Eu te ofereço o melhor que tiver!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "Mmm... Eu gosto de homens decididos. Mas não vou beber vinho lá embaixo no meio de bêbados ordinários. Arrume um quarto pra gente, lá a gente bebe e conversa.";
			link.l1 = RandSwear()+"Você é atraente! Venha comigo!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "Vamos lá... Despeje logo, não faça a moça esperar!";
			link.l1 = "Claro, meu querido!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "Mmm... Só de pensar, aqui estou eu, a sós com Charlie Prince, bebendo um vinho excelente...";
			link.l1 = "Você vai adorar essa aventura comigo, eu prometo! Charlie Prince é gentil e atencioso com as damas que se entregam a ele. Vai se entregar, princesa?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Tee-hee... Claro, querido! Suas promessas parecem tão tentadoras, sabia...";
			link.l1 = "Então, não vamos perder tempo, linda?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Oh! Eu adoro isso! Homens de verdade!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			if(bSFW) PlayStereoSound("sex\sex_sfw.wav");
			else PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "Mmm...";
			link.l1 = "Gostou, minha princesa?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Com certeza! Espero que você também tenha gostado de mim.";
			link.l1 = "Hein! Até minha cabeça parece limpa agora!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Príncipe, tenho um pedido para você. Pode me ajudar?";
			link.l1 = "Eu buscaria uma estrela no céu pra você, ha-ha! Vai lá.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "Eu preciso chegar a La Vega, para ver o Tyrex. Tenho medo dele, mas vocês fazem negócios juntos. Por favor, me leve até ele.";
			link.l1 = "Olha só! E por que uma moça tão doce e delicada ia querer ver o Guardião do Código?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Essa doce e frágil moça gostaria de ganhar algum dinheiro. Meu falecido pai e meus irmãos não me deixaram quase nada. Tyrex pode resolver isso.";
			link.l1 = "Ah é? E como? Procurando uma pista sobre um galeão espanhol? Ha-ha!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "Saqueando caravanas e cidades é coisa para gente dura, igual a você, querida. Tenho outro negócio para o Marcus. Ele compra e vende informações, não é? Eu tenho algo... De jeito nenhum eu conseguiria usar isso, mas ele pode. Vou ficar satisfeita só de receber uma pequena parte disso.";
			link.l1 = "Interessante! Me conte mais.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm... Eu não sei...";
			link.l1 = "Ah, qual é. Pode me considerar a mão direita do Tyrex, já cavei muito pra ele, pode confiar. Se a sua informação valer a pena – eu mesmo compro.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Tá bom. Eu te conto mais, mas nada de detalhes até eu receber o dinheiro. Fechado, querido?";
			link.l1 = "Pode deixar, bela. Charlie Prince não passa a perna nos parceiros... você me entende, ha-ha-ha! Vai lá, estou todo ouvidos.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... Meu pai era capitão de uma escuna mercante. Um dia, de algum jeito, ele soube de um antigo assentamento de mineração espanhol escondido nas selvas do continente. Vinte anos atrás, um terremoto destruiu tudo. Os mineiros abandonaram o lugar e os túneis secretos foram esquecidos. Menos um. Meu pai o encontrou\nEle levou meus irmãos e um guia até lá, e eles acharam o lugar cheio de ouro extraído e fundido anos antes. Muito ouro. Pelo menos um milhão de pesos. Meu pai voltou ao navio para buscar homens para transportar o ouro, mas ficou chocado ao descobrir que o navio tinha sumido. Parece que o imediato dele iniciou um motim e deixaram ele e meus irmãos numa praia deserta\nEles construíram um bote e navegaram pela costa, desesperados atrás de algum lugar habitado, mas... (chora) uma tempestade pegou eles e meus (chora) irmãos morreram. Meu pai sobreviveu, mas não viveu muito depois de voltar pra casa – a morte dos meus irmãos foi matando ele aos poucos, dia após dia. Antes de partir, ele fez um mapa e me entregou\nDisse que quando eu me casasse, meu marido deveria ir lá, pegar o ouro e nós viveríamos como reis. Claro que vamos, mas eu não vou deixar meu homem entrar de novo nessas selvas amaldiçoadas. Nunca mais! Um milhão de pesos, meu pai disse, mas isso não é pra mim. Um prêmio desses, só os melhores e mais duros conseguem – homens como Marcus Tyrex. É por isso que vou me encontrar com ele.";
			link.l1 = "Quanto você quer pelo mapa?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Duzentos dobrões de ouro. Isso não é nada comparado ao prêmio. Tenho certeza de que Tyrex vai aceitar. Ele é tão rico quanto Crasso.";
			link.l1 = "Hein! E se tudo isso for uma armadilha?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "Eu pareço suicida? Enfrentar o Tyrex? Querido, é melhor viver na pobreza do que não viver. Então, você vai me levar até lá? Por favor...";
			link.l1 = "Onde está o mapa? Vai me mostrar?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "Meu padre guarda isso em segurança. Eu te mostro por 200 dobrões.";
			link.l1 = "Muito bem! Eu vou comprar. Estranhos em tavernas às vezes pedem muito mais por porcarias.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "É mesmo? É verdade, meu bem? Estou tão feliz por não ir para La Vega! Para ser sincera, tenho medo do Marcus. E de você também, aliás... mas um pouco menos.";
			link.l1 = "Uma garotinha tão doce não precisa ter medo de mim. Onde devo levar o dinheiro?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Vamos fazer um acordo: me encontre na nossa igreja qualquer dia, das dez da manhã até uma da tarde. Vou me sentir muito mais seguro sob a proteção deste lugar sagrado. Fecharemos nosso acordo lá.";
			link.l1 = "Você ainda tem medo de mim? Ha-ha! Fique tranquila, Camilla, eu não vou te trair. Charlie Prince não se rebaixaria por duzentos dobrões, além disso, quero te ajudar.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Maravilhoso. Muito bem então, lindo, estarei esperando por você... Obrigada pelo tempo maravilhoso que passamos juntos esta noite! Estou tão feliz por termos nos conhecido!";
			link.l1 = "Até logo, bela.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "E então? Trouxe o dinheiro, querido?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "Sim. Aqui está o seu ouro, agora me dê o mapa.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "Estou logo atrás disso.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Obrigada, querido... Aqui, pegue. Juro pela memória do meu pai – este mapa não é falso, ele vai te levar exatamente onde você precisa ir...";
			link.l1 = "Que bom, querido. Que tal comemorarmos nosso acordo como da última vez?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "Eu gostaria, Príncipe, mas estou me preparando para a confissão com meu padre, então preciso me manter longe de qualquer tentação agora. Vamos deixar para a próxima vez.";
			link.l1 = "Ah, você está me provocando, moça. Tudo bem! Sem tempo a perder: estamos prestes a zarpar. Juro que dobro sua recompensa se o mapa do seu pai realmente me levar ao ouro.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "Você é tão generoso, querido. Boa viagem!";
			link.l1 = "Yo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "Seus bastardos mataram meu pai e meus irmãos. Seu ataque a Cartagena trouxe sofrimento para cada família de lá. Espero que agora você esteja com medo, tão assustado quanto nós, cidadãos de Cartagena, estávamos quando seus brutamontes se divertiam nas ruas e nas casas. Você vai queimar no inferno, Charlie Prince.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "Tão poucas coisas neste mundo me dão tanta alegria quanto ver ratos numa caixa se despedaçando!\nSó o rato mais forte e mais asqueroso sobrevive. Depois, tudo o que você precisa fazer é esmagá-lo...";
			link.l1 = "Argh! Quem é você?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "I am Don Enrico. The English scum call me Fox, the Dutch call me Vos, the French call me Renaud. But I prefer my Spanish nickname - Zorro. I punish the wicked who torment and terrorise the common folk, the most vulnerable among the people.\nThis trial today will judge four pirates of Marcus Tyrex: Bold Jeffry, Pelly the Cutlass, Luke the Leprechaun, and Charlie Prince - these bandits are responsible for the massacres in Merida and Cartagena. The last bastard, called Handsome Jean, didn't show up here; he must be the cleverest of your lot.";
			link.l1 = "O quê?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "Você é um canalha, Charlie Prince, mas não é um idiota. Acho que já entendi tudo. É uma armadilha feita por mim para você, com mapas falsos, documentos, palavras e promessas de ouro e prata. Eu atraí todos vocês para essas masmorras, onde acabaram se destruindo, movidos por seus traços mais desprezíveis: inveja, ganância, mesquinharia e falta de escrúpulos. Foi simplesmente a justiça sendo feita!";
			link.l1 = "Camilla... Eu devia ter percebido que havia algo errado com aquela garota!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "Uma moça chamada Camilla levava uma vida tranquila em Cartagena com o pai e os irmãos. Estava prestes a se casar quando você e seus demônios atacaram a cidade. Seus piratas mataram todos que eram próximos dela, então ela jurou fazer o que fosse preciso para vingar a família. Foi um papel difícil de suportar. Ela teve até que se deitar com o desgraçado responsável pela morte dos seus. Nem quero imaginar o que ela sentiu naquele momento\nA pobre garota passou dias na igreja rezando por perdão. Doou os malditos dobrões ensanguentados que você deu a ela para as vítimas que mais sofreram com seu ataque. Agora está em um convento, pobre alma. Você destruiu a vida dela, canalha! Pense nisso! Pense em quantas Camillas, Isabelas, Rositas você violentou e transformou em viúvas! Quantos Juans, Carlos, Pedros vocês, malditos, mataram e torturaram!\nLembre-se de Mérida! Lembre-se de como prometeu ao chefe da cidade não colocar fogo nela, e depois queimou tudo até o chão!";
			link.l1 = "Eu nunca quis fazer isso! Quando saí da residência, o fogo já estava por toda parte. Eu não mandei fazer isso...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "Você é responsável pelos atos dos seus piratas. Homens mortos pesam em sua consciência e logo vão te arrastar para o inferno!";
			link.l1 = "Então vamos lá! Hein? Me enfrenta! É isso que você quer, não é?! Então vamos resolver isso!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "No, Charlie Prince. Don't reach for your weapon, it's pointless... I could kill you easily, but a quick death is not enough for a bastard like you. You will stay in this dungeon forever. The door you used to enter is blocked by a stone outside, and the door behind me will be blocked too; besides, there are sturdy bars protecting it. That's it, there is no way out except for these two doors\nWhat the... I locked all the doors!";
				link.l1 = "O que está acontecendo...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "No, Charlie Prince. Don't reach for your weapon, it's pointless... I could kill you easily, but a quick death is not enough for a bastard like you. You will stay in this dungeon forever. The door you used to enter is blocked by a stone outside, and the door behind me will be blocked as well; besides, there are sturdy bars protecting it. That's it, there is no way out except for these two doors\nThere is water below, so you'll have enough time to reflect on your deeds. All alone here, in the darkness, perhaps you will repent for what you have done before you starve to death or go insane\nOne last thing - the treasure below is a fake. The gold ingots are nothing but coloured lead. The doubloons are real, though, but there are only a few of them, just enough to cover the rocks inside the chests. A fitting end for pirates, eh? You killed each other for a fake treasure, Prince. Farewell now. Pray for your sinful soul, Charlie Prince, if you still remember how...";
		// belamour legendary edition -->
				link.l1 = "Acabei de matar toda a vanguarda do Marcus Tyrex! Acha mesmo que essas grades enferrujadas vão me segurar?! Vou quebrá-las com a sua própria cabeça!";
				link.l1.go = "enrico_5a";
				link.l2 = "Talvez eu merecesse isso. Mas eu não vou desistir, está ouvindo?! Eu vou dar um jeito, sempre dou!";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "Você tem razão, a porta é confiável, mesmo sendo velha. Obrigado por não ter baixado o portão—isso teria me atrasado. Mas não por muito tempo.";
			link.l1 = "Hercule Tonzag, Gaston Careca! Eu devia imaginar que alguém como você ficaria do lado do Príncipe e de toda aquela laia. Que sorte a minha te encontrar aqui também.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "Sortudo, é? Bem, se está com pressa de morrer... Embora eu achasse que não, já que preferiu deixá-lo morrer de fome em vez de encará-lo.";
			link.l1 = "Está me acusando de covardia? Que tolice da sua parte. Como eu disse ao Príncipe, a morte seria um castigo fácil demais pra ele. Ele não está à minha altura.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "E você não é páreo para mim, Don.";
			link.l1 = "Dez anos atrás? Certamente. Agora? Quase nada. Além disso...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "Além disso, o quê? Qual é o motivo dessa pausa dramática? Embora, considerando essa sua máscara de carnaval... Não acha um pouco cedo pra me descartar, não?";
			link.l1 = "Você arrombou a porta, mas força bruta sozinha não vai bastar comigo. Como estão seus reflexos? E a sua visão? Só tem um olho. Eu ainda tenho os dois.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "Bem, por enquanto, pelo menos. Heh-heh.";
			link.l1 = "Por Porto Bello, você merece um destino pior do que o do Príncipe!";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "Ah, então você já ouviu o que eu fiz? Imagino que o seu pessoal vai continuar fofocando sobre isso por um tempo. Então você sabe pelo que eu passei.";
			link.l1 = "Você está velho, Tonzag, e desta vez sua arrogância vai ser sua ruína. E sim, eu não só ouvi falar – Cartagena e Mérida são obra sua. Assim como Porto Bello.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "Eu até poderia levar isso como um elogio, mas não, não fui eu. Embora possa parecer parecido, de longe. Muito amador. Mas, pensando bem, até em Porto Bello já houve... incidentes.";
			link.l1 = "Incidentes?! Naquele dia, uma pessoa morreu... E considerando que foi você quem começou aquele massacre, ainda te culpo por isso, mesmo que não tenha matado todos com as próprias mãos. Eu te culpo por cada 'incidente'.";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "Uma pessoa, você diz... Muitos morreram naquele dia. Seja mais específico.";
			link.l1 = "De verdade, você não tem coração se consegue dizer isso! Mas eu vou responder: aquele que você não deveria ter matado. Meu pai, Don de la Vega. Se ele estivesse vivo, eu nunca teria seguido por esse caminho, e todos vocês ainda estariam vivos.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "Cale a boca, moleque. Minha querida esposa... também morreu lá.";
			link.l1 = "Esperando condolências? Não vai receber. Isso é o castigo de Deus pra você. Parece que você tem coração sim – pequeno e negro. E eu vou encontrá-lo com a minha lâmina.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "Ah, tanto drama por causa do meu coração. Você se engana se acha que já viu coisa pior do que eu.";
			link.l1 = "Você acha que sou apenas um jovem mimado desperdiçando dinheiro? Saiba disso: não gastei um único doblão em jogos ou mulheres! Joguei tudo na luta contra gente como você e dediquei minha vida a isso!";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "E para quê? Não parece estar dando muito certo. As rotas comerciais continuam cheias de piratas. Você está sozinho nessa cruzada. E eles são uma verdadeira legião.";
			link.l1 = "Alguém tem que fazer isso. Pelo menos alguém. E talvez, matando só um capitão pirata, eu consiga salvar algumas vidas.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "Ingênuo. Idealista. E... de certo modo, nobre, eu diria, se não fossem seus métodos. Desonrado, como seus inimigos. No fim, você... não é melhor.";
			link.l1 = "Não venha me dar lição! Honra é para quem segue suas leis. Eu entendo você. Eu penso como você. E eu também castigo.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "Você tem razão. Te ensinar não faz sentido. Então, não vamos nos separar em paz. Mas eu não poderia me importar menos com você, Don Enrico. Você não vale nem o meu tempo.";
			link.l1 = "O que você que...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "Está tudo bem com você, Capitão? Eu avisei para ter cuidado. Devia ter confiado no meu instinto.";
			link.l1 = "Sim, estou bem. Obrigado, Hercule. Só um pouco...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...chocado? Não tenha medo de admitir - é normal para alguém da sua idade e numa situação dessas. Além disso, esse Don é um verdadeiro manipulador.";
			link.l1 = "Aham. Mas ele parecia ter medo de você. Isso me surpreendeu. Mas também me fez voltar ao normal. Aliás, ele ainda está vivo? Parece que sim. Você não devia ficar de costas pra ele.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "Vivo, mas atordoado. Está recobrando os sentidos. Devia ter mirado na cabeça, não no peito – pelo visto, nosso nobre hidalgo está usando um gibão leve, mas resistente, por baixo do casaco. Heh, até o Fleetwood se contentava com um simples colete. Se não fosse isso, já teria uma poça de sangue aqui.";
			link.l1 = "E como você veio parar aqui? No mesmo lugar que ele?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "Agora não é hora pra isso. Logo ele vai estar de pé de novo. Por enquanto, vamos levantar esse portão.";
			link.l1 = "Nós... o quê?? Tudo bem, talvez você seja o Hércules, mas...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "Os homens do meu tempo eram forjados na dureza. Essas dobradiças têm pinos curtos. Vamos lá, me dá uma mão, Capitão – posso até ser um Hércules, mas já estou ficando velho.";
			link.l1 = "Certo, no três! E levanta!";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "Acha que destruiu todos os meus planos e saiu vitorioso? Isso foi inesperado, claro, mas eu ainda tenho muita carta na manga!";
			link.l1 = "Gosto desse couraço leve por baixo da sua roupa. Por que esse e não um completo por cima? Só pra exibir o casaco?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "Não sou nenhuma donzela, Príncipe. Minhas razões são puramente práticas – uma couraça completa limita demais meus movimentos. Cada um tem seu jeito de fazer as coisas.";
			link.l1 = "E aqui estou eu, um francês, já acostumado a usar couraças, diferente de um espanhol. Que ironia. Então, e agora? Você não conseguiu nos pegar. Se preparou para tudo... Um duelo fazia parte dos seus planos? Ou a lâmina – e até a couraça – servem para tudo, menos para uma luta de verdade?";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "Está tentando me chamar de covarde também? Como eu disse, você merece sofrer por muito tempo, não morrer num duelo. Qual seria o sentido, se suas almas não terão tempo de suportar e compreender todos os seus pecados aqui na Terra?";
			link.l1 = "O caminho para o inferno está cheio de boas intenções, como dizem... E atormentar suas vítimas não mancharia a sua própria alma?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "Jamais. Nunca mesmo. Pois continuo fiel a mim mesmo e aos meus princípios.";
			link.l1 = "Aha, não como nós. Você já falou tanto sobre como somos canalhas sem um pingo de honra, então... por que não corresponder às suas expectativas? Vamos cuidar de você nós mesmos. Juntos.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "Tenho uma proposta para você, Don Enrico. Eu o desafio para um duelo, aqui e agora. De um nobre para outro.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "Hm-m.   Caso contrário, você não teria a menor chance. Tonzag vai ser complicado, claro... Então vou cuidar de você primeiro.";
			link.l1 = "Como se ele fosse deixar você fazer isso.";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "Você? Nobre? Talvez seja um “príncipe”, mas duvido que tenha uma gota de sangue nobre em você.";
			link.l1 = "Você revelou seu verdadeiro nome para mim. Eu vou revelar o meu. Sou Charles de Maure. E já ofendemos a honra um do outro o bastante para que cada um de nós tenha o direito de exigir satisfação. Defenda-se, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "Mas não se arrependa da sua decisão depois.";
			link.l1 = "Já me arrependi de muitas decisões na vida, mas desta eu não vou me arrepender. Em guarda!";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "Está tudo bem com você, Capitão? Nosso nobre hidalgo não estava só de couraça – ele também envenenou a lâmina. Aqui, pegue isto. Sempre carrego algumas dessas comigo quando ando pela selva – nunca se sabe quando uma cobra pode morder ou um índio pode lançar um dardo envenenado.";
			link.l1 = "Obrigada, Hercule. Estou bem. Sua chegada na hora certa me ajudou a me recompor.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "Não foi nada. Vamos, eu vou te tirar daqui – ele disse que bloqueou a entrada com pedras. Eu encontrei outra passagem, um atalho.";
			link.l1 = "Me conte, Hercule... o que exatamente aconteceu em Porto Bello? E quando?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "Hoje não estou com vontade de falar sobre isso. Mas talvez um dia, com uma taça de vinho ou algo mais forte. Por agora, vamos sair daqui – o garoto tinha razão, estou mesmo ficando velho. Quero descansar no navio.";
			link.l1 = "Então mostre o caminho.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Me diga, irmão – como você se tornou uma aberração dessas? Quando eu disse para conhecer os piratas, não quis dizer incendiar cidades, matar civis inocentes e torturar mulheres. Até mesmo uma guerra pode ser travada com honra e dignidade\nVocê é uma vergonha para nossa família. Ainda bem que nosso pai não está aqui: ele teria morrido de vergonha ao saber que o filho virou pirata e bandido!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Irmão! Irmão!\nVocê consegue me ouvir?\nHá uma passagem atrás de uma das duas portas. A porta pode ser aberta. A chave está perto de você!\nProcure-a na escada. Na escada!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha, olá, meu bravo canalha! Por que essa cara triste? O mar, o ouro, o rum e as mulheres – o que mais te falta? Lembra do nosso primeiro encontro? Eu te disse naquela época – preciso de homens que não temam o cheiro da pólvora nem fazer o sangue correr como rios. Você superou todas as minhas expectativas! Virou um pirata de verdade, Charlie Prince! Ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "Um verdadeiro pirata sanguinário! Ah-ah-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "Quem é você? O que está fazendo aqui? Responda rápido!";
			link.l1 = "Eu sou de Fadey, vim buscar um lote de ossos negros. Ele deveria ter avisado você.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "Hah! Don't worry about appearances, friend. We recognised you; the Muscovite gave a very detailed description. He also asked that you not take offence at the price. So, taking into account the advance payment, you owe 10,000 silver. Or, if you pay in gold, then only 50 doubloons. Well, what have you decided? Don't drag it out!";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "Eu vou pagar 50 doblões. É mais lucrativo.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "Eu vou pagar 10.000 pesos.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "Desculpe, mas não posso comprar escravos agora.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "Ótimo. Avise seus homens para pegar a mercadoria.";
			link.l1 = "Com certeza.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "Excelente. Dê o sinal para seus homens pegarem a mercadoria.";
			link.l1 = "Com certeza.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "Bem, como quiser. Sempre vai ter alguém querendo esse produto. Até mais, amigo.";
			link.l1 = "Adeus.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "Saudações, Capitão. Você é Charlie Prince, se não me engano? Não se preocupe, minhas paredes não têm ouvidos. Para ser sincero, não me importa qual é o seu nome. O que importa é que você veio recomendado, e isso significa que podemos fazer negócios.";
			link.l1 = "Saudações para você também, Gaspard ‘Dente de Ouro’. Mas, para falar a verdade, pouco me importa como você se chama. Ouvi dizer que talvez esteja interessado em comprar algumas bugigangas?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		// ---> andre39966, Фриплейный Гаспарито
		case "GasparGold_meeting_sandbox":
			dialog.text = "Saudações. Meu nome é Gaspar Parmentier. Em que posso ajudá-lo?";
			link.l1 = "E aí, Gaspar. Sou o capitão " + GetFullName(pchar) + ". Vim da taberna local. Ouvi dizer que você compra bugigangas?";
			link.l1.go = "GasparGold_meeting_01";
			link.l2 = "Olá, Dente de Ouro. Ouvi dizer que você compra tudo o que brilha? Por todos os trovões, nós vamos nos dar bem.";
			link.l2.go = "GasparGold_meeting_wrong";
		break;

		case "GasparGold_meeting_wrong":
			dialog.text = "Parece que o senhor está me confundindo com outra pessoa. Por favor, saia deste local antes que eu chame a guarda.";
			link.l1 = "Argh... Tá bom...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gaspar_sandbox_repeat";
		break;

		case "Gaspar_sandbox_repeat":
			dialog.text = RandPhraseSimple("Acho que pedi para você sair deste local.", "Não tenho tempo para conversas vazias. Por favor, me deixe em paz.", "Estou impressionado com sua falta de tato. Vai continuar me incomodando?");
			link.l1 = "Calma, parceiro. Vim da taberna.";
			link.l1.go = "Gaspar_Alternative";
			link.l2 = "Pare de me enrolar! Eu sei que você compra joias!";
			link.l2.go = "Gaspar_Angry";
		break;

		case "Gaspar_Angry":
			dialog.text = "Já disse que não estou envolvido com nada disso. Saia antes que eu mande te expulsar.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gaspar_sandbox_repeat";
		break;

		case "Gaspar_Alternative":
			dialog.text = "Isso muda tudo, capitão. Você está no lugar certo. Então, quer vender algumas joias?";
			link.l1 = "Bem, quanto a 'minhas'... você se precipitou. He-he.";
			link.l1.go = "GasparGold_01";
			NextDiag.TempNode = "GasparGold";
		break;
		// <--- andre39966, Фриплейный Гаспарито
		
		case "GasparGold_meeting_01":
            dialog.text = "Está certo. Ninguém vai te oferecer um preço melhor do que eu. Bem, talvez os agiotas, mas eles não compram muita coisa. Estou pronto para comprar tudo o que você quiser vender. Nem precisa me trazer os objetos de valor pessoalmente: tenho uma porta dos fundos que leva a um cais isolado. Fique à vontade para me vender todas as bugigangas que você guardou nos baús do seu navio.";
			link.l1 = "Que ótimo! Fico feliz em conhecer você.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "Isso é assunto meu. Prefiro que você não se meta nisso. Só posso dizer que está tudo sob controle, então pode negociar comigo sem preocupação. O resto não é da sua conta.";
			link.l1 = "Bem, o que importa mesmo é não correr riscos! Tem mais uma coisa que eu queria perguntar...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "Como posso ajudar? Quer se livrar de algumas pérolas ou pedras preciosas? Talvez ouro, prata, joias? Eu compro tudo.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "Me diz, como é ser um comprador de mercadorias roubadas? Você não tem medo das autoridades?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "Tenho algo aqui... Quero trocar isso por um bom dinheiro.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "Então, vamos fazer a troca. Dublões ou pesos?";
			link.l1 = "Vamos de pesos – não precisa de dobrões. Dinheiro comum é aceito em todo lugar.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "Acertou — eu preciso mesmo é de dobrões. Então só vou vender por eles.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "Eu não tenho nada à venda no momento. Só queria ter certeza de que você está pronto para comprar itens valiosos quando eu tiver. Até a próxima!";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "Você ainda está recorrendo à intimidação, capitão? Eu consegui ouvir suas ameaças lá de fora.";
			link.l1 = "Eles não me deixaram escolha. Ofereci presentes à esposa desse Tagofa para conseguir a ajuda dele. Ela nem quis me ouvir. Agora que o chefe tente conversar com eles. E se ele não conseguir fazer esses teimosos voltarem à razão, eu mesmo arranco o coração dele do peito com as minhas próprias mãos. E, aliás, quem é Yahahu?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "Você não devia ter piorado as relações com os índios. Nós, piratas, só temos nossas espadas e navios como aliados. Mas já que essa é a sua decisão, que seja. E Yahahu é um demônio maligno. Não sei mais nada sobre ele.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "Perder tempo tentando convencer, Leprechaun, não é sensato. Ou prefere abrir mão do rico saque para manter boas relações com os índios?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "Eu preferiria ficar com os dois.";
			link.l1 = "Não vai dar para ficar em cima do muro dessa vez. Chega de discussões, tudo já foi feito. Amanhã o chefe vai nos informar da decisão de Tagofa, e espero que ele não me decepcione. Caso contrário... vou ter que tomar medidas extremas. O que eu gostaria de evitar, claro.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "Então, como estão as coisas? Vamos ter um guia?";
			link.l1 = "Não, Jean, não vamos. O chefe e toda a tribo temem os Kapongs como o diabo teme o incenso. Parece que teremos que abandonar nosso plano.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "Terrax não vai gostar nada desse rumo dos acontecimentos.";
			link.l1 = "Você acha que estou feliz por as coisas terem acabado assim? Os covardes Lokono não querem se meter com os Kapongs. Eles não se deixam levar nem por conversa, nem por recompensa.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "Então vamos ter que usar ameaças. Diga que você vai queimar a maldita vila deles até o chão e torturar qualquer sobrevivente até que alguém aceite nos guiar.";
			link.l1 = "Jean, você ficou maluco de vez? Eu não vou queimar as casas de pessoas inocentes. E muito menos torturá-las.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "Charles Prince é um verdadeiro benfeitor. Nunca esperei tamanha demonstração de carinho de você.";
			link.l1 = "Isso não é ternura, Bonito. Muito bem, vamos torturar um índio até quase a morte. Por vingança, ele vai nos levar direto para as mãos dos Kapongs e depois sumir por trilhas que só ele conhece. Não vou arriscar a vida do meu povo desse jeito.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "Nesse caso, eu e Leprechaun estamos indo embora. Aqui estão cinquenta mil em prata por me libertar das plantações de Maracaibo. Eu estava guardando para comprar um novo navio. E um conselho: fique longe dos olhos do Marcus por um tempo. Adeus, Charles Prince.";
			link.l1 = "Adeus, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "Todo mundo da região vai correr pra cá agora! Tem certeza de que explodir aquelas árvores foi uma boa ideia, Capitão?";
			link.l1 = "Droga! Talvez tivesse sido melhor se todo mundo tivesse trabalhado com machados... Mas agora já é tarde pra isso.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "É verdade. Vamos ter que lidar com o que temos. Prepare-se.";
			link.l1 = "Você também, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "Eles ainda estão vindo pra cá. Então, vamos lidar com esses também?";
			link.l1 = "E se eles nunca acabarem? Não viemos aqui pra esse tipo de encrenca.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "Bem, tudo chega ao fim... Mas você tem razão. Vamos recuar. E rápido.";
			link.l1 = "Vamos depressa!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "Tão implacáveis, eles nos alcançaram. Tem um caminho aqui, vamos entrar? Vai ser mais fácil segurar a linha.";
			link.l1 = "Espere, Hercule. Você está ouvindo isso? Tem alguém lá dentro. Você e os rapazes cuidem das coisas aqui. Eu vou entrar antes que peguem o tesouro – duvido que alguém tenha entrado ali por acaso.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "Certo. Mas tome cuidado, tenho um mau pressentimento sobre isso.";
			link.l1 = "Você também! Eu vou pra lá.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "Quer dizer alguma coisa, Capitão? Você ficou pensativo o caminho todo até o navio.";
			link.l1 = "É isso mesmo. Tenho pensado no que andei fazendo ultimamente. Sobre Terrax e... aonde isso me levou. Cheguei mais perto de salvar meu irmão? Ou de voltar pra casa?..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "Hm-m. Boas perguntas. E quais são as suas respostas?";
			link.l1 = "Só mais uma pergunta. Se antes não fazia sentido, será que agora vai fazer? Terrax não vai me ajudar. Nem com meu irmão, nem com Tortuga.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "Provavelmente não. Ele não tem utilidade para isso. Surpreende que só agora você percebeu. Mas qual é a sua próxima pergunta?";
			link.l1 = "Por que diabos eu estava correndo atrás do Terrax como um cachorrinho, resolvendo todos os problemas dele esse tempo todo?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "Agora, essa sim é uma boa pergunta. Uma de verdade. Tem uma resposta pra ela dessa vez?";
			link.l1 = "Mais como uma decisão. Hoje eu tive sorte. Mas será que vou ter sorte de novo? É importante saber a hora de parar. E... se respeitar. Já chega pra mim.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "Decidiu terminar sua parceria com Terrax?";
			link.l1 = "Sim. Tenho coisas mais importantes para fazer. Família, amigos. Com eles, vou alcançar meus objetivos. E não desse jeito. E mesmo que eu consiga... não será com o Marcus. Serei meu próprio mestre. Tomarei minhas próprias decisões.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "O homem que um dia segui está falando de novo. Não se envolva com as pessoas erradas outra vez. Não desperdice o potencial que um dia me chamou a atenção.";
			link.l1 = "Entendi, Hercule. E obrigado de novo. Desta vez, por me ajudar a realmente perceber isso. Não sou mais o capanga do Príncipe. Sou Charles de Maure, um nobre orgulhoso. Vamos embarcar no navio – nós dois estamos cansados.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "Isso foi uma baita explosão, senhor – knippel direto na minha popa! Soou exatamente como uma salva do Valkyrie. Mas receio que aqueles caras ali também perceberam...";
			link.l1 = "Se perceberam, o problema é deles. Ninguém chamou eles pra cá. Pronto pra dar uma lição neles, Charlie?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "Sempre pronto, senhor!";
			link.l1 = "Excelente. Vamos começar.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "Receio que vamos receber mais companhia, Capitão. Quais são suas ordens?";
			link.l1 = "Vamos entrar mais fundo na selva e nos esconder – não tem como enfrentar todos eles, e nem é pra isso que estamos aqui.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Sim, senhor.";
			link.l1 = "Então vamos embora!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "Eles nos encontraram, Capitão! Mas podemos nos abrigar aqui – parece que esse caminho leva a algum lugar, embora eu ache que já tenha alguém lá.";
			link.l1 = "Não vamos nos esconder! Parece que alguém mais já ficou sabendo do tesouro. O plano é o seguinte: eu vou ver o que está acontecendo antes que eles levem tudo, e você segura eles aqui com os rapazes!";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Sim, senhor.";
			link.l1 = "Excelente. Estou descendo agora! Confio que você vai cuidar das coisas aqui.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "Khe-khe... Você está... bem, senhor?";
			link.l1 = "Charlie! Você escolheu o momento perfeito pra se preocupar comigo. Guarda o fôlego. Tá aguentando? Eu devia ter te deixado no navio e trazido mais homens no lugar...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "Ah, só um arranhão, senhor. Estou um pouco cansado. Nunca lutei assim, nem nos meus tempos de jovem! Mas dei neles uma surra tão grande que vão ouvir disparo de canhão pela eternidade!";
			link.l1 = "Marinha Real, das antigas! Pelo visto, você lutou como um leão, Charlie. Mas ainda assim, mal consegue ficar de pé. Não disfarça – quão grave é o ferimento?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "Não é nada grave, Capitão, só exaustão. A entrada atrás de você desabou quase imediatamente, e nós ficamos lutando contra aqueles homens por um bom tempo. No fim, fiquei sozinho, ferido. Então vim até aqui para abrir caminho e cuidar um pouco dos meus ferimentos.";
			link.l1 = "Entendo. Bem, você fez a sua parte hoje. Quanto a mim... eu falhei. Todos nós fomos enganados e colocados uns contra os outros para divertir alguém — nem sequer havia tesouro algum. E eu não fui o único tolo ali.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "Você falhou?.. Mas está vivo, senhor. O que aconteceu? Conseguiu escapar?";
			link.l1 = "Não, mas ainda assim precisei correr um pouco. Desculpe, velho amigo, mas o que aconteceu lá dentro, não vou contar a ninguém – nem mesmo aos meus amigos mais próximos. Porém, tirei as conclusões necessárias.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "Que tipo de conclusões, senhor? Nem sempre entendo seu raciocínio. Minha filosofia é simples – uma boa colubrina e bala de corrente no mastro.";
			link.l1 = "Me diga, você já matou espanhóis antes, assim como eu fiz recentemente. Na época em que servia na Marinha Real. E depois, com o Fleetwood.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "Eu fiz. Espanhóis, holandeses—e muitos outros também. Como Dick me disse uma vez, nosso serviço é perigoso e exigente. Mas por que está perguntando? Qual é o seu ponto?";
			link.l1 = "Eu vou explicar. Mas antes, outra pergunta. Você já duvidou do que estava fazendo e do porquê estava fazendo isso, Charlie?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "Hm-m. Eu dizia pra mim mesmo que estava agindo pelo bem da Coroa. Se preocupar com ordens é um trabalho ingrato – no fim das contas, você tem que obedecer mesmo assim.";
			link.l1 = "A Coroa... Bem, você tinha seus motivos. Eu nem isso tinha – Michel mandou eu me aproximar do Terrax. Mas valeu todos os sacrifícios? Isso ajudou a mim ou a ele? Sim, sim, a gente não gosta dos dons... mas no fim, somos todos humanos.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "Acho que estou começando a entender onde o senhor quer chegar.";
			link.l1 = "Ótimo. Me diga, quando Fleetwood foi embora, você ficou feliz por não precisar mais atacar mercadores holandeses? Alguns deles eram pessoas honestas.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "Eu nunca pensei nisso, Capitão. Mas vou dizer uma coisa – sempre gostei de servir ao seu lado, senhor. Que eu seja amaldiçoado com uma corrente no pescoço se eu estiver mentindo!";
			link.l1 = "Ha-ha-ha, tudo bem. Mas me diz uma coisa – quem você acha que se deu pior? Você, que só seguia ordens? Ou eu, que não fui forçado a fazer o que fiz?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "Eu não sei, senhor...";
			link.l1 = "Nem eu. Mas isso não importa. O que importa é que não quero mais nada com Terrax. Chega. Charlie Prince acabou. Agora só Charles de Maure.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "Mas isso não fazia parte do seu plano para salvar seu irmão?";
			link.l1 = "Foi sim. Mas no fim das contas, não me ajudou em nada. Então, se algum dia eu tiver que fazer algo assim de novo – vai ser só decisão minha. E só se isso realmente me aproximar do meu objetivo.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "Espero que você saiba o que está fazendo, Capitão. E que não acabe como Terrax. Ou na forca.";
			link.l1 = "Também espero que sim. Mas do que tenho certeza é que, de agora em diante, meus objetivos e interesses virão em primeiro lugar. Agora, vamos cuidar dos seus ferimentos.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "Sua explosão chamou atenção, Lorde Capitão. Um grupo inimigo parece estar se aproximando de nós.";
			link.l1 = "Maldição! ...Você acha que tinha um jeito melhor de lidar com aquelas árvores? E o que você teria feito?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "Não sei. Mas sei o que fazer agora – lidar com essas pessoas.";
			link.l1 = "Bom, justo. Acho que é exatamente isso que vamos fazer.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "Novas pessoas chegaram, Lorde Capitão.";
			link.l1 = "Sim, eu percebi, obrigado, Longway. Mas não temos tempo pra esses aí, então vamos recuar pra dentro da selva – talvez a gente consiga despistá-los.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "Hum, nós poderíamos dar conta deles, claro, mas como você disse.";
			link.l1 = "Não precisamos dessa briga, então vamos embora.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = " Eles não vão desistir e vão acabar nos pegando, Capitão! Eu te disse, era melhor termos matado eles antes. Quer que a gente prepare uma emboscada naquela caverna? Mas parece que já tem alguém lá.";
			link.l1 = "Melhor armar uma emboscada aqui com os rapazes! O que eu não vou perder é esse tesouro. Parece que mais alguém ficou sabendo do esconderijo... Então vou dar uma olhada eu mesmo.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "Seja cauteloso, Lorde Capitão. Lembre-se, até mesmo um grande dragão já morreu em cima de uma montanha de ouro.";
			link.l1 = "Vou me lembrar disso, Longway. Vamos todos tentar não morrer hoje.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "Senhor Capitão, parece que você conseguiu escapar de lá.";
			link.l1 = "Surpreso, Longway? Tenho que admitir, eu também estou um pouco surpreso. Parece que só você conseguiu sair vivo. Mas como conseguiu isso?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "Um bando de gatos vira-latas não pode derrotar um tigre. Um ninho de cobras não derruba um dragão. Entre os brancos, poucos são adversários à minha altura.";
			link.l1 = "Mas lembre-se, Longway, uma matilha de cães pode despedaçar um leão.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "Agora o Lorde Capitão vem compartilhar sua sabedoria com Longway? Pena que não ouviu meu conselho antes.";
			link.l1 = "Sobre o dragão na montanha de ouro? É verdade, quase me tornei um – na verdade, quase morri. Mas não foi numa montanha de ouro – não havia nada disso. O que encontrei foi outra coisa, igualmente importante.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "Da próxima vez, 'quase' pode não ser suficiente. O que você encontrou, Lorde Capitão?";
			link.l1 = "Sim, agora eu entendo. O que encontrei foi... sabedoria. Experiência. Compreensão. Uma decisão. Diga-me, Longway, o que temos feito ultimamente?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "Somos piratas. Trabalhamos para o seu novo mestre, Lorde Terrax. Contrabandeamos, saqueamos vilarejos, matamos, salvamos e ajudamos o povo dele.";
			link.l1 = "Ele não é meu dono, sabia. Mas droga, você descreveu tudo tão bem! Esqueci meu orgulho, minha dignidade, e fiquei seguindo ele feito um cachorrinho.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "Longway entende você, Lorde Capitão. Eu também trabalhei para van Merden e Rodenburg, esquecendo honra, orgulho e respeito por causa de um objetivo muito desejado.";
			link.l1 = "Me diga, você se condena por isso? Você se odeia?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "Condenar? Às vezes. Odiar? Não. Eu sei e lembro quem sou. Eu lembro do meu objetivo, minha estrela-guia. Nada é mais importante na vida. E você, tem um objetivo?";
			link.l1 = "Não sou uma estrela-guia como você, mas ainda assim tinha um objetivo importante, sim – salvar meu irmão. Mas me desviei desse objetivo. E isso é algo que não posso me permitir repetir.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "Deixe-me compartilhar mais um pouco da sabedoria do Império Celestial com você. Não existem pessoas totalmente boas ou más. Cada um carrega dentro de si tanto o Yin – escuridão e ignorância – quanto o Yang – luz e sabedoria. O equilíbrio entre eles muda em cada pessoa.";
			link.l1 = "Então, meu Yang é Charles de Maure. E meu Yin é Charlie Prince. Mas talvez até mesmo Charles de Maure precise tomar decisões sombrias e difíceis algum dia.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "É assim que é a vida, Senhor Capitão. Todo mundo acaba tomando decisões tanto sombrias quanto luminosas.";
			link.l1 = "Mas a máscara do Príncipe quase se fundiu a mim. Mas vou me livrar dela. Charles de Mort é um nobre, não um criado. A partir de agora, será assim. Recupero meu orgulho e dignidade. De agora em diante, sou meu próprio senhor.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Longway aprova sua decisão, Lorde Capitão.";
			link.l1 = "Obrigado, Longway. Aliás, você já se arrependeu de não ser um capitão livre? Servindo a mim, como você diz, 'seu mestre'?";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "Hm-m. Longway sente falta de comandar seu próprio navio. Mas eu reconheço você. Por me tratar com respeito e sabedoria, diferente do típico bárbaro branco. Talvez eu quisesse uma vida diferente. Mas não me arrependo de ter ajudado você.";
			link.l1 = "Fico feliz em ouvir isso, Longway. Agora... vamos sair daqui e deixar o caminho do Yin para trás. E trazer mais Yang para as nossas vidas. Acertei?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "Sim, está certo. Espero que siga um caminho muito melhor daqui pra frente.";
			link.l1 = "Dao?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "O Caminho, Senhor Capitão. Ou a Essência. Mas no nosso caso – o Caminho.";
			link.l1 = "Seja qual for o caminho que meu futuro reservar, não vou mais me desviar do que realmente importa. Vamos sair daqui, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "Capitão Charles, muita gente está vindo para cá. Seu sinal de fumaça os atraiu. E está claro que não são nossos amigos.";
			link.l1 = "Ah, se fosse só um 'sinal de fumaça', como você disse – ecoou pela selva inteira. Não temos escolha – vamos nos defender. Com certeza não queremos ser surpreendidos por uma patrulha inteira pelas costas.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "Sim, Capitão Charles. Ataque primeiro!";
			link.l1 = "Ataquem! Não economizem nas balas!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "Vem mais gente! Ainda mais pessoas.";
			link.l1 = "Vamos recuar para a selva, Tichingitu! Vamos nos esconder e esperar passar. Vim aqui atrás de tesouro, não de briga!";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "Se for preciso, podemos preparar uma emboscada na selva.";
			link.l1 = "É verdade. Agora vamos – rápido, mas em silêncio.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "Capitão Charles, olha! Tem uma passagem ali na frente. E eu consigo ouvir passos e vozes vindo de lá.";
			link.l1 = "Alguém mais descobriu sobre o tesouro? Droga! Você também está ouvindo esse barulho atrás da gente? Parece que nos alcançaram. Tichingitu! Vou ver o que tem pela frente. Segure eles com os rapazes!";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "Vamos tentar! Vai você!";
			link.l1 = "Estou contando com você!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "Capitão Charles! Você sobreviveu! Tichingitu vai ficar feliz com isso.";
			link.l1 = "Obrigado, meu amigo. Também estou feliz. Fico aliviado por ter sobrevivido, e por você estar bem. Parece que só restou você de todo o grupo. Eram muitos? Você realmente conseguiu segurá-los muito bem.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "Muitos. Mas o meu é um dos melhores guerreiros da nossa aldeia Maskog. O que aconteceu com você lá? Achou o tesouro que procurava?";
			link.l1 = "Não, Tichingitu. Fomos enganados – não havia tesouro nenhum. Me diga, o que você acha do que temos feito ultimamente?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "O que temos feito, Capitão Charles? Navegar. Derrotar seus inimigos.";
			link.l1 = "Parece que você não me entende. Me diga então, você está triste por ter sido exilado da sua tribo? Quer voltar, sente falta dos seus irmãos?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "Claro, sinto falta dos meus amigos e da minha família. Mas voltar? Meu lar não existe mais sem... ela. Além disso, tem aquele coiote maldito, o xamã!";
			link.l1 = "Desculpe, não era minha intenção tocar nesse assunto. Sabe, recentemente eu entrei para uma tribo, por assim dizer. Uma tribo de capitães como eu. Mas no fim, percebi que era só um bando de chacais que se achavam lobos do mar...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "E o que aconteceu? O que fazemos agora?";
			link.l1 = "Boa pergunta. Eu quase virei um chacal no meio daqueles chacais. Então, pra mim já basta. Meus amigos e minha tripulação – essa é a minha 'tribo'.";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "Tichingitu fica feliz que você encontrou sua tribo, Capitão Charles.";
			link.l1 = "Obrigado, meu amigo. Eu precisava dizer isso. Você e eu somos nossos próprios líderes e nossa própria tribo. Agora é hora de voltar ao que realmente importa.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "Alguém está vindo! E, pelo barulho, não parece que veio se juntar a nós para comemorar o Dia de Ação de Graças.";
			link.l1 = "Malditas raízes! Certo, vamos ter que lidar com esses canalhas agora – melhor agora do que quando estivermos levando o tesouro para o navio.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "Isso mesmo. Pronto?";
			link.l1 = "Você não precisava pedir. Não é como se tivéssemos escolha.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "Eles estão por toda parte, como ratos nos cortiços de Londres, Meritíssimo! Qual é o plano - ficamos firmes e trocamos tiros com os caras?";
			link.l1 = "Agora não, recuem! Viemos pelo tesouro, não para lutar!";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "Heh, sem objeções aqui.";
			link.l1 = "Então anda logo!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "Ei, Capitão, olha – parece que esse caminho leva a algum lugar. E está bem animado por lá, pelo barulho!";
			link.l1 = "Será que mais alguém ficou sabendo do tesouro? Tommy, você está ouvindo isso? Eles nos alcançaram. Certo, vou avançar, e vocês tratem de recebê-los direito aqui!";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "Agora eu também estou ouvindo! Seja lá quem for, é melhor você se apressar, heh-heh. Caso contrário, pra que serviu todo esse nosso esforço pra chegar até aqui?!";
			link.l1 = "Ah, eu odiaria que fosse esse o caso.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "Ah, é você, capitão! Então, você sobreviveu. Não vou mentir – não esperava por isso. Mas fico feliz, não me leve a mal, heh-heh.";
			link.l1 = "Eu também não esperava por isso, não vou mentir. Mas o fato de você ter sobrevivido – isso não me surpreende nem um pouco. Você fugiu?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "Você está me acusando injustamente! Tommy Irons nunca foge! Ele só volta para buscar reforços. Mas nem foi preciso – eu e meus rapazes demos conta do recado sozinhos, embora, mais uma vez, só eu tenha saído vivo dessa, heh...";
			link.l1 = "Talvez desta vez você devesse ter ido buscar reforços. Mas eu... eu fugi.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "Você fugiu? Heh, você me surpreendeu de novo. Mas na verdade eu queria correr até você assim que terminasse! Sou melhor que qualquer reforço, sabia? É só que...";
			link.l1 = "O que houve, Tom?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "Droga, enquanto eu estava enrolando, a entrada atrás de você foi bloqueada por pedras. Eu não consegui passar. Fico até envergonhado de ter demorado tanto pra limpar aquilo e não ter conseguido te ajudar. Acabei me perdendo tentando achar o caminho de volta pra buscar os rapazes e ajudar a tirar as pedras... Quando voltei, você já tinha voltado.";
			link.l1 = "É, talvez eu tenha vergonha de admitir o que aconteceu comigo hoje.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "E o que aconteceu? Não tenha medo, me conte. Mas se for algo engraçado, já aviso que vou rir. Como deveria ser diferente? Um amigo oferece o ombro e te cutuca com o cotovelo rindo.";
			link.l1 = "Bom, você realmente sabe como consolar alguém. Me diga, Tommy. Você disse que gostava de piratear. Ficou feliz de voltar a isso comigo?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "Vou ser direto. Seja eu pirata ou não, o que sempre amei de verdade é a aventura! Vejo que minha resposta não te agrada. Esse tipo de coisa, esses grandes assuntos, não são realmente da minha conta.";
			link.l1 = "Não é que isso não me satisfaça. Mas não era sobre isso que eu queria falar. Sabe... Percebi que com os Tiraqs, me afastei totalmente dos meus objetivos. E também... Charlie Prince era só um capanga, não um capitão pirata de verdade, entende, Tom? Isso já basta pra mim.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "Entendi. Por isso mesmo fiquei surpreso de ver você deixar o Terrax te controlar assim. Nem parecia você.";
			link.l1 = "Talvez eu realmente fosse Charlie Prince naquela época. Mas voltar ou não à pirataria, quem decide sou eu! E só se isso realmente servir aos meus interesses e me aproximar do meu objetivo!";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "Agora sim, isso é outra coisa! Mas quero dizer, seja Charlie Prince ou Charles de Maure – ainda é você. E com você, sempre foi uma maldita aventura!";
			link.l1 = "Fico feliz em ouvir isso, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "Lembre-se, quase ninguém vai te ajudar além de você mesmo. É melhor fazer o que você ama, mesmo sozinho, do que deixar que outros decidam por você!";
			link.l1 = "Verdade. Foi exatamente assim que me senti com o Terrax. Mesmo que eu acabe seguindo alguém de novo, vai ser só em condições que valham a pena, não como um maldito faz-tudo!";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "Você tem razão! Agora, vamos sair daqui – minhas pernas já estão bambas.";
			link.l1 = "Ei, eu ia dizer isso, haha. Mas você tem razão, vamos lá. Temos muito trabalho importante pela frente, Tom. Não esse tipo de coisa.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "Capitão, parece que temos companhia! Não estamos sozinhos aqui.";
			link.l1 = "Era só o que faltava... Tudo bem, vamos resolver isso agora. Depois, só vai dar mais dor de cabeça.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "Sim, Capitão.";
			link.l1 = "Prepare-se!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "Tem cada vez mais deles!";
			link.l1 = "Então não faz sentido continuar com isso! Recuem! Vamos despistá-los e ir direto para o tesouro!";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "Sim, Capitão!";
			link.l1 = "Anda logo, anda logo!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "Capitão, parece que tem uma entrada aqui! E alguém já está lá dentro.";
			link.l1 = "Prestem atenção — estamos sendo seguidos. Vou entrar e dar uma olhada enquanto vocês seguram aqui. Me deem cobertura, rapazes!";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "Sim, Capitão!";
			link.l1 = "Fique firme. Boa sorte pra você – pra todos nós!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é "+GetSexPhrase("um ladrão, hein! Guardas, peguem ele","Uma ladra, hein! Guardas, prendam ela")+"!!!","Não acredito! Virei de costas por um segundo – e você já está mexendo nas minhas coisas! Pare, ladrão!!!","Guardas! Roubo! Peguem o ladrão!!!");
			link.l1 = "Aaaah, demônio!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}
