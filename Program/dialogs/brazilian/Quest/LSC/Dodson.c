// Акула: Стивен Додсон
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
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, que diabos?";
				link.l1 = "Steven, houve um problema. Não consegui nem vir nem avisar sobre a minha ausência...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Bom te ver, camarada! Em que posso te ajudar? ";
				link.l1 = "Bom te ver também, Steve. Quero te agradecer por aquele espetáculo perfeitamente conduzido!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Bom te ver, camarada! Em que posso te ajudar?";
				link.l1 = "Tenho uma proposta pra você, Steven. Uma proposta de pirata.";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "There's our man! The job is done; your baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look? He-he!";
				link.l1 = "Ha, isso pode esperar. Ele está sendo bem tratado?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Bom te ver, camarada! Em que posso te ajudar?";
				link.l1 = "Preciso de uma coisa, Steven...";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Bom te ver, camarada! Em que posso te ajudar?";
				link.l1 = "Steven, tenho algo pra você.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Bom te ver, camarada! Em que posso te ajudar?";
				link.l1 = "Steven, preciso te pedir uma coisa. Talvez você não goste... mas preciso da sua ajuda.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ah, aí está você, "+pchar.name+". I was expecting you; Forest Devil told me about your trouble with Tortuga...";
				link.l1 = "Ele também me disse que você já encontrou uma solução. É verdade?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "Como estamos indo, "+pchar.name+"?";
				link.l1 = "Segredos por toda parte... Preciso do seu conselho, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "Quero te mostrar uma coisa... Vem comigo até o cais?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "Ah, meu amigo "+GetFullName(pchar)+"! Entre, entre, é bom ver você!";
				link.l1 = "Olá, Steven! Bem, estou aqui como prometido. Seu navio está pronto?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "E então, como vão os seus negócios? Ainda está atrás da 'Frota Dourada'?";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "Ah, meu amigo "+GetFullName(pchar)+" ! Entre, entre, é bom te ver!";
			link.l1 = "Olá, Steven. Estou em Sharptown a negócios e resolvi passar aqui por um minuto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ha! Então você é o nosso visitante noturno? Acabei de ser informado sobre esse incidente. Revirei seus pertences e encontrei a carta do Diabo da Floresta. Diabos, ela quase cheirava às selvas da Nova Espanha!\nSeu nome é "+GetFullName(pchar)+"? I'm Steven Dodson, better known to some as Shark. Svenson must've told you about me. Around Justice Island, however, I'm known as the Admiral.\nI apologize for the actions of my men last night. They were acting on orders from me to capture anyone who snuck into the hold; the Narwhals and Rivados routinely send thieves to steal provisions from us.\nChad let you go, I assume? Odd... I was just about to order him to release you.\nWhere's your ship? Is she intact?";
			link.l1 = "Chad? Pelo que entendi, seu contramestre jamais teria me deixado sair vivo da prisão. Eu mesmo me libertei, junto com um daqueles... daqueles Rivados.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Isso é interessante. E como foi que você saiu do Tártaro? Acho que vou ter que bater um papo com o Chad e os rapazes dele...";
			link.l1 = "Vai ser uma conversa de mão única, receio. Estão todos mortos. Chad ameaçou me deixar na jaula para sempre. Me chamou de Rivados, disse que a única forma de provar o contrário seria matando o mago negro Chimiset.";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "O quê?! Ah, Kapper, seu idiota do caralho...\nPrecisávamos do Chimiset vivo, e o Chad sabia disso! E por que ele acharia que você era o Rivados, se todos eles são negros?!";
			link.l1 = "Chimiset não está morto, Steven. O velho feiticeiro me convenceu de que, mesmo que eu o matasse, Chad nunca me deixaria sair de Tártaro com vida...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Em vez de matar o Chimiset, arrombei um baú de armas e munição e abati o Chad e os comparsas dele.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Ótimo! Isso é simplesmente do caralho! Mas ainda não entendo... por que diabos o Chad faria tudo isso?";
			link.l1 = "Estou chegando lá! Chimiset me contou que Chad fez um acordo com os Narvais – outro clã, pelo que entendi – para te matar e tomar seu lugar como chefe dos piratas. Os Narvais querem você morto, porque têm certeza de que você assassinou o líder deles, Alan... Alan Milton? Miller?";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Besteira! Eu não matei o Alan Milrow! Foi outra pessoa — talvez até um dos Narvais! Cheguei a pensar que podia ter sido o líder deles agora, o Donald Greenspan.";
			link.l1 = "Não. Chad matou ele. Chimiset testemunhou o crime – por isso Chad queria matar ele também. Ele não quis fazer isso pessoalmente porque tinha medo que Chimiset assombrasse ele, ou... ou sei lá, não sei. Enfim, foi por isso que ele queria que eu fizesse o serviço.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "E... por que o Chad mataria o Alan?";
			link.l1 = "Para te incriminar e te transformar em inimigo dos Narvais. Ele espalhou boatos que garantiram que a culpa caísse sobre você, tornando perigoso aparecer em público. E, quando você estivesse morto, ele ia culpar os Rivados pelo seu assassinato, para que seus piratas se voltassem contra eles.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "Encontrei esta carta no baú do Chad. Leia. Parece uma prova sólida, ainda que indireta.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(reading)... heh! In hindsight I'm not surprised at Chad's betrayal. The whoreson always wanted more power.\nBut the Narwhals! To seriously think I killed Alan! This will cost them double their current price on provisions!\nAs for Chimiset... I was planning to release him anyway; it's high time we made peace with the Rivados. You have shocked me, mate, truly...";
			link.l1 = "Eu entendo, Steven. Também não gosto disso. Não vim aqui pra me meter nessas intrigas políticas, vim pra encontrar você e o Nathaniel Hawk--";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "Hawk? Ele não está na Jamaica?";
			link.l1 = "Não. Agora é o Jackman que manda em Maroon Town. Fiquei sabendo que o Hawk chegou aqui do mesmo jeito que eu: pelo ídolo de Kukulcan.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "... Que porra você tá falando?";
			link.l1 = "Eu não cheguei aqui de navio, Steven. Sei que é difícil de acreditar, mas existe um ídolo indígena no continente espanhol que funciona como uma espécie de portal — não me olhe assim, não estou louco, nem bêbado! Eu também não entendo como isso é possível, mas é!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "...";
			link.l1 = "Um xamã chamado Olho de Cobra, na aldeia Miskito ao sul da Enseada de Amatique, ajudou Hawk a escapar de uns homens que queriam matá-lo. Ele mostrou ao Hawk o ídolo indígena — um ícone de Kukulcan — e isso o transportou para esta ilha. Olho de Cobra me contou que ele mesmo já tinha vindo para esta ilha exatamente do mesmo jeito, e me explicou como eu poderia fazer o mesmo.";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "...";
			link.l1 = "Eu fui até o ídolo à meia-noite, exatamente como ele me disse. E esse ídolo, que o dia todo parecia feito de pedra comum, tinha virado ouro maciço! E uma luz estranha brilhava dele.";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "...";
			link.l1 = "Quando toquei o ídolo, um círculo de luz se formou ao redor dele, fogo explodiu por toda parte, e então fui puxado para dentro do ídolo. Fui jogado aqui, no porão do seu navio, lá embaixo perto da proa, na rachadura...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "...";
			link.l1 = "Foi horrível, mesmo assim – fiquei enjoado e exausto depois da travessia. Olho de Cobra me deu uma poção especial pra aliviar isso, pelo menos. E pra piorar, fui atacado por um caranguejo gigante, porra! (respira fundo) ";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "... All right, I believe you.\nThat is, I believe the part about the crab. There are lot of those monsters around the island. We bait them with dead fish, so they hang around the submerged breaches in the hull.\nWonderful guards - scare thieves shitless. But all this about the idol...\nI won't reject that part of your story out of hand; I've heard about the strange rituals the Rivados used to conduct aboard their ships... There was talk of human sacrifices to a... to an Indian idol...";
			link.l1 = "Eu juro, é tudo verdade.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "Eu acredito que você acredita nisso. Mas vamos deixar de lado esses ídolos mágicos por enquanto.\nSegundo a carta do Jan, você quer que eu me torne o chefe dos Irmãos da Costa?";
			link.l1 = "Exato. Muita coisa mudou depois que você e o Hawk sumiram. Jackman quer se tornar o líder da Irmandade, e ele vai conseguir, se eu e o Jan não o impedirmos.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "Jackman está pronto para um jogo sério e sangrento. Tenho certeza de que foi ele quem armou a emboscada para Hawk. Também acho que ele matou Blaze Sharp. Fazer de você o líder dos Irmãos é a única maneira de detê-lo.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Olha, eu até toparia assumir a coroa, mas primeiro precisamos sair desta ilha.\nJá tive o suficiente dela. O plano era deixar o Dexter tomando conta da nossa base aqui — nunca quis ficar muito tempo — mas meu navio foi queimado numa batalha com os clãs.\nE nem pense em sugerir alguma baboseira mística de índio pra sair daqui. Ou é um navio, ou nada pra mim.";
			link.l1 = "Steven... (suspiro) Ainda preciso encontrar aquele ídolo! Olho de Cobra jurou que estaria aqui. Agora, você disse que sabia algo sobre os Rivados fazendo rituais com um ídolo. O que mais pode me contar?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "Nada. Tudo isso foi antes de eu chegar aqui – muito antes.";
			link.l1 = "Viajar por esses... esses portais de Kukulcan já não me assusta mais – e vai ser o jeito mais rápido de sair da ilha, conseguir um navio e te levar pra casa. Se não acreditar em mais nada, acredite que eu quero te ajudar.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "I understand... but I. Can't. Help. You. Aside from the rumours, I know sweet fuck-all about this idol.\nAnd you know, call me selfish, but I'm a little more preoccupied with this assassination business; Chad is dead, but I doubt the Narwhals will give up on trying to kill me.\nSince you need me alive and you're already involved in this mess, I want you to investigate this conspiracy.\nAs a newcomer, you can go places and talk to people that my lads could never reach. Find Chad's partners and bring them to me - or kill them, I don't care.\nTalk to Chimiset; the old black knows more than he lets on. And he may know more about your idol...\nBe careful with the Narwhals, and don't cross their borders unless you have the current password - they change it every week.\nOnce this whole thing's put to bed, I'll give you my rutters. They contain sailing directions and information you'll need to sail to and from Justice Island.\nGo. Find the conspirators. Restore order. Keep me alive.\nNow... Dexter needs to clean the bodies out of the gaol... Tartarus needs a new gaoler... and I need some rum. Fuck me, what a day.";
			link.l1 = "...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Would you believe it? Someone has killed the Admiral's gaoler, Chad Kapper! No doubt the work of that Rivados wizard he locked up, Chimiset...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead, but there's been no official statement and his body hasn't turned up. Perhaps, the Admiral simply gave him a secret mission...?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I haven't seen our gaoler, Chad Kapper, lately. Some say he was killed, some say he's still alive. The only thing people agree on is that no one has seen him...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the Admiral doubled provision prices for the Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Então, o que você tem aí, "+pchar.name+"? Alguma novidade sobre os Narvais?";
			link.l1 = "Sim. Você vai gostar de saber, Steven, que a conspiração foi desmascarada e os conspiradores estão mortos. Agora eu sei de tudo.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "Foi o que pensei quando ouvi os tiros... Fale comigo.";
			else dialog.text = "É mesmo? Que alívio! Conte-me.";
			link.l1 = "Foi tudo planejado pelo seu contramestre, Chad Kapper. Ele matou Alan Milrow nas celas do Tártaro e espalhou a mentira de que foi você quem fez isso. Os Narvais ficaram furiosos – especialmente a namorada do Alan, a Mary Ruiva...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "Mary estava sedenta por vingança e Chad Kapper se aproveitou da raiva dela. Eles armaram um plano para te assassinar. Fiquei sabendo que você costuma passear pela galeria de popa do San Augustine toda noite...";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Heh! Esse é um hábito que vou ter que largar... Continue.";
			link.l1 = "Eles precisavam de um rifle de longo alcance e precisão para executar o plano, e foi aí que Adolf Barbier entrou em cena. Mas o stutzen dele estava penhorado com Giuseppe Fazio, então Mary e Chad tiveram que comprá-lo de volta — Adolf resgatou o stutzen...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "They hired Marcello Cyclops, a former royal hunter, to take the shot. After that, Mary would kill him and use his corpse and rifle as proof the Rivados were responsible for the attack; Cyclops was a mulatto.";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "E tudo isso saiu da mente tortuosa do Chad... filho da puta esperto!";
			link.l1 = "E no fim, os Narvais e os piratas atacariam o clã Rivados e acabariam com eles. Chad se tornaria almirante e Mary seria sua amante. Embora... depois de algumas noites juntos, ele provavelmente teria cortado a garganta dela, já que ela sabia demais.";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "Enfim, já acabou. O Adolf não era muito de conversa, então tive que matá-lo ali mesmo na cabine dele. Também resolvi o caso da Mary e do Ciclope quando vieram pegar o stutzen com o Adolf.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "Então, todos eles estão mortos dentro da Santa Florentina, é isso? E ninguém sabe?";
			link.l1 = "Sim. Todos os três – e ninguém sabe além de nós.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "Ótimo. Testemunhas só iam complicar tudo. Eu cuido dos corpos. Você fez um bom trabalho, "+pchar.name+"! Se você fosse da minha tripulação, eu te faria imediato.";
			link.l1 = "Grandes elogios, Tubarão. Obrigado. Ah, dá uma olhada nessas cartas. Peguei dos corpos do Ciclope e da Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our scrappy madcap Red Mary has disappeared. I wouldn't be surprised if she's dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. You heard about that?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she's still inside her cabin, but I don't believe it; it's been a long time since I saw a light in her window.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she was a tough sort, but everybody loved her. Who could have done such a thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "Enfim, já passou. O Adolf não era de muita conversa, então tive que matá-lo ali mesmo na cabine dele. Também resolvi a situação com a Mary e o Ciclope quando vieram pegar o stutzen do Adolf.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Que pena que você arrumou confusão no Eva. Agora os Narvais vão querer sua cabeça por matar gente deles. Fique longe deles até conseguir fazer as pazes.\nNo geral, você se saiu bem, "+pchar.name+"! Se você estivesse na minha tripulação, eu faria de você meu imediato.";
			link.l1 = "Grandes elogios, Tubarão. Valeu. Ah, dá uma olhada nessas cartas. Peguei dos corpos do Ciclope e da Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you've committed! The Narwhals won't forget it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits, but... the girl. Why did you have to kill poor Mary?", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Pobre Mary? Não me diga que você sente pena daquela vadia.";
			link.l1 = "Eu sei. Chad enganou ela, manipulou seus sentimentos e seu temperamento impulsivo... Ela não merecia morrer por causa das ambições dele.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "Bem, vá falar com o Irmão Julian e acenda uma vela, se está se sentindo tão mal assim. Eu, pessoalmente, estou é feliz pra diabo que aquela desgraçada morreu.\nTá certo, vamos mudar de assunto. Sou grato pela sua ajuda, "+pchar.name+". Agora você pode contar com meu apoio. Quero te recompensar pelo excelente trabalho. Aqui estão quinhentos dobrões.";
			link.l1 = "Obrigado, Steven...";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you're the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "Eu não te conheço. O que você quer?";
			link.l1 = "Claro que não. Nunca nos vimos antes, e eu acabei de chegar. Olá, Steven. Estava procurando por você.";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "Muita gente já veio atrás de mim. A maioria agora está em cemitérios. Se não quiser se juntar a eles, talvez deva me dizer logo por que está me procurando.";
			link.l1 = "Temos um amigo em comum. Aqui, pegue esta carta. Foi escrita por Jan Svenson. O Velho Diabo da Floresta pode explicar as coisas muito melhor do que eu.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(lendo)... Hm. Isso realmente explica as coisas. E eu achando que você tinha vindo me entregar o ponto negro por ter matado o Blaze – ultimamente tem muito pirata querendo fazer isso.\nVocê deixou seu navio no anel externo? E como soube que eu estava aqui?";
			link.l1 = "Eu não fiz isso. Foi pura sorte. E sobre o Blaze... eu e o Jan não achamos que você seja responsável pela morte dele.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "Você está certo, eu não sou. Mas alguém quer que a Irmandade pense que fui eu.";
			link.l1 = "Interessante... sabe, eu vim aqui pra encontrar o Nathaniel Hawk, mas quem eu encontro é você, hein!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "Você vai ter que conversar sobre isso com os mais velhos da ilha. Procure o feiticeiro Rivados, Chimiset. O velho negro sabe muito mais do que aparenta.";
			link.l1 = "E onde posso encontrar esse mago?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "In my prison, aboard the Tartarus. I was planning to release him soon; it's time to improve our relations with the Rivados.\nYou can deliver the order yourself! Go to the Tartarus, tell Chad Kapper, the gaoler, that I want Chimiset freed.\nBetter yet, ask to see Chimiset first. Tell him I sent you, that I'll release him if he's talkative enough. I'm sure he'll tell you what you want to know.";
			link.l1 = "Hmm... onde está o Tártaro?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "Saia da minha residência, atravesse a ponte, vire à esquerda, passe pela fragata Caroline até o galeão Gloria e chegue à Esmeralda. Procure uma placa escrito 'loja' e entre pelas portas embaixo. Siga pela porta na proa do navio e você vai chegar ao Tártaro.\nTome cuidado na Esmeralda, ali é território dos Narwhal, embora outros possam visitar. Não irrite os guardas deles e não arrume confusão.";
			link.l1 = "Quem são esses Rivados e Narvais?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "Eles são clãs descendentes dos primeiros colonizadores da Ilha da Justiça. Os Narwhals são em sua maioria de origem inglesa, holandesa e francesa. Os Rivados são todos negros.\nCada clã tem um líder, e cada um controla vários navios que formam um território fechado para forasteiros.\nVocê precisa saber as senhas certas para visitar tanto o território dos Narwhals quanto o dos Rivados, e eles trocam as senhas toda semana.";
			link.l1 = "Bom saber, mas será que vão me deixar entrar na prisão?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "Eles vão sim. Aqui está a chave, assim Chad vai saber que fui eu quem te mandou. Não perca.";
			link.l1 = "Valeu. Vou falar com aquele... aquele Chimiset e volto com o resultado.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "Você já esteve em Tártaro?";
			link.l1 = "Sim. Passei suas ordens para o Chad e conversei com o Chimiset.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "O mago te contou alguma coisa?";
			link.l1 = "Ah, sim. Ele me contou onde encontrar o ídolo que estou procurando. Estava no San Geronimo, perto do território dos Narwhal, que afundou há alguns anos.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ha-ha-ha! Então, seu ídolo mágico agora está no fundo do mar, hein? Bem, camarada, parece que você está preso com a gente.";
			link.l1 = " Vou dar um jeito de chegar até o ídolo. Agora, Chimiset disse que você não deve confiar no Kapper, porque ele viu o Chad matar um tal de Alan Milrow--";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "O quê?! Chad matou o Alan? Chimiset está mentindo, isso não pode ser verdade!";
			link.l1 = "Steve, Chimiset estava apavorado. Se ele estava mentindo, fez um trabalho danado de bom nisso...";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "Maldição, isso é mesmo o fim da picada!\nO assassinato do Alan azedou minha relação com os Narvais — alguns até acham que fui eu quem fez isso — e agora descubro que um dos meus próprios oficiais cometeu o crime?!";
			link.l1 = "Parece que você acaba levando a culpa por muita coisa que não fez.";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "Percebi.";
			link.l1 = "Bem, receio que a coisa piore: Chimiset ouviu que alguns dos seus homens estavam planejando te matar. Ele só vai contar mais depois que você soltá-lo, e só em particular.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Ótimo. Eu sabia que esse dia estava indo bem demais.\nChimiset te contou algum detalhe?";
			link.l1 = "Não. Ele tem muito medo do Chad. Primeiro, quer garantir a própria segurança.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "Certo. Vamos avisar aos Rivados que quero me encontrar com o Chimiset. Vamos ver o que ele tem a dizer. E sobre a tentativa de me matar... só resta tomar cuidado.\nEntão, o que você vai fazer agora, "+pchar.name+"?";
			link.l1 = "Nada em particular ainda. Vou dar uma volta pela ilha e conhecer os moradores – talvez eu tenha alguma ideia de como sair daqui. E preciso encontrar Nathaniel Hawk, ele é o motivo de eu ter vindo para cá.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "Certo. Não esqueça de me procurar quando encontrar um jeito de sair desta ilha, vou te dar os roteiros com minhas instruções de navegação pra você poder trazer um navio de volta aqui. Também vou te passar outras informações que você vai precisar.";
			link.l1 = "Beleza. Eu vou te visitar com certeza, Steve!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = ""+pchar.name+", más notícias: Chimiset está morto e Chad Kapper sumiu.";
			link.l1 = "Maldição! Então, o Chad finalmente matou o velho feiticeiro...";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "Parece que sim. Essa situação está piorando a cada hora. Eu já tinha uma trégua pronta com o Eddie Negro, e agora...\nBem, podemos esquecer a paz com os Rivados. Aliás, eles sabem que você falou com o Chimiset antes dele morrer, e acham que você é um dos meus, então fique longe deles.";
			link.l1 = "Maravilhoso.";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "Tem mais. Recebi uma carta do mediador e diplomata da ilha, Giuseppe Fazio. Ele me convidou para ir à cabine dele a bordo do Caroline à meia-noite.\nEle também disse que eu devo ir sozinho, porque minha vida está em risco e meus homens não são confiáveis.\nIsso faz sentido – Chimiset nos alertou sobre um traidor na nossa tripulação – mas ainda assim, tudo isso parece muito suspeito. Sozinho, à meia-noite...\nNormalmente, o gordo é quem vem até mim. Vou pedir sua ajuda, "+pchar.name+". Jan disse que você é um homem engenhoso e corajoso, além de um excelente lutador. Quero que me acompanhe até a reunião à meia-noite.";
			link.l1 = "No need to ask, Steven; I'm in. I don't like this invitation either - it's almost certainly a trap.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Talvez. Espero estar enganado, mas prefiro estar preparado. Fico feliz por ter você comigo\nVenha ao convés principal do San Augustine à meia-noite e vamos ver o Fazio. Daqui até o Caroline é só uma caminhada curta.";
			link.l1 = "Meia-noite, então. E estarei bem armado.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "Certo, "+pchar.name+", não vamos perder tempo. Vamos ver o que o velho gordo Fazio tem a dizer. Fique perto de mim.";
			link.l1 = "Estou com você, Steve. Mantenha sua arma pronta...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "Onde está aquele gordo? Para onde ele foi? Que jeito de tratar os convidados! Você está vendo ele, "+pchar.name+"? Eu não.\nTalvez devêssemos olhar nos baús dele, vai que ele está lá dentro... se não acharmos nada, pelo menos ganhamos uma compensação pelo trabalho, ha-ha!";
			link.l1 = "Heh, duvido que exista um baú no mundo em que ele conseguiria se enfiar - silêncio! Steven! Ouvi alguma coisa...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "... prepare-se, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Caroline_DlgExit_3");
		break;
		
		case "caroline_5":
			dialog.text = "Porra! Conseguimos... Caralho, achei que estávamos ferrados.";
			link.l1 = "Já passei por enrascadas piores que essa, mas até eu admito, dessa vez foi por um triz. Chimiset estava certo: Chad era um traidor. Quem era aquela garota que comandava eles?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "Mary Casper, também conhecida como Mary Vermelha. A amante do falecido Alan Milrow.\nEu entendo por que Chad estava aqui – ele queria tomar o meu lugar – mas o que Mary estava fazendo aqui?";
			link.l1 = "Se ela era amante do Alan, então está claro: ela queria vingança pela morte dele. Coitada, nem percebeu que estava lutando ao lado do próprio homem que matou o Alan...";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Faz sentido. Ah, eu vou fazer os Narvais pagarem por isso! Vou parar de vender mantimentos pra eles, deixar que morram de fome!\nE o que eles podem fazer a respeito? Se nos atacarem, o San Augustine aguenta qualquer cerco! Eles vão se arrepender. E eu vou pregar o traseiro gordo do Fazio na parede atrás da minha cadeira!";
			link.l1 = "Steve, Steve, espera! E se... e se os Narvais não tivessem nada a ver com isso? Chad era um dos seus piratas, não dos Narvais. Chad matou Alan, Chad matou Chimiset, e Chad espalhou os boatos sobre você. E se tudo isso começa e termina com Chad?";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "... Maldito seja, "+pchar.name+", mas... talvez você tenha razão.\nTudo bem, eu te devo essa, então vou te dar uma chance de investigar isso. Se conseguir provar que os Narvais não tiveram nada a ver com isso, eu cancelo a guerra.\nVocê ganhou minha confiança, e pode contar com minha ajuda no que precisar. Eu até faria de você meu imediato, se ainda tivesse um navio.";
			link.l1 = "Você pode me pagar assumindo a liderança dos Irmãos da Costa quando sairmos daqui. Vai descansar um pouco, eu vou dar uma olhada nesta cabine pra ver se encontro mais pistas — e não ouse morrer enquanto eu estiver fora!";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Heh, nem sonharia com isso. Vou mandar alguém limpar esses corpos. Os caranguejos vão se fartar hoje à noite! (cospe) Até mais, meu amigo.";
			link.l1 = "Boa noite.";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Bem, "+pchar.name+", aprendeu alguma novidade?";
			link.l1 = "Pode encerrar sua vingança, Steven. Os Narvais não estavam envolvidos no complô contra você, com exceção da Mary e dos caras que enfrentamos no Caroline – acho que ela os convenceu a nos atacar. Fazio foi obrigado a te enviar o convite. Encontrei uma carta na cabine dele que explica muita coisa. Leia.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(lendo)... Hmm... esse é o Fazio de sempre: só pensa em salvar a própria pele. Então, foi tudo culpa do Chad mesmo, do começo ao fim...";
			link.l1 = "E tudo isso porque ele queria ser Almirante. Eu visitei Donald Greenspan. Ele jurou que nem ele, nem nenhum dos homens dele estavam conspirando contra você.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Você confia nele?";
			link.l1 = "Sim. O Donald vai te livrar da acusação pela morte do Alan. Ele está pronto pra te visitar pessoalmente e resolver tudo numa conversa.";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Good. Much as I love a dustup, a war at this stage would be pointless. Too many have died already, and the ones who set all this in motion are crab food.\nYou say Donald is ready to apologize? Fine, let's salvage what relations we can with the Narwhals; I think the Rivados are lost to us because of Chimiset.";
			link.l1 = "Esta pode ser a única chance que você tem de encontrar paz.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Você já me convenceu. Diga ao Donald que estou pronto para vê-lo e fazer as pazes.";
			link.l1 = "Estou a caminho.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Espere, "+pchar.name+"Você fez um bom trabalho e merece ser bem pago. Aqui estão quinhentos dobrões.";
			link.l1 = "Obrigado!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "Na minha prisão, o Tártaro. Você pode ir lá e vê-lo. Vou te dar a chave. Fale com Chad Kapper, nosso carcereiro--";
			link.l1 = "Espere, Steven. Tem algo que você precisa saber sobre o Kapper...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "... Estou ouvindo...";
			link.l1 = "Eu não sei como dizer isso de outro jeito, mas... Kapper está tramando te matar.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "... É bom que você tenha um motivo muito forte pra acusar um dos meus camaradas mais antigos de traição.";
			link.l1 = "Deixa eu te contar toda a história--";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Fale rápido.";
			link.l1 = "Depois que me vi no porão alagado, saí por um buraco no casco e nadei entre os destroços procurando um lugar para subir. Acabei encontrando um naufrágio onde consegui entrar por uma porta na proa. Lá dentro, uma garota de casaco vermelho brigava com dois brutamontes--";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Alguém tentou matar a Mary Vermelha?";
			link.l1 = "Aparentemente. Ajudei ela a acabar com aqueles desgraçados e depois tivemos uma conversa interessante... Me diz, Steve, quem são os 'Narvais' e os 'Rivados'? Ela mencionou esses nomes várias vezes.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Eles são clãs descendentes dos primeiros colonizadores da Ilha da Justiça. Os Narwhals são em sua maioria de origem inglesa, holandesa e francesa. Os Rivados são todos negros.\nCada clã tem um líder, e cada um controla vários navios que formam um território fechado para forasteiros.\nVocê precisa saber as senhas certas para visitar tanto o território dos Narwhals quanto o dos Rivados, e eles trocam as senhas toda semana.";
			link.l1 = "A-ah, entendi... e a Mary é uma Narval?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Sim. Então, o que ela te disse?";
			link.l1 = "Chad Kapper matou Alan Milrow, o amante dela, que foi capturado por você. Depois disso, ele espalhou um boato de que foi você quem cometeu o assassinato. Ele tentou manipular a sede de vingança da Mary para alcançar seus próprios objetivos.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "O Chad matou o Alan?! Mas por quê?";
			link.l1 = "Colocar a culpa em você e fazer com que os Narvais fiquem hostis a você. O objetivo final de Kapper é te eliminar e tomar o seu lugar como Almirante. Mary se recusou a participar do plano dele — e a se tornar amante dele — então ele mandou seus homens matá-la.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "E ela te contou tudo isso?";
			link.l1 = "Sim. Não acho que ela estivesse mentindo. Além disso, ela me deu uma carta do Chad Kapper. Já li. Aqui.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = " (lendo) ... Sim, essa é mesmo a letra do Chad. Argh! Inacreditável! Desgraçado! Traidor!\nVou enforcá-lo com as próprias tripas! Layton! Chame cinco homens e--\nPensando bem... esqueça, Layton. Dispensado! Vamos fazer isso com inteligência.\nEu estava procurando um jeito de melhorar nossa relação com os Rivados, e talvez essa seja a chance.\nO feiticeiro deles, Chimiset, está preso em Tártaro, a prisão local. Vamos deixar que os Rivados libertem o homem deles, e no processo, eles vão matar o Chad pra gente.\nLayton! Vá até Tártaro e tire todos os nossos guardas do convés superior dela! "+pchar.name+", tenho um trabalho importante para você. Encontre o líder dos Rivados, o Eddie Negro, e negocie com ele--";
			link.l1 = "Eu? Mas eu não conheço ninguém aqui!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Você está prestes a fazer isso, começando pelo Eddie: ele é o chefe de todo o clã Rivados.\nVocê é a melhor pessoa para tratar de diplomacia por nós. Nenhum dos meus piratas conseguiria uma audiência com o Eddie... e, pra ser sincero, nenhum deles tem lá muita lábia.";
			link.l1 = "(suspiro) Tudo bem, vou falar com esse... Eddie Negro.";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Pegue esta chave e entregue a ele. Ela abre todas as portas do Tartarus – os negros vão precisar dela se quiserem resgatar Chimiset. Além disso, pegue estes cinquenta dobrões. Outro local que você vai conhecer é Giuseppe Fazio, um mediador e diplomata no Caroline. Pegue os dobrões e compre a senha desta semana para o território dos Rivados – Fazio faz questão de conseguir as senhas assim que são escolhidas. Depois, vá até o Protetor. É a residência do Eddie Negro. Diga a ele que Chad Kapper se juntou aos Narvais, parou de seguir minhas ordens e vai assassinar Chimiset hoje. Entregue a chave a ele, diga para reunir um bom grupo e atacar o Tartarus. Vamos matar dois coelhos com uma cajadada só: os Rivados vão nos considerar aliados e Kapper vai morrer nas mãos dos negros. Entendeu tudo?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "Acho que sim, mas onde encontro o Protetor e a Caroline?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Escuta, Steve, me conta quem são esses Rivados e Narvais. Eu ainda não sei nada sobre eles.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "Eles são clãs descendentes dos primeiros colonizadores da Ilha da Justiça. Os Narvais são, em sua maioria, de origem inglesa, holandesa e francesa. Os Rivados são todos negros.\nCada clã tem um líder, e cada um controla vários navios que formam um território fechado para forasteiros.\nVocê precisa saber as senhas certas para entrar tanto no território dos Narvais quanto no dos Rivados, e eles mudam as senhas toda semana.";
			link.l1 = "Agora entendi. Mas onde encontro o Protetor e a Caroline?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Saia da minha residência, atravesse a ponte de corda e vire à esquerda. Essa será a Caroline.\Chegar ao Protetor é um pouco mais complicado: depois de cruzar a ponte, vire à direita e vá até a Santa Florentina - do outro lado da ponte de tábuas.\nProcure os soldados Rivados - como eu disse, todos eles são negros. Eles vão pedir a senha. Diga em voz alta e clara. Depois entre na Fury e acesse o Protetor pela popa.";
			link.l1 = "Certo... Acho que entendi.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Então, mãos à obra, amigo!";
			link.l1 = "Eu volto já.";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Você ainda está aqui? Vá ver o Eddie Negro agora mesmo!";
			link.l1 = "Estou a caminho.";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Alguém tentou matar a Mary Vermelha?.";
			link.l1 = "Era esse o nome dela? Tentei salvá-la, mas um dos agressores a atingiu com um golpe de sabre.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Sinto muito pela garota, mas não estou surpreso. Mary sempre foi encrenqueira.\nE quanto ao Chad? Ele é meu contramestre.";
			link.l1 = "Seu contramestre? Ah... hum, aqui, leia esta carta. Encontrei no corpo da garota. Kapper está planejando um atentado contra sua vida, Steven.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Onde você estava?! Disseram que os Rivados libertaram o feiticeiro deles, mas ninguém te viu por horas!";
			link.l1 = "Me desculpe, Steven. Os negros me mantiveram como refém no Protector para garantir a própria segurança caso você os traísse. Eles libertaram Chimiset, sim, mas Chad conseguiu fugir.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "Merda! Nunca confie num negro pra fazer o trabalho de um branco... Consegue estragar até uma tarefa simples... Malditos sejam esses Rivados!";
			link.l1 = "O Chad está escondido entre os Narvais...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Claro que ele sabe! Não é nenhum idiota – ele entende que os Rivados nunca teriam entrado no Tártaro sem a minha ajuda! Agora ele vai se esconder e tramar nas sombras.\nLayton! Dobre a guarda! Fiquem atentos o tempo todo! Uma fortuna pra quem mandar Chad Kapper pro inferno!!";
			link.l1 = "Steven, eu vou indo. Talvez eu consiga encontrar o Chad. Volto assim que tiver novidades.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "O que aconteceu, "+pchar.name+"? Você parece que está sendo perseguido pelo próprio Diabo!";
			link.l1 = "Você conseguiu um barril de uísque?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Que uísque--?";
			link.l1 = "Você conseguiu um barril de uísque?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Fala mais baixo, homem! Não tenho uísque nenhum! O que foi?";
			link.l1 = "Graças a Deus cheguei a tempo... Chad Kapper comprou um barril de Bushmills do Axel Yost--";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills? Essa é a minha bebida favorita! Faz séculos que não tomo uma!";
			link.l1 = "Yes-yes, and Kapper knows that; he asked his pal, Marcello Cyclops, to buy some arsenic from Sancho Carpentero. You get it now?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Ele ia me envenenar...?";
			link.l1 = "Sim! Por isso eu estava com tanta pressa. Porra, meu coração... Escuta, se alguém te trouxer um barril de uísque, não beba! Vai estar envenenado.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = ""+pchar.name+", obrigado pelo aviso, vou tomar cuidado - espera aí, pra onde você vai agora?";
			link.l1 = "Preciso encontrar o Kapper e o Cyclops. Acho que sei onde eles estão. Falo com você em breve!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ha! Justo o homem que eu procurava! Parece que te devo a minha vida.";
			link.l1 = "O uísque chegou?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "Consegui! Bushmills, exatamente como você disse. Nosso querido Fazio foi tão generoso – me deu de presente. Naturalmente, eu o prendi.";
			link.l1 = "Ele confessou?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "Ele contou. Disse que o Kapper obrigou ele a fazer isso, mandou dizer que o uísque era um presente dos Narvais..";
			link.l1 = "Kapper está morto. Os amigos dele da Narval também. Agora só resta um desgraçado — Marcello Cyclops... Tenho certeza de que o Fazio sabe onde ele está. Deixa comigo, vou apertar ele!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Fique à vontade – mas cuidado para não matá-lo, nosso querido Fazio anda com a saúde bem fraca.";
			link.l1 = "Vou pegar leve... na maioria das vezes.";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", amigo, tem algo muito errado comigo...";
			link.l1 = "Steven! Você bebeu esse uísque?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Sim... Bushmills... Giuseppe Fazio trouxe pra mim hoje, disse que era um presente do líder do Narval... um sinal de paz...\nAh, porra, isso dói!";
			link.l1 = "Aquele uísque estava envenenado com arsênico!! Chad e Cyclops fizeram isso!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Argh... desgraçado, finalmente me pegou...";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "Você não vai morrer! Ouviu? Não vai! Rápido, pegue este frasco. Esta é a poção de cura mais poderosa do mundo, cura qualquer coisa. Beba... agora!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Steven...!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", esse negócio é incrível. Ainda estou meio enjoado, mas a dor quase sumiu...";
			link.l1 = "Um xamã indígena me deu isso. Beba tudo, rápido! Aí está...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "Um milagre... Estou me sentindo ótimo! Obrigado, amigo... Vou me lembrar disso!";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "É melhor você descansar agora. Você está com uma cara horrível. Aquele desgraçado do Kapper não vai mais poder te ameaçar – já cuidei dele e de alguns dos seus amigos do Narval também. Só falta o Marcello Ciclope. Você disse que foi o Fazio quem trouxe o uísque, certo?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "É melhor você descansar agora. Você está com cara de morto. Foi o Fazio que trouxe o uísque pra você?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Sim. Fiquei pensando por que ele parecia nervoso... achei que era só por estar na minha ilustre presença, he-he...";
			link.l1 = "O Kapper deve ter forçado ele a fazer isso. Tudo bem, vou fazer uma visitinha àquele porco gordo e arrancar umas informações dele. Agora descanse, Steven!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Sim. Eu me perguntei por que ele parecia nervoso... achei que era só por estar diante da minha ilustre presença, he-he...";
			link.l1 = "O Kapper deve ter forçado ele a isso. Vou pegar aquele porco gordo mais cedo ou mais tarde, mas agora preciso lidar com o Kapper e o Ciclope. Eu sei onde eles estão escondidos. Agora descanse, Steven!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "Oi, "+pchar.name+"! Ouvi falar da sua briga com o Kapper no Eva, ha-ha! Estou impressionado! Matar o Chad e os homens dele, sozinho... O Jan tinha razão sobre suas habilidades de luta.";
			link.l1 = "Não só resolvi o problema com o Kapper, como também impedi uma tentativa contra a sua vida. Iam te envenenar, Steven. Mas está tudo certo, eu cuidei disso.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "Me envenenar? Como?";
			link.l1 = "O Chad comprou um barril de uísque Bushmills irlandês do Axel--";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills? Esse é o meu preferido! Faz séculos que não bebo isso!";
			link.l1 = "E o Kapper sabia disso. Ele pediu ao amigo dele, Marcello Ciclope, para comprar arsênico do Sancho Carpentero. Depois, ele e os comparsas agarraram o Fazio e desceram até o porão de carga do Eva. A ideia era envenenar o uísque e obrigar o Fazio a levar pra você como um 'presente dos Narvais'.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Damn... it would've worked, too; I'd have drink a pint of that whiskey in a heartbeat.";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "O Chad estava contando com isso. Mas ele falhou – nem teve tempo de colocar o arsênico. Então... Levei o barril comigo. Pode ficar com ele, está intacto.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "O Chad estava contando com isso. Mas ele falhou – nem teve tempo de colocar o arsênico.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Mostre-me... "+pchar.name+", isso é Bushmills de verdade! O melhor uísque irlandês! Argh, sonhei com isso por anos!\nVocê, meu amigo... Porra, você é um milagreiro! Você elimina o Chad, salva minha vida e ainda me traz um barril do meu uísque favorito como se não fosse nada!\nIsso merece uma recompensa à altura.\n (revirando coisas) Que diabos...? Ah! Aqui, pega isso. Se chama Martelo de Thor, e é eterno. Nunca mais você vai precisar temer que seus canhões explodam na sua cara! Seu artilheiro vai adorar isso!";
			link.l1 = "Meu Deus, Steven... obrigado! Tenho certeza de que ele vai.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "Agora, se me dá licença, está na hora de eu fazer amizade com esse uísque magnífico... "+pchar.name+", venha me ver amanhã. Enquanto isso, tenho umas coisas para pensar...";
			link.l1 = "Tá bom, Steven, não vou te impedir de tomar seu uísque, ha-ha!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "Você me fez um favor contando tudo isso. Preciso pensar nas suas palavras e nas ações do Chad... depois te chamo.";
			link.l1 = "Vou estar esperando!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ha, aí está você, "+pchar.name+"Agora que todos estão aqui, podemos começar. Chamei você e o Layton para discutirmos a situação e decidirmos o que fazer sobre os Narvais.";
			link.l1 = "O que você quer dizer com 'o que fazer sobre os Narvais'?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "O que você quer dizer com 'o que você quer dizer?' Chad tentou me matar com a ajuda dos Narvais.   Eu vejo isso como um ato aberto de agressão. Isso não pode ficar sem resposta. Considerando que temos boas relações com os Rivados, eu proponho o seguinte...   Vamos formalizar nossa aliança com os Negros, juntar nossos homens e acabar de uma vez por todas com os Narvais.   Você, "+pchar.name+", você vai ser nosso diplomata mais uma vez. Fale com o Black Eddie e a Chimiset, convença-os a aceitar minha oferta de amizade. O Dexter vai cuidar dos nossos planos de batalha, ele conhece a ilha melhor do que ninguém. Layton?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "No need to exterminate the Narwhals at the first stroke; we control the island's food.\nForce them to retreat to the San Gabriel, and we can pen them up and starve them. What do you say, "+pchar.name+"?";
			link.l1 = "O que eu digo? ... Eu digo que você devia deixar os Narvais em paz, Steven.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "... você levou uma pancada na cabeça antes de vir pra cá? Esqueceu que os homens que lutaram com o Chad eram Narvais?";
			link.l1 = "Nem todos eles. Marcello Ciclope não era. Na verdade, ele era leal aos Rivados – afinal, era mulato. Acho que os únicos Narvais que se juntaram ao Chad foram aqueles que ele conseguiu comprar com dinheiro, ou com a mentira de que você matou Alan Milrow.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "E o que você sugere, que eu simplesmente ignore tudo isso?";
			link.l1 = "Eu sugiro que eu faça o papel de diplomata... mas com o chefe dos Narvais, Donald Greenspan. Vai me ouvir, Steven?";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "... Continue ...";
			link.l1 = "Aprendi muito sobre a Cidade dos Navios Abandonados desde que cheguei aqui. O pessoal daqui deixou claro que, quando só havia os dois clãs na ilha, a guerra era constante. A chegada dos seus piratas trouxe uma terceira força para a ilha, criando equilíbrio e paz pela primeira vez. Mas os Narvais e os Rivados continuam fortes, e uma vitória vai custar caro.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "O preço pela destruição dos Narvais será a vida de muitos piratas e Rivados. Além disso, Layton disse que o cerco a San Gabriel vai demorar, e se os Rivados começarem a sentir que perderam demais nessa campanha, eles podem desistir... ou até mesmo se voltar contra nós.";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "Não se esqueça que ambos os clãs ainda querem dominar a ilha, e até pouco tempo atrás estavam unidos para te enfrentar. Essa guerra pode não acabar tão rápido ou de forma tão previsível quanto você imagina. E no meio disso tudo estão as pessoas comuns. Você realmente quer governar um cemitério?";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "... Você tem bons argumentos... mas ainda não me convenceu.";
			link.l1 = "I also need to leave the island somehow; I have to reach the idol of Kukulcan on the seabed. The Rivados can't help me... but maybe the Narwhals can. I've heard they have some smart, talented men among them. They won't help me if they're at war with me.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "A-ha! I knew you had selfish reasons for wanting peace! And I guess that one of them is that redhead on the Ceres, eh, my friend? Am I right? Don't worry about her, "+pchar.name+", we'll find a safe place for her before the fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" Mas se você está tão decidido, tudo bem. Vá falar com o Donald. Ele mora nos fundos da Esmeralda. Veja o que esse canalha tem a dizer.\nSe você se convencer de que ele e o clã dele não tiveram nada a ver com o plano do Chad... eu vou considerar a paz.";
			link.l1 = "Obrigado, Steven. Tenho certeza de que essa é a decisão certa.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "Mas não deixa ele sair dessa tão fácil, hein! Aqueles ainda eram os homens dele com o Chad – ainda eram Narvais! Faz ele lamber suas botas, que ele mostre arrependimento de verdade!";
			link.l1 = "Eu vou, eu vou.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "Então, você já falou com o Donald?";
			link.l1 = "Conversei com ele, e ele confirmou minhas suspeitas. Nem ele, nem o clã como um todo, tiveram qualquer envolvimento no plano do Chad. Todos os Narvais que participaram foram recrutados pelo Kapper. Ele está muito chateado e me garantiu que não te culpa pelo assassinato do Alan Milrow, nem por tudo o que aconteceu depois.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "Ele está preparado para ficar diante de mim e dizer tudo isso na minha cara?";
			link.l1 = "Ele jurou pela Bíblia que faria isso.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Heh, então é isso mesmo... Parece que o único desgraçado a ser culpado é meu contramestre traidor...";
			link.l1 = "Eu tenho certeza disso, Steven. Nós não precisamos dessa guerra, ninguém precisa. Não seria bom para os negócios.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "(bate na mesa) Muito bem, então! Está feito. Se o Greenspan vier e beijar a minha bunda, tudo estará perdoado... e teremos paz.";
			link.l1 = "Vou avisá-lo imediatamente. Steven... Fico feliz que evitamos essa guerra.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Feel free to bring your Mary over to the San Augustine, I can set aside some quarters for the two of you.";
			else sTemp = "";
			dialog.text = "Espere... "+pchar.name+", fico muito feliz que você tenha aparecido aqui, nesta Ilha da Justiça esquecida por Deus.\nJan falou muito bem de você na carta... mas qualquer expectativa que eu tinha foi completamente superada.\nSe você estivesse na minha tripulação... na verdade! Eu te ofereço o lugar do Kapper, enquanto estiver por aqui. Você vai comandar minha guarnição no Tartarus. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "Não, Steven, obrigado, mas não vou ficar aqui por muito tempo. Dê o trabalho para algum rapaz de confiança que mereça mais. E sobre a Mary... estamos bem no Ceres.";
			else link.l1 = "Não, Steven, obrigado, mas não vou ficar aqui por muito tempo. Dê o trabalho para algum rapaz de confiança que mereça mais.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = " Difícil imaginar alguém mais merecedor ou confiável do que você, e apesar do que diz, não acho que sair desta ilha vai ser tão fácil quanto espera.\nMas que seja. Agora, não posso deixar você sair daqui sem uma recompensa, então cale a boca e aceite essas quinhentas dobrões.";
			link.l1 = "Obrigado!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Vamos falar dos nossos negócios... Pegue meus roteiros náuticos. Eles têm instruções de navegação que vão te permitir chegar à ilha com o navio inteiro.\nNão os perca! Sem eles, seu navio vai afundar nos recifes ou ser destruído pelas tempestades. E lembre-se: só dá pra chegar na ilha com uma embarcação relativamente pequena! Bote, tartana, lugre, escuna, nada maior que isso.\nQuando você voltar pra me buscar, eu me junto a você e ao Svenson nessa jogada.\nAinda acho difícil acreditar que um ídolo indígena afundado vai te ajudar, mas... Boa sorte, meu amigo.";
			link.l1 = "Não é em Deus que precisamos confiar, Steven, mas em Kukulcan. Até nos encontrarmos de novo.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = ""+pchar.name+"... return as quickly as you can. My storehouses are running low; soon there will be no provision at all. You know what armed, hungry men are capable of?";
			link.l1 = "Tenho uma ideia. Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "Já encontrou um jeito de sair da ilha, "+pchar.name+"?";
			link.l1 = "Ainda não, Steven, ainda estou trabalhando nisso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Então, o que você tem, "+pchar.name+"? Tem alguma novidade interessante?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, gostaria de pedir que me devolva meus pertences que você confiscou.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, me conte mais sobre esta ilha.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Tem certeza de que o Hawk não está na ilha? Ele passou pelo ídolo, então deve estar aqui.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Você conhece um homem chamado White Boy?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "Quais territórios pertencem aos Narvais e aos Rivados?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "Como posso descobrir as senhas para embarcar nos navios dos clãs?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Escuta, existe um mapa da ilha?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "Você tem uma espada larga tão bonita. Nunca vi nada parecido antes...";
				link.l8.go = "blade";
			}
			link.l9 = "Sem perguntas por enquanto. Talvez em breve...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ah, sim! Tinha me esquecido deles... Suas coisas estão lá em cima, num baú. Pode pegar, o Layton não vai te impedir.";
			link.l1 = "Valeu!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "This island is over a hundred years old; I've seen caravels on the outer ring whose keels must've been laid in 1550 or earlier.\nThere's a shoal beneath our feet that buttresses the wrecks that founder here, keeps them above water. And even though many ships rot to dust each year, storms and a powerful sea current bring more.\nJustice Island shits, eats, and grows like a thing alive.\nThe first settlers arrived here on de Betancourt's expedition, of which the San Augustine and Tartarus were part. The Tartarus carried a lot of black slaves in her hold, one of whom was a man named Pedro Rivados. He led an uprising against his Spanish captors which failed, and he was sentenced to a slow death: tied to a mast and left to cook in the sun.\nBut his attempt at freedom weakened de Betancourt's crews such that a second uprising succeeded, and they formed the Rivados clan in his honour.\nFearing Rivados dominance of the island, with their savage African ways, the white Christian settlers miraculously managed to rise above their various nationalities and united to form the Narwhal clan.\nHeh, few things'll make white men set aside their differences faster than the threat of playing second fiddle to Negroes.\nThe Narwhals have a lot of mercenaries, soldiers, officers and adventurers in their ranks. Year on year they gather supplies and selectively recruit new men from the shipwrecks that arrive here. You can see the results today: they are a disciplined, professional army - and that's been enough to curb Rivados ambitions about ruling the island.";
			link.l1 = "Existe alguma ligação entre a ilha e o resto do Caribe?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "Nenhum nos últimos dez anos. Se você ouvir o que dizem por aqui, parece que o clima em volta da ilha mudou: as tempestades ficaram mais frequentes, e a correnteza ficou mais forte.\nÉ como se, de repente, a ilha tivesse sido isolada do resto do Caribe.\nOs ilhéus costumavam negociar com os bucaneiros de Cuba, comprando comida com ouro e tesouros resgatados dos naufrágios, mas nenhum bucaneiro visita a Ilha da Justiça há uma década.\nBem, pelo menos nenhum que tenha voltado, de qualquer forma.";
			link.l1 = "Hm. Então parece que o Diabo da Floresta e o Pastor Negro estavam certos... E por que as pessoas não foram embora da ilha quando tiveram a chance?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Alguns quiseram, mas a maioria preferiu ficar. Muitos já fizeram daqui seu lar, outros nasceram aqui e não conhecem outro lugar.\nTem gente que quer ir embora, mas morre de medo de arriscar atravessar a zona de tempestades nesses barcos velhos e remendados.\nQuanto aos Rivados... bem, eles são negros, e da última vez que vi, lá fora o mundo ainda é dos brancos. Dá pra culpar eles por quererem ficar?";
			link.l1 = "E por que você veio parar aqui, Dodson? Você tinha uma fragata, era um pirata respeitado--";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "(slams the table) I was being hunted!!\nI was blamed for the murder of Blaze Sharp! By whom, or for what reason, I've no idea.\nSomeone made me a pawn in their game and I was surrounded by enemies, abandoned by my friends, so I had to leave Isla Tesoro and lay low.\nI'd known of this island for a long time, but I couldn't reach it on my frigate; she was too big to bypass the reefs. So, I traded her for a brig.\nI was attacked by the Narwhals and Rivados as soon as I got here - guess the only people Negroes and white men hate more than each other are pirates, he-he. They rowed longboats to my ship at night and fired her.\nWe blasted their tubs to matchwood with our cannons, but the fire did its work - my poor brig was burnt to her frames.\nWe got mad as hell and struck back: we stormed the San Augustine and showed them how corsairs fight! They couldn't hold her and showed us their cowardly backs.\nWe captured San Augustine and discovered that the whole island used her as their storehouse! Overnight, we became the most important clan on the island.\nNow, every fucking Justice Islander has to buy back their own food at a price we name, ha-ha-ha!\nWe also captured two of the clan leaders: Alan Milrow of the Narwhals and a Rivados voodoo man name of Chimiset. My mate Layton spent the next few days scouting the island and then we attacked the Tartarus, the old slave ship.\nNow we hold two vessels and the clans have to deal with us... or starve. Nowadays, we have something like peace, here.\nAs for the citizens... we sell food to them proper cheap - they didn't take up arms against us. Anyway, they seem to like the fact that we balance out the other two clans, somewhat.";
			link.l1 = "Incrível... que história impressionante!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "Não vi ele. É a primeira vez que ouço dizer que o Hawk está em outro lugar além de Maroon Town.   É possível que ele esteja em algum canto da ilha ou no anel externo sem ter sido visto — tem lugar de sobra pra se esconder — mas você pensaria que ele já teria vindo falar comigo até agora...";
			link.l1 = "Entendi...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "Garoto branco? Hm... não, nunca ouvi esse nome. Mas isso não quer dizer que ele não esteja por aqui – por acaso é minha obrigação conhecer toda a ralé local?";
			link.l1 = "Não, não. Tudo bem, vou perguntar para outra pessoa.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "The island is divided between the Narwhals, Rivados and my pirates, with a neutral area between us.\nI control the San Augustine and Tartarus.\nRivados hold Protector, which is their leader's residence, Fury, their barracks, and Velasco, their warehouse. Strangers are forbidden to pass, you must say a special password in order to get there.\nNarwhals hold a lot of ships: Esmeralda is a shop and the residence of their leader; the San Gabriel and Phoenix, run by some kind of scientist; and the Ceres, their smithy.\nEvery ship except the Esmeralda is a restricted area; you must say a password before they let you in. Same goes for the Rivados. And the passwords change every week.\nThe rest of the ships are considered neutral territory, and are where the citizens live.\nWho am I forgetting...? Oh, the Fleuron is a tavern run by a man named Sancho Carpentero, and the Gloria is the local church - Brother Julian is the pastor there.";
			link.l1 = "É muita coisa pra lembrar... Acho que vou ter que conhecer a cidade andando por ela.";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "Se metendo com os clãs. Mas já que você não é durão o bastante pros Narvais nem tem a cor certa pros Rivados, vá até uma velha fragata chamada Caroline e procure um gordo chamado Giuseppe Fazio. Ele é uma espécie de diplomata por aqui. Não sei o que ele fazia antes de chegar na ilha, mas o homem é um canalha de verdade. Faz negócio com todo mundo. Os clãs usam ele como mediador, então sempre tem as senhas da semana. Fazio é tão ganancioso que comeria a si mesmo por um único doblão. Você pode pedir a senha atual tanto do território dos Rivados quanto dos Narvais, mas esteja pronto pra pagar em ouro.";
			link.l1 = "Caroline... Fazio... tudo bem, obrigado.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexter tem um. Ele é meu imediato. Fez um mapa detalhado logo que chegamos. Sobe lá e fala com ele, vê se ele te vende.";
			link.l1 = "Entendi. Valeu!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ha! Um troféu de Alan Milrow, chefe do clã Narwhal.\nJurgen, o ferreiro dos Narwhal, fez isso com um ferro raro que encontraram no fundo do mar. Não enferruja, nunca perde o fio e pode cortar dois corpos ao meio com um só golpe.\nEssa espada é uma das poucas coisas boas que saíram dessa expedição, e por isso mesmo, não me desfaço dela. Nem por todo o ouro do mundo.";
			link.l1 = "O Jurgen consegue fazer outra espada larga como esta?";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Pfft! Not likely. Jurgen is a Narwhal; he's loyal to his clan and never makes weapons for outsiders.\n Besides, you'd need some of that special iron to make a second sword. That iron can only be found at the bottom of the sea, and unless you've got gills, how are you going to reach it? So, forget about it.";
			link.l1 = "Entendo... que pena...";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = ""+pchar.name+"! Seu desgraçado maluco, ha-ha-ha, você conseguiu!! Vi suas velas no horizonte! Como vai, amigo? Como foi a viagem?";
			link.l1 = "Heh, bom te ver também, Steven. Eu sobrevivi.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ótimo! Pelos dentes de Deus, estou pronto para sair desta ilha e tomar um gole com o Diabo da Floresta.\nLayton vai ficar como Almirante - ele já tomou meu lugar, ha-ha! Acho que ele realmente gosta deste lugar.";
			link.l1 = "Você disse uma vez que muita gente que chega aqui acaba preferindo a vida na Ilha do que lá fora. Está surpreso que o Dexter não seja diferente?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "É, não diria 'surpreso'... só triste por perdê-lo. Não se encontra imediato melhor que ele.\nBem... quando pretende levantar âncora?";
			link.l1 = "Em breve. Suba no meu navio, Steven. Partiremos assim que eu terminar meus assuntos aqui.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Você é o capitão! Ah, vai ser bom sentir o balanço do convés debaixo dos meus pés de novo!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Blueweld... estranho... parte de mim achava que nunca mais veria árvores verdes e campos de novo...\n...\n ... Hã, bem... vou falar com o Svenson. Você também devia procurá-lo e conversar sobre o futuro. Dias quentes nos aguardam, hein?";
			link.l1 = "Sem dúvida, Steven. Bons ventos pra você!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Claro, vou fazer o que puder! Fala aí.";
			link.l1 = "Steve, dá uma olhada... Um dente de tubarão. Não me diga que isso te é estranho!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Você acertou, é o meu dente – ou melhor, é o dente de um tubarão que eu matei pra impressionar uma garota. Por isso me chamam de Dodson 'Tubarão'.\nPoucos conseguem fazer uma coisa dessas debaixo d’água só com um sabre, mas eu era jovem e tolo, e Beatrice Sharp era a garota mais bonita do Caribe...\nComo você conseguiu isso?";
			link.l1 = "A former executioner of St. John's gave it to me. A man was butchered with it; his name was Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Mm-hmm, you've found your butcher; I cut his throat with this tooth.\nI was heartbroken by Beatrice's death, and I believed Leadbeater to be the only guilty man within my reach.\nI found some papers on him after he'd gurgled his last that clarified a few things. He had every right to crave revenge.\nBlaze's sister was just in the wrong place at the wrong time. Mask shouldn't have been blamed for her death - he was only interested in Butcher. Truthfully... I regret murdering him.\nThat bitch Jessica set the whole thing up.";
			link.l1 = "Você ainda está com aqueles papéis?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Claro que não. Não precisei deles. Mas posso te contar por que o Máscara estava atrás do Açougueiro, se quiser saber.";
			link.l1 = "Sim, muito. Me dê tinta e uma pena, que eu escrevo tudo.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Certo. Então escute. Joshua Leadbeater era um capitão britânico no comando da fragata Neptune, que depois virou lenda...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... no entanto, Leadbeater sobreviveu e foi salvo por um navio que passava - embora tenha ficado desfigurado pelos ferimentos.\nDesde então, passou a usar uma máscara, e encontrar e punir o responsável por suas desgraças tornou-se o objetivo de sua vida.";
			link.l1 = "Entendi... tudo bem, acho que anotei cada palavra. Vou reler depois. É uma história triste. Você conhecia a Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sure! She accompanied Butcher on all his voyages until he dumped her for Beatrice. Jess never forgave him.\nThey called her Butcher's talisman, because as long as she was with him, she brought him luck.\nAs soon as he left her on Barbados, his business went bad; the booty dried up and the Neptune became a frequent guest at the Isla Tesoror shipyard. Though that can be better explained by the fact that Butcher spent all his time in his cabin with Beatrice instead of on his quarterdeck.\nBeatrice wasn't like Jessica: she didn't crave adventure and battle- though Nicolas taught her fencing and seamanship. She was a romantic, wasn't hard enough to be a pirate.\nThis life wasn't for her, and in the end, it killed her.";
			link.l1 = "E o que dizer da Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, she was something! Every sailor on the Neptune obeyed her orders without question, and not just because she was the captain's girl.\nJess was a master fencer and navigator - learned everything she knew from Butcher, and even exceeded him. She was tough and fearless, and blessed with looks that would make angels blush.\nA lot of men wanted her, but she only wanted Butcher. Chasing her was risky; she was likely to reward unwanted interest with a free fencing lesson, and for many, it was the last they ever received.\nJess owned a very special sword, the only one of it's kind in the Caribbean. I have no clue where she got it. The flame-bladed sword. The slightest touch of its blade leaves the most terrible wound.\nJess was an adventurer - not by birth, but by vocation. If you want to learn more about her, there's a friend of yours can tell you much more about her than.";
			link.l1 = "Sério? E quem é esse homem?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson.\nOld Forest Devil will never admit it, but he had plans for Jessica. This was just after he'd claimed the Spanish Main for himself and his fame was known throughout the Caribbean, so he figured the tigress was as good as his.\nAfter Butcher got rid of Jess, Jan started visiting Barbados on a regular basis. That set the Englanders' nerves on edge; as you know, Jessica was the daughter of a Bridgetown planter.\nWe all knew what he intended, and we knew it could end very badly, but we didn't say anything. Jan may sit on his arse in Blueweld these days, but speak the slightest ill of him back then and he'd turn up at your door with a poison blade and a band of hard buccaneers, he he...\nJan's plans came to naught: Jess couldn't live with the way Butcher treated her, so she took her revenge a year later with a help of Mask.\nIn the end, her vengeance destroyed her, along with Mask, Beatrice, and Butcher.";
			link.l1 = "O Açougueiro ainda está vivo.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "... Besteira...";
			link.l1 = "Steven, o Capitão Butcher ainda está vivo. Jacob Jackman e Henry o Carrasco fizeram uma visita ao carrasco. O enforcamento foi forjado. Eu tenho provas.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Falsificado... Então, onde está o Açougueiro agora?!";
			link.l1 = "He calls himself Lawrence Beltrope now, and he lives in Port Royal. He's still dangerous though; Jackman, who caused so much trouble for the Brethren, was acting under Butcher's command.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Maldição! O imediato finalmente se reuniu com seu capitão!\nBeltrope, você disse... espere! Agora entendo por que havia um registro estranho de um interrogatório entre os papéis do Blaze... Parece que o Blaze também descobriu sobre o Açougueiro-Beltrope...";
			link.l1 = "Do que você está falando?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Depois que assumi esta residência, revirei os velhos papéis do Blaze. Encontrei o registro de um interrogatório de um tal Samuel Brooks.\nHavia menção às 'aventuras de Thomas Beltrope', e que ele era conhecido como pirata e grande amigo de Nicolas Sharp!\nParece que Thomas era o pai do Açougueiro.";
			link.l1 = "Interessante... parece que os filhos de Sharp e Beltrope continuaram o trabalho dos pais...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Parece que sim... Mas me diga, meu amigo, por que você está tão interessado nos feitos dos mortos?";
			link.l1 = "Preciso de documentos — documentos que comprovem que Helen MacArthur é filha de Beatrice Sharp e que ela tem todos os direitos sobre a herança. Não me importa que ela também seja filha do Beltrope.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Não tem nada sobre a Helen MacArthur nem nos papéis do Leadbeater, nem nos arquivos do Blaze.\nÉ estranho a Beatrice não ter contado ao Blaze sobre o nascimento da sobrinha dele, isso não é do feitio dela...";
			link.l1 = "Escuta, será que tem mais alguma coisa nos papéis do Sharp? Eu preciso de cada detalhe!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, I guess... According to Blaze's notes, he'd been trying to find the island where his sister died.\nThere're papers concerning Leadbeater's punitive expedition... Nothing interesting, except for latitude numbers.\nThis parallel crosses the northern Caribbean sea. But there's no longitude.\nObviously, Blaze's search failed; you can't imagine how many small islands there are along that latitude.";
			link.l1 = "Me diga os números.";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Vamos ver... aqui: latitude 21 graus 32 minutos Norte.\nMas não vejo pra que serve sem a longitude.";
			link.l1 = "Deixe isso comigo. Obrigado, Steven, pela sua história. Até a próxima!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "You could say that. Now, about Tortuga.\nThe island was named such because it resembles a turtle. Well, Levasseur's been thickening turtle's shell for twelve years.\nHis crowning achievement is Fort La Roche. A frontal attack is suicidal; the fort's heavy cannons can smash even ships-of-the-line.\nMaking a soup out of this beauty won't be easy. The Spanish have been trying for a very long time and they've not yet succeeded.";
			link.l1 = "O Svenson me prometeu ajudar a derrubar o Levasseur. Ele disse que você teria um plano, então qual é?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "I've had men walking the streets of Tortuga for the last few weeks and they've obtained a lot of interesting information. I have good news for you, pal: it seems you won't have to face the cannons of La Roche. We're not the only ones fed up with Levasseur; he has friends who want him dead.";
			link.l1 = "Continue...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Todo mundo sabe que o Levasseur gosta de meninas jovens. Depois que ele se diverte, elas somem.  O principal fornecedor de escravos em Tortuga é Robert Marten, do galeão Voltigeur. O parceiro dele, Henri Thibaut, sobrinho do Levasseur, escolhe as garotas mais bonitas do porto para o tio.  Não faz muito tempo, Marten conseguiu uma bela moça de um brigue inglês chamado Molly Jones. Ele entregou a garota para o Thibaut, sobrinho do Levasseur, à noite, num grotão secreto em Tortuga.  Contaram para a tripulação que a menina morreu de ataque do coração e jogaram o corpo no mar, mas é claro que aquele corpo devia ser de alguma pobre prostituta do porto que eles pagaram e depois mataram.  No fim das contas, parece que Marten e Thibaut decidiram ficar com a Molly só pra eles, em vez de entregar para o Levasseur. Se o Levasseur descobrir, vai dar uma confusão dos diabos.";
			link.l1 = "Are you sure we can exploit this? I'm sure Marten and Thibaut realize the risk they're running; they'll have taken precautions.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "Verdade. Mas toda corrente tem um elo fraco.\nTrês dias atrás, um ex-tripulante do Voltigeur chamado Fernand Lucas bebeu demais na taverna de Basse-Terre e falou coisas bem interessantes...\nAcontece que Molly Jones pediu pra ele pedir ajuda ao irmão dela em St John's. Mas Lucas nunca chegou até ele.\nEle fugiu do capitão e agora está em Guadalupe, bebendo pra esquecer a própria covardia.\nAntígua não é um lugar seguro pra piratas franceses — lembre-se disso! O coronel Fox jurou pendurar um em cada palmeira da ilha depois que a esposa dele morreu nas mãos de um corsário francês, e os fuzileiros dele vão fazer de tudo pra cumprir essa promessa.";
			link.l1 = "Fique atento, Steven... Me conte sobre Marten e Thibaut. Por que eles arriscariam tanto? Os encantos da Molly eram mesmo tão fortes, ou esses mercadores de escravos resolveram mostrar um pouco de misericórdia, só dessa vez?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "I know that scum Marten very well. If he's taking this risk, that means there's either gold or self-preservation involved.\nMaybe Marten thinks he can get a huge ransom for her - which is unlikely; the girl arrived on Tortuga in servant's garb.\nOr maybe... Ha! I wonder who Marten would be more afraid of than Levasseur...?";
			link.l1 = "Hum... me conte mais sobre o Thibaut.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Não sei muito sobre o homem, só que Levasseur confia nele o bastante para torná-lo seu herdeiro.\nNinguém sabe ao certo onde a garota está presa, nem por que Thibaut dá tanta liberdade ao Marten, mas desvendar esse mistério pode nos dar a vitória sem precisarmos invadir Tortuga. Você é francês, então imaginei que preferiria assim.\nMas é melhor se apressar, nunca se sabe quando as baboseiras bêbadas do Lucas vão chegar a um navio rumo a Tortuga, e se Levasseur souber disso antes de agirmos... estamos ferrados!";
			link.l1 = "Vou partir imediatamente.";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "Here's what you do: visit Antigua first. Molly sent Lucas there to find her brother; maybe the brother has information that can help you.\nAfter that, get your arse to Guadaloupe. Find Lucas and learn everything you can about Marten, Thibaut, Voltigeur, and Molly.";
			link.l1 = "Obrigado, Steven. Antígua, depois Guadalupe.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "Continue!";
			link.l1 = "Encontrei o irmão da Molly em St. John's. É o escrivão do Coronel Fox. Mas tem algo estranho... Ele descreveu a irmã, Molly, como uma velha conhecida, mais ou menos da sua altura – mas nem de longe tão bonita. Ela é criada da filha do Fox, Catherine, e estava com ela na Inglaterra até pouco tempo atrás...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "Quanto à Catherine, ela realmente é conhecida por sua beleza e estava indo visitar o pai no aniversário dele, mas o esquadrão que a levava acabou se atrasando...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "O coronel Fox proibiu que ela deixasse a Inglaterra sem uma esquadra de escolta, então Molly Jones não pode ser prisioneira de Thibaut. Então quem ela é...?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... Maldição, não faço ideia. Talvez ela seja outra Molly Jones – não aquela de quem você anda perguntando.\nMas... são coincidências demais. Não acredito que seja tudo acaso!\nSabe... tenho uma suspeita, mas...";
			link.l1 = "O que você quer dizer? Fale logo!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "... E se Catherine desobedecesse as ordens do pai e partisse sem escolta? O mês passado foi bem tempestuoso, o Albatross pode ter se danificado e virado presa fácil para o Marten.\nSuspeito que Catherine escondeu seu verdadeiro nome do Marten – dá pra entender o motivo – e usou o nome da Molly no lugar!";
			link.l1 = "Maldição! Se for esse o caso, então tudo faz sentido... mas é uma baita suposição!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "É isso que eu quero dizer, camarada. Posso estar enganado, mas...";
			link.l1 = "... mas se for verdade, isso muda tudo! Podemos pedir apoio aos ingleses, deixar as baionetas dos Raposas do Mar abrirem caminho para nós!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Calma, "+pchar.name+"! We need proofs. As I said, I could be wrong, and Catherine could still be in London, waiting for an escort to set sail.\nThe English have problems of their own; they won't risk attacking La Roche. But if we're right, and Colonel Fox finds out what's happened to his daughter...\nHe'll set up a blockade around Tortuga and wait for reinforcements. Then he'll attack the city. Sea Foxes are fearsome in close-quarters, so there'll be lots of casualties - army and civilian.\n And in the end, I'm sure he'll raise the English flag above the ruins of Tortuga three days later. Do you really want that?";
			link.l1 = "Não... não, eu não vejo. Agora entendo de que resgate o Marten está falando.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "Precisamos ser cautelosos. Nem sabemos ao certo se Marten tem conhecimento da verdadeira identidade da Catherine. Chantagear o Coronel Fox seria suicídio, ainda mais com o esquadrão de Cromwell chegando ao Caribe. Se Catherine morrer por nossa culpa, estaremos completamente ferrados. O Coronel Fox poderia acabar com a Irmandade da Costa se achasse que fomos nós que matamos a filha dele. Mas se, no fim das contas, Catherine tiver que morrer, precisamos garantir que não pareça coisa nossa, e que ela nos ajude a alcançar nossos objetivos. O melhor desfecho seria entregar a garota ao pai dela. Quem salvar a filha será muito bem recompensado, he-he...";
			link.l1 = "Steven, você é um gênio! Estou indo para Tortuga. Vou confirmar se Molly é Catherine Fox.";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Não perca tempo, "+pchar.name+". E se eu estiver certo, garanta que aquela garota continue viva.";
			link.l1 = "Vou fazer tudo o que puder.";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ho-Ho! Fala logo, amigo! Vamos resolver qualquer problema, pode apostar!";
			link.l1 = "Vou direto ao ponto, então. Você conhece Miguel Dichoso?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Eu conheço ele. Aquele don espanhol me vendeu um navio e tanto – uma fragata. Ah, que embarcação era aquela, só de lembrar...";
			link.l1 = "Deixa eu adivinhar, casco único, dezesseis nós de velocidade máxima? 'Santa Quiteria'?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Você está certo sobre o casco e a velocidade dela, mas o nome era outro – 'San Martin'. Paguei a ele uma fortuna em ouro, foi tudo o que eu tinha. Todas as minhas economias foram direto para os bolsos daquele canalha.";
			link.l1 = "Tem certeza de que o nome dela era San Martin e não Santa Quiteria? E quando você a comprou? E por que está chamando ele de canalha?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Tantas perguntas! Vou responder todas na ordem: tenho certeza de que era San Martin. Eu mesmo ajudei os homens do Alexus a arrancar aquela tábua com nome de papista da popa. Eu a batizei de 'Fortuna' — um nome muito mais digno para uma princesa dessas. Comprei ela pouco antes do Blaze Sharp ser assassinado, no inverno de 1654. Por que chamei o Miguel daquele jeito? Porque aquele filho da puta conseguiu roubar o navio da base militar espanhola em Providence. A gente armou um belo espetáculo pra eles, bem na frente do forte de San Juan. Sacrifiquei dois lugres meio mortos só pra deixar a briga mais convincente. Queimamos e afundamos os barcos, simulando uma batalha com a fragata. E quando a noite caiu — levamos o San Martin pra Ilha da Justiça... Fiquei com o navio e o Dichoso ficou com o dinheiro. Ele contou pros chefes dele que a fragata tinha sido afundada numa batalha com piratas, e o comandante de San Juan confirmou a história.";
			link.l1 = "Então é assim que os fidalgos espanhóis enchem os bolsos! Que canalha! Me diga, isso aconteceu mesmo no inverno de 1654? Ou talvez na primavera? E a fragata foi danificada pelas tempestades?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "No inverno... Droga, não tenho certeza absoluta – pode ter sido na primavera também. Na verdade, não lembro direito. A fragata não estava danificada, era novinha em folha. Parecia recém-construída. Quando penso nela, só me dá vontade de chorar de raiva...";
			link.l1 = "Por quê? É, e onde está a sua bela fragata agora?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Porque ela se foi de mim. Armaram pra cima de mim, colocaram meu talismã no corpo do Blaze e espalharam que fui eu quem o matou. Depois ouvi dizer que Marcus Tyrex – nosso guardião do código – ia me marcar com o sinal negro. Então decidi sumir daquele caos por um tempo na Ilha da Justiça, onde você acabou me encontrando\nNão consegui chegar lá com uma fragata, então deixei ela com o Pastor Negro em troca de uma escuna cheia de mantimentos, não tinha muito dinheiro depois do meu trato com aquele esperto do Dichoso. Eu esperava vender os mantimentos e voltar pra Isla Tesoro em um ou dois meses... Bem, você sabe o resto.";
			link.l1 = "E o Pastor Negro não esperou por você, então ele a vendeu";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Exatamente. Ela foi comprada por um inglês, ou melhor dizendo, por um escocês, William Paterson. Eu até poderia tentar trazer a garota de volta, claro, mas esse montanhês é um sujeito perigoso, capitão da Marinha Real e grande amigo do coronel Fox. Além disso, ele fazia negócios com Jackman do mesmo jeito que você fazia com Svenson\nO escocês tem um esquadrão... dane-se, nunca mais vou ver meu navio.";
			link.l1 = "Entendi. Você sabe onde está esse Dichoso agora?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Não faço ideia. Nunca mais o vi depois que comprei minha Fortuna.";
			link.l1 = "E por que o Miguel não tentou vender para outra pessoa? E o Tyrex, Barbazon, Sharp? Ou o Paterson?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Não faço ideia. Pelo que me lembro, o Paterson não estava aqui naquela época. Zachariah, Jacques e Marcus jamais teriam concordado e eu... Eu gostava mesmo daquela fragata!";
			link.l1 = "Eu entendo que... na verdade, não entendo nada. Quebra-cabeças por toda parte...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Querendo cavar o passado de novo? Qual ilha você quer conquistar desta vez? Ha-ha-ha!";
			link.l1 = "Existe uma ilha... Mas ainda não descobri como chegar lá. Tudo bem, Steven, obrigado pela informação! Até logo!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Boa sorte, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "E eu fico feliz em te ajudar, como sempre. O que você quer desta vez, "+pchar.name+"?";
			link.l1 = "É de novo sobre o seu velho amigo Miguel Dichoso. Fiquei sabendo que ele foi visto na Ilha Tesoro outra vez. Você não pode me ajudar a encontrá-lo?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ô, amigo, na verdade eu não sabia disso. Não vi ele por aqui. Não vejo ele desde que comprei a 'Fortuna' dele. E por que você precisa desse don espanhol?";
			link.l1 = "Eu preciso dele. Miguel conhece o caminho para uma antiga cidade indígena. Estou realmente ansioso para chegar lá.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Como sempre, meu amigo, você vai acabar se metendo em confusão. Infelizmente, não posso te ajudar. Meu conselho é dar uma volta pela vila e perguntar por aí, talvez alguém tenha visto ele. Ele é bem conhecido por aqui, sabe.";
			link.l1 = "Ei, Steven, você pelo menos pode me dizer como ele é?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Bem, ele tem uns vinte e cinco, vinte e oito anos, mais ou menos da sua altura, olhos escuros, sem peruca. Tem uma cicatriz de sabre na bochecha direita.";
			link.l1 = "Hm. Sabe, tem muita gente que se encaixaria nessa descrição.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Não há outros detalhes únicos sobre ele. Ele é autoconfiante, insolente e muito perigoso. Já circularam boatos sobre ele...";
			link.l1 = "Entendi. Tudo bem, vou perguntar sobre ele por aí. Boa sorte, Steven!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Veio ao lugar certo! Fala logo!";
			link.l1 = "Tem um sujeito que não tem medo de piratas. Ele não nos leva a sério. Precisa aprender uma lição sobre respeito. Lembre-se, não mate ele.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Ora, ora! Se não é o velho Charles! Aposto que você se meteu em outra encrenca de novo! Vamos aos detalhes, quem é o alvo desta vez e o que vamos ensinar pra ele";
			link.l1 = "Um convidado da Europa, um inspetor do Ministério das Finanças da França – o barão Noel Forget. Ele quer fundar uma Companhia de Comércio Francesa aqui, mas eu e um grande amigo meu somos contra isso. Tentamos convencer o Barão de que negociar aqui seria muito arriscado por causa dos holandeses, ingleses e, principalmente, dos piratas depois que Levasseur foi derrotado, mas ele não nos ouviu. Precisamos fazer ele sentir medo, para que entenda o perigo na própria pele.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Sim, sim... Um barão de verdade!.. Vamos atacar o navio dele?";
			link.l1 = "É o seguinte: o navio dele vai partir de Port-au-Prince para Capsterville em breve. Você precisa interceptar o Barão depois que ele zarpar e capturá-lo como refém. Seria melhor não afundar o navio nem matar a tripulação. Os franceses são nossos aliados, afinal. Acha que consegue dar conta disso?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Bem, não posso prometer nada. Mas vou tentar. Que navio é esse?";
			link.l1 = "Uma brigue chamada 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Uma brigue não é páreo para minha fragata. Vamos acabar com eles facilmente. Se se renderem, deixo todos vivos.";
			link.l1 = "Perfeito. Espalhe o medo e ofereça a eles a chance de se render. Depois, mande o Barão para o porão infestado de ratos. Tente encontrar o lugar mais imundo que conseguir, mas não o deixe lá por mais de um dia, senão ele pode adoecer e morrer. Depois acomode-o na cabine, vá para a Ilha da Justiça e tranque-o em algum lugar isolado. Vista alguns dos seus homens como mercadores franceses capturados e faça-os agir como tal. Durante três dias seguidos, eles devem contar a ele tudo sobre como os piratas cruéis os perseguem, roubam, exigem resgates, torturam... com todos os detalhes necessários.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! Esse deve ser o trabalho mais divertido que aceitei em muito tempo! Muito bem, vou encontrar esses atores, camarada. Pode apostar, depois das histórias deles, seu barão vai se borrar de medo! Eles vão mostrar cicatrizes de sabres e de vergalhões em brasa... ";
			link.l1 = "Mandou bem. Depois, você vai obrigá-lo a escrever uma carta para Poincy, pedindo resgate. Três milhões e quinhentos mil por um figurão desses nem é tanto assim.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Ótimo. O que vamos fazer agora?";
			link.l1 = "E então você vai levar o Barão para Turks. Lá, você receberá o resgate e me entregará o Barão. E além disso, deve avisar que todos os franceses vão pagar por Tortuga e Levasseur.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! Essa foi boa demais! Nós mesmos, bem, você sabe o que fizemos com o Levasseur, e agora... ha-ha-ha!.. Beleza, camarada. Vai ser feito! Você disse que o navio vai chegar logo?";
			link.l1 = "Em breve. Precisamos ficar de olho.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Não se preocupe , eu não vou te decepcionar. Vou cuidar disso pessoalmente. Quando ouvir boatos de que esse barão foi capturado, venha até mim.";
			link.l1 = "Ótimo. Obrigado, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Claro, camarada. Como combinado. Histórias assustadoras sobre piratas cruéis, massacrando mercadores franceses inocentes. O som de chicotes, gemidos e gritos. Braseiro com carvão e algemas queimadas. Do jeito que tem que ser.";
			link.l1 = "Calma aí! Segura a onda. Eu preciso dele vivo.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Não se preocupe, ele vai sobreviver. Ele escreveu essa carta com a mão trêmula. Aqui está.";
			link.l1 = "O que está escrito aí? Ele está implorando para o Poincy tirar ele daqui?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Mandou bem, camarada! Ele tá implorando!";
			link.l1 = "Jogue esta carta fora, ou melhor ainda – queime-a. Vamos nos encontrar em Turks daqui a uma semana. Tem que parecer que precisamos de tempo para juntar o resgate.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Entendido. Daqui a uma semana, no golfo do norte. Não esqueça de levar o dinheiro: isso tem que parecer bonito. Depois, venha até mim, vamos resolver isso.";
			link.l1 = "Claro, até um ouriço-do-mar teria percebido isso. Até mais! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Ei, comedor de rãs! Pare!";
			link.l1 = "Eu não vou sair daqui.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Aqui está seu barão. Um pouco acabado, mas inteiro. É ele?";
			link.l1 = "Sim.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfeito. Agora, entregue o dinheiro ou ele está acabado! E nem pense em nos enganar, estamos de olho em você!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Aqui.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Maldição! Esqueci isso no navio...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Você é esperto, francês. Pegue sua santidade. E diga ao Poincy que ele deve preparar o dinheiro: todos esses bastardos franceses vão ter que pagar pelo que vocês fizeram com o Levasseur e com Tortuga. E seus mercadores vão nos pagar com suas mercadorias e navios. Ha-ha-ha! Não se esqueça de trazer mais barões para o arquipélago, eles nos dão muito lucro! Ha-ha-ha!";
			link.l1 = "Por favor, vá até o meu barco, Barão.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "E nem pense em nos perseguir, capitão. Você sabe quem eu sou. Tenho mais prisioneiros franceses, e se eu não voltar pra casa a tempo, meus homens vão matar todos eles. Entendeu?";
			link.l1 = "Chegará a hora em que vamos acertar as contas com vocês, malditos blasfemos!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Você está tirando com a minha cara?";
			link.l1 = "Um minuto, vou trazer...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Steven, o que foi que seu idiota fez agora!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, o que você estava fazendo? Cadê o dinheiro? Eu não avisei aos meus rapazes que isso não era pra valer... e aí esse idiota achou que você queria enganá-los...";
			link.l1 = "Que pena! O Barão está morto... O que será que Poincy vai fazer agora?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "Olha, camarada, a culpa é sua, espero que entenda isso. Talvez, no fim das contas, isso até seja melhor pra você.";
			link.l1 = "Que idiota eu sou! Estraguei tudo. Tá bom, vou pra Poincy... Me perdoa por ser um imbecil, Steven, até mais.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Você precisa descansar, está perdendo o jeito. Venha me ver qualquer hora, eu te arranjo um pouco de rum e umas moças bonitas.";
			link.l1 = "Obrigado, vou te fazer uma visita quando puder.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "De nada, camarada. Pra mim, isso foi a coisa mais divertida que fiz esse ano! Rimos demais, eu e meus rapazes!.. Então quero te agradecer por isso. Aqui está o seu dinheiro.";
			link.l1 = "Você deveria ficar com uma parte para você.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Esqueça. Fiz isso pela nossa amizade. A Irmandade da Costa te deve muito mais, e mesmo assim você não pediu nem um doblão.";
			link.l1 = "Ainda assim, aceite pelo menos cinquenta mil pelos serviços e pela compensação. Obrigado, Steven! Fico feliz por ter te conhecido naquela estranha Ilha da Justiça dos navios perdidos.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "E eu também. Charles, venha me visitar quando tiver um tempo!";
			link.l1 = "Com prazer!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Você está atrasado uma semana! Eu não contei pros meus rapazes que isso não era pra valer... ! Eles se recusaram a esperar mais e decidiram acabar com o seu barão!";
			link.l1 = "Que idiota eu sou! Estraguei tudo! O que vou dizer para o Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Bem, camarada, a culpa é sua, espero que entenda isso. Talvez, no fim das contas, isso seja até melhor pra você.";
			link.l1 = "Tá bom, eu vou pra Poincy... Me perdoa por ter sido um idiota, Steven, até mais..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "Você precisa descansar, está perdendo o jeito. Venha me ver qualquer hora, eu arranjo um pouco de rum e belas moças pra você";
			link.l1 = "Obrigado, vou te fazer uma visita quando puder.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "Interessante, fiquei curioso. Bem, vamos dar uma volta.";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "Por todos os diabos! Não acredito no que vejo! É mesmo ela? Me diga, é ela? Essa é a 'Fortuna'?!";
			link.l1 = "Sim, meu amigo, seus olhos não te enganam. É ela mesma. Sentiu falta dela?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "Ha ha ha, eu não acredito nisso! Mil diabos! Mas de onde você tirou isso?";
			link.l1 = "De um certo escocês chamado William Paterson. Sim, sim, daquele que comprou do Pastor Negro.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "Não é possível... E então, ele te vendeu a 'Fortuna'? Um navio tão lindo? Depois que você já tinha comprado?";
			link.l1 = "Hehe, bom, quase isso. Digamos assim: a gente não se deu nem um pouco bem, e eu peguei o navio como compensação pelos custos que tive por causa do nosso conflito. De qualquer forma, ele não precisa de navio.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "Você me surpreende ainda mais ... Ele é um capitão militar a serviço da Inglaterra. O esquadrão dele na colônia pode saquear quem quiser. Nem eu tive coragem de bater de frente com ele. E como você lidou com isso? Conseguiu arrancar a 'Fortuna' do esquadrão dele?";
			link.l1 = "Não, o esquadrão afundou. Na verdade, não foi fácil. A batalha foi séria, mas aconteceu longe de lugares habitados, e só meus marinheiros e oficiais estavam entre as testemunhas. No geral, não tenho medo de perseguição pelas autoridades britânicas. William Paterson simplesmente sumiu durante mais uma aventura qualquer ...";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "Caramba... Já tinha perdido as esperanças de ver minha andorinha de novo. Bem, espero que este navio te sirva fielmente. Fico realmente feliz por você, amigo!";
			link.l1 = "O quê? Você não precisa dele? Eu queria devolver isso ao verdadeiro dono...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "Ha-ha-ha, meu amigo, fique com a 'Fortune' para você. Primeiro, você é o dono legítimo dela. Conquistou honestamente na batalha. Não é certo abandonar o navio depois disso. E segundo, eu já tenho uma nova embarcação. Claro, quando comprei a 'Fortune', nunca imaginei que um dia trocaria por outra. Mas, como eu já não esperava vê-la de novo, encomendei uma nova fragata com o Alexus. E sabe de uma coisa... Ela ficou incrível. Ouvi dizer, e nesse caso você teve parte nisso, ha ha!";
			}
			else
			{
				dialog.text = "Ha-ha-ha, meu amigo, fique com a 'Fortune' para você. Primeiro, você é o dono legítimo dela. Conquistou honestamente em batalha. Não é certo abandonar o navio depois disso. E segundo, já estão construindo um novo navio para mim. Claro, quando comprei a 'Fortune', nunca imaginei que um dia trocaria por outro. Mas, como já não esperava vê-la de novo, encomendei uma nova fragata ao Alexus. Mal posso esperar para pisar no convés dela.";
			}
			link.l1 = "Bem, então não me resta outra opção a não ser ficar com este belo navio para mim, Steven!";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "Exatamente. Só te peço uma coisa: cuide da 'Fortuna'. Acredite, você não vai encontrar um navio como esse em nenhum outro lugar. Ele é único. E eu o amo como uma lembrança. Ficarei feliz em saber que meu amigo é dono desse navio, e não algum canalha.";
			link.l1 = "Está bem, Steven. Eu prometo que vou proteger a 'Fortuna'.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "Sim, e mais uma coisa...";
			link.l1 = "Ouvindo.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "Já que agora você tem a 'Fortuna', quero te propor um negócio.";
			link.l1 = "Estou te ouvindo MUITO atentamente.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "Como eu disse, Alexus está construindo uma nova fragata pra mim. Claro que ele dificilmente vai superar a 'Fortuna' em velocidade, mas também não vai ficar muito atrás. E justamente por isso eu preciso de uns dois navios poderosos, mas rápidos. Eu até poderia dar conta sozinho, mas dois são bem melhores.";
				link.l1 = "Ótimo. E que tipo de negócio é esse?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "Como eu disse, Alexus recentemente construiu uma nova fragata pra mim. Claro, é difícil que ela supere a 'Fortuna' em velocidade, mas também não vai ficar muito atrás. E justamente por isso eu preciso de alguns navios poderosos, mas rápidos. Talvez eu consiga fazer isso sozinho, mas dois é bem melhor.";
				link.l1 = "Ótimo. E que tipo de negócio é esse?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "É cedo demais para falar sobre isso, porque ainda não sei quando meu novo navio vai sair do estaleiro. Alexus parece estar tendo alguns problemas para conseguir os materiais. Aliás, se tiver oportunidade, você poderia ajudá-lo. Tenho certeza de que ele vai pagar bem: dei a ele um adiantamento generoso. Depois que ele conseguir todos os materiais, acho que em um mês meu navio estará pronto. Então estarei esperando por você. Mas venha com o 'Fortuna' e prepare-o com antecedência, porque depois o tempo vai ser curto! Ah, e certifique-se de que os espanhóis não estejam querendo ver sua cabeça numa bandeja de prata. Depois te conto todos os detalhes.";
			link.l1 = "Bem, vou perguntar ao nosso construtor naval de que ajuda ele precisa. E então voltaremos a conversar daqui a um mês, depois que eu ajudar o Alexus, quando você já estiver navegando de novo.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "É cedo demais pra falar disso, porque meu navio nem saiu do estaleiro ainda. Ainda preciso equipá-lo. Então, espero você não antes de um mês. Mas venha na 'Fortuna' e prepare tudo com antecedência, aí vai sobrar pouco tempo! Ah, e cuide pra que os espanhóis não queiram ver sua cabeça numa bandeja de prata. Depois te conto todos os detalhes.";
			link.l1 = "Certo, então voltamos a conversar depois, quando você estiver navegando de novo.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "Tá bom, então. Agora vou pra residência, se não se importa. As coisas, como dizem, não esperam.";
			link.l1 = "Até logo, Tubarão! Não vou me despedir.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "A minha está pronta, e a sua? Eu te disse para vir na 'Fortune'. Não sei onde você a deixou, mas é arriscado demais apostar tudo em outro navio. Então estou te esperando no navio que combinamos. E não aperte demais.";
				link.l1 = "Droga, esqueci completamente, seu canalha! Espera aí: já volto para o navio certo.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Charles, eu disse pra você vir sem esquadrão. Pro assunto que quero tratar com você, navios extras não servem pra nada. Leve sua flotilha pra outro lugar e volte.";
				link.l1 = "Sim, eu tinha esquecido completamente. Espere: já volto, e sem esquadrão.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ah, aí está você, amigo! Finalmente! Já estava começando a me preocupar. Meu navio está quase pronto. Agora mandei ele para Tirax: ele vai equipá-lo com os canhões de trinta e dois calibres que pegou do galeão pesado que capturamos no mês passado. Já fui com ele até os turcos e voltei, e devo dizer que Alexus fez um trabalho excelente. Aliás, ainda não escolhi um nome decente pra ele, embora tenha algumas opções. Pode me ajudar a escolher?";
			link.l1 = "Claro que vou ajudar! Seja qual for o nome que você der ao navio, é assim que ele vai navegar, não é? Quais são as suas opções?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Até agora, decidi por três opções.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "A primeira opção é 'Fantasma'. A fragata é rápida e poderosa, e com esse nome, todos os avarentos de Havana até Cumaná vão tremer só de ouvir falar dela!";
			link.l1 = "É, e você também precisa aparecer e sumir na neblina pra fazer os marujos até se benzerem, ha ha! Bom nome, gostei.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Eu também gosto. A segunda opção é 'Tubarão'. E daí? Por que não dou um apelido pro meu navio também? Vamos ser xarás, eu e ele, ha!";
			link.l1 = "Tem um tubarão no 'Tubarão'... Irônico. Mas todo mundo vai saber exatamente quem é o dono do navio.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Aqui estou mais ou menos igual. E a terceira opção é 'Rajada'. Pra fazer todo mundo ter medo até de chegar perto do meu navio, ha ha ha!";
			link.l1 = "Porque você pode ser pego por uma saraivada de balas vindo de lado? E daí, não é tão ruim.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Exatamente! Mas agora não consigo decidir entre esses três nomes. Então vamos lá, me ajuda. Como quiser.";
			link.l1 = "Eu sugiro chamar de 'Fantasma'. Assim, todos os mercadores vão hastear a bandeira branca assim que te virem no horizonte!";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "Eu gosto do nome 'Tubarão'. Todos devem saber que este navio não é de um novato, mas sim do próprio chefe da Irmandade da Costa!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "Acho que 'Flurry' é um bom nome. Qualquer guerreiro, corsário ou mercador deveria saber o que vai acontecer se decidir enfrentar este navio.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "Olha só – até os militares vão começar a fazer igual, ha! Então está decidido. Segura a caneca, amigo. Vamos brindar ao meu novo navio. Ao 'Fantasma!'";
			link.l1 = " Pelo 'Fantasma!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "E que pensem três vezes antes de cruzar meu caminho! Então, está decidido. Segure a caneca, amigo. Vamos brindar ao meu novo navio. Ao 'Tubarão'!";
			link.l1 = "Por 'Tubarão'!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "E se ele ainda insistir, vai ser engolido por uma tempestade tão feroz que até furacão vai parecer brisa! Então, está decidido. Segure a caneca, amigo. Vamos brindar ao meu novo navio. Ao 'Flurry!'";
			link.l1 = "Por 'Flurry!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "E que este navio sirva fielmente e nunca conheça o amargor da derrota! Bem, agora ao que interessa.";
			link.l1 = "Estou te ouvindo com atenção.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Me diga, Charles, você sabe o que é a 'Frota Dourada'?";
			link.l1 = "Kha-kha! .. Já até engasguei com o rum. Steven, não me diga que você está com duas fragatas para atacar o comboio mais bem armado do Caribe.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "Bem, não, claro, não sou suicida. Nós definitivamente não vamos assaltar o comboio inteiro. Mas aqui a gente pode pegar alguma coisa dali.";
			link.l1 = "Steven, me desculpe, de verdade, mas não estou pronto pra isso. Os espanhóis vão nos queimar vivos se a gente se enfiar na frota deles! Vai sem mim.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "Certo, onde não sumimos... Estou pronto pra participar!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "Argh! Que pena. Eu sou perigoso demais sem você. Tudo bem, não vou insistir agora, mas pense nisso, certo? Se algum dia mudar de ideia, me avise.";
			link.l1 = "Se eu fizer isso, tudo bem. Desculpa, Steven.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Essas empreitadas não desistem! E você? Mudou de ideia, talvez?";
			link.l1 = "Não, amigo, me desculpe, mas ainda vou recusar.";
			link.l1.go = "exit";
			link.l2 = "Certo, onde não sumimos... Estou pronto para participar!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Você pode estar pronto, mas seu navio não está. Eu te disse para vir na 'Fortune'. Não sei onde você a deixou, mas é arriscado demais apostar tudo em outro navio. Então vou te esperar no navio que combinamos. E não exagere.";
				link.l1 = "Droga, esqueci completamente, desastrado! Espera aí: já volto pro navio certo.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Mas não: você ainda não está pronto, Charles. Eu disse pra você vir sem esquadrão. No caso que quero tratar com você, navios extras definitivamente não são necessários. Leve sua frota pra outro lugar e volte.";
				link.l1 = "Sim, eu me esqueci completamente. Espere: já volto, e sem um esquadrão.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Mil demônios, era exatamente isso que eu queria ouvir! Então, sugiro que a gente pegue uma parte daquele comboio. Tem muito saque...";
			link.l1 = "Roubar, você quer dizer? Sem ser pego pelos navios de patrulha?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Exatamente. Olha, como você provavelmente sabe, a 'Frota de Ouro' se reúne em Porto Bello e de lá segue para Havana. Depois de Havana, já não adianta tentar interceptá-la: ela cruza o Atlântico rumo à Espanha com uma escolta tão forte que só um completo idiota se arriscaria a enfrentá-la. No momento da travessia de Porto Bello para Havana, a situação não é muito melhor. Claro, você pode tentar, mas pra isso precisa reunir uma esquadra capaz de quebrar fortalezas como se fossem nozes. Mas em Porto Bello, navios chegam de todo o Maine, e lá eles já não estão tão protegidos assim.";
			link.l1 = "Só que agora o horário da travessia e os nomes desses navios são totalmente confidenciais. Não vamos ficar vagando por Porto Bello por meio ano esperando interceptar qualquer navio espanhol que chegue ao porto.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Claro que não vamos. De Cartagena, por exemplo, os navios vão sozinhos, e, como você bem disse, só Deus sabe que tipo de navios são esses e quando vão partir. Mas de Caracas, que fica perto de uma mina espanhola e bem longe de Porto Bello, os navios não estão totalmente sozinhos.";
			link.l1 = "Como assim, não está completamente sozinho?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "Consegui descobrir que um navio carregado de mercadorias sai de Caracas sozinho ou com uma escolta pequena, mas em algum ponto na longitude do Golfo de Maracaibo, navios de guerra espanhóis o encontram para garantir sua segurança dali em diante. Como você acha que eles sabem quando e quem precisam encontrar lá?";
			link.l1 = "Devem ter contado alguma coisa pra eles...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "Certo. Antes do navio principal partir, uma embarcação mensageira vai de Caracas até Porto Bello, informando o local e a data do encontro, além do nome do navio espanhol. Depois, ela retorna levando a confirmação de que o navio será recebido na hora certa e no lugar certo. Só então, nosso objetivo com você parte de Caracas.";
			link.l1 = "Mas se interceptarmos o mensageiro, o navio em Caracas não vai receber a confirmação e não vai sair do porto. Tem alguma ideia sobre isso? E além disso, como vamos pegar o próprio mensageiro? Também não sabemos quando ele vai partir.";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "E aqui temos um pequeno problema. Os espanhóis, claro, usam lugres-correio para isso, mas é arriscado: a chance de serem interceptados pelo primeiro pirata de passagem é grande demais. Então, às vezes eles podem demorar muito para enviar o navio. Por isso, quando surge a oportunidade, eles mandam as instruções junto com navios bons, poderosos e rápidos — mercantes, por exemplo, ou corsários que seguem a rota certa.   Como se fosse uma carta lacrada. Além disso, sai muito mais barato do que mandar um navio-correio só pra isso, mesmo que seja um lugre. E os oficiais espanhóis, sempre gananciosos, adoram economizar e ainda guardar um troco no bolso, hehe.";
			link.l1 = "Acho que entendi! Preciso me tornar um mercador desses?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "Exatamente! E demos sorte: consegui descobrir por uma fonte confiável que em Caracas estão procurando justamente por um mensageiro assim para enviá-lo com uma carta nas próximas três semanas. E você tem um navio poderoso e rápido, ainda por cima construído pelos espanhóis! Tire uma licença GVIK, para dar mais credibilidade — já faça logo por seis meses, compre uma boa quantidade de mercadorias em Caracas para revender com lucro em Porto Bello, e então vá até o chefe da autoridade portuária local e pergunte se precisa levar algo no caminho.  Se a Autoridade Portuária perguntar, diga que é espanhol. E mais uma coisa — nem pense em levar um esquadrão junto. Não precisamos chamar atenção demais, senão toda a empreitada pode ir por água abaixo.";
			link.l1 = "E pelos documentos que eles vão me entregar, vou descobrir a data e o local do encontro do navio com o comboio?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "Não é tão simples assim. Estou te dizendo: os documentos estão lacrados. E você não pode abri-los sozinho. Eles só serão abertos na autoridade portuária de Porto Bello, e então eles vão redigir uma resposta e, se você for gentil o bastante para dizer que está voltando para Caracas, vão pedir para você levar a resposta até lá. A resposta, claro, também estará lacrada.";
			link.l1 = "E como eu vou descobrir então o lugar e a data do encontro?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "Você vai ter que ser esperto e dar um jeito de espiar isso... Por exemplo, no momento em que abrirem os documentos em Porto Bello e estiverem escrevendo a resposta. Ou simplesmente roubar quando te entregarem a confirmação, que você vai precisar levar para Caracas. Mas essa não é uma boa opção: depois disso, tudo pode dar errado.";
			link.l1 = "É difícil, claro... Mas acho que dou conta do recado.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "Eu, por minha vez, vou pegar meu navio de volta do Marcus e esperar por você ancorado perto do Cabo Santa Maria, em Curaçao. Quando terminar, é só vir até mim. Interceptamos o navio nas coordenadas indicadas e, em seguida, caímos fora dali o mais rápido possível. Agora entende por que precisamos de navios poderosos, mas rápidos? Não quero brigar com o esquadrão militar espanhol de jeito nenhum. Você vai ter que despistar eles.";
			link.l1 = "Entendi. Então, estou indo embora. Me encontre no Cabo Santa Maria!";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "Isso mesmo, nos encontramos lá. Boa sorte, amigo! Tomara que nosso negócio dê certo.";
			link.l1 = "Também espero. Enfim, estou indo.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "Maldito Charles! Achei que nunca mais fosse te ver! Onde você esteve? Esperei por você no lugar combinado, mas você nunca apareceu. E não tive nenhuma notícia sua.";
			link.l1 = "Desculpe, Steven. Não consegui cumprir minha tarefa.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "Ah, deixaram escapar um peixe desses ... Tudo bem, não fique chateado. Da próxima vez você dá mais sorte.";
			link.l1 = "Espero que sim.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", mas que diabos? Eu te disse pra vir sem esquadrão! Entenda: não precisamos de peso morto, senão toda a operação pode ir por água abaixo! Não sei o que deu em você, mas assim não vai rolar. Manda logo sua caravana pra outro lugar e volte com um só navio. Tô te esperando aqui.";
				link.l1 = "Sim, só achei que isso era mais provável... Tudo bem, entendi você. Espere aqui: já volto!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", mas que diabos? Eu te mandei ficar na 'Fortune'! Entenda: precisamos de dois navios rápidos e poderosos, senão toda a operação pode ir por água abaixo! Não sei o que deu em você, mas assim não vai funcionar. Troque logo essa sua canoa pela 'Fortune' e volte. Estou te esperando aqui.";
				link.l1 = "Sim, só achei que este navio é melhor ... Tudo bem, entendi você. Espere aqui: já volto!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "E aí está você, meu amigo! Então, o que acha do meu belo?";
			link.l1 = "Belíssima fragata, Steven! Eu não recusaria isso...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "Não, agora você tem 'Fortuna', haha! Então, me conte como foi.";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "Deu tudo certo: consegui me passar por um comerciante honesto e confiável. Levei os documentos para Porto Bello, onde consegui distrair o chefe da autoridade portuária por cinco minutos e anotei para mim a data e as coordenadas do encontro dos navios com a carga e o esquadrão militar.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "Houve algumas pequenas complicações. A carta foi enviada para Porto Bello por um mensageiro. Eu a interceptei, entreguei ao destinatário e até consegui uma resposta, mas o chefe da autoridade portuária percebeu que eu não era a pessoa que deveria trazer os documentos. Tive que sair de lá na base da força. Mas consegui descobrir a data e as coordenadas do encontro do navio com a carga e o esquadrão militar, e entreguei a resposta em Caracas, então a produção está nos esperando!";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "Espera aí. Você disse 'navios'?";
			link.l1 = "Sim, Tubarão! Serão dois deles!";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "Ha-ha-ha, sim, vamos ficar ricos! Bem, minha fera está pronta para enfrentar seu batismo de fogo. Mas ainda não participou de batalhas, então vamos liderar o combate. Por enquanto, vou me juntar ao seu esquadrão.";
			link.l1 = "Eu vou comandar ninguém menos que Steven Dodson, chefe dos Irmãos da Costa? Que honra!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "Bem, não se ache demais: é só porque vou lutar no meu navio pela primeira vez. E trate de garantir que haja oficiais livres para cuidar dos navios-prêmio. Porque os porões vão estar lotados, e nenhum dos meus homens vai conseguir comandar o navio sozinho... Chega de papo furado. O saque está esperando por nós!";
			link.l1 = "Exatamente! Estou indo para o meu navio.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "Sim, você herdou ... Então precisamos nos preparar para o fato de que o esquadrão vai chegar lá antes da data combinada, e teremos que lutar com todo mundo de uma vez.";
			link.l1 = "Por que você diz isso?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "E você pensa. Em Porto Bello eles sabem que o navio com a carga vai mesmo sair de Caracas, porque você levou a carta de volta pra lá. Mas como você se entregou, eles vão fazer de tudo pra impedir que a gente intercepte esse navio. Acho que o esquadrão vai chegar lá antes. É o que eu faria. Então, vamos nos preparar pra uma briga feia. Se recuar, vai ser tarde.";
			link.l1 = "Não se preocupe. Você e eu somos dois lobos do mar, nós já passamos por coisa pior!";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "Sua verdade. Bem, minha fera está pronta para passar por um batismo de fogo. Mas ainda não participou de batalhas, então deixe que você lidere o combate. Enquanto isso, vou me juntar ao seu esquadrão.";
			link.l1 = "Eu vou comandar Stephen Dodson em pessoa, o chefe da Irmandade da Costa? Que honra!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "Sem tempo pra conversa, "+pchar.name+"! Vamos atrás do saque!";
			link.l1 = "E que a sorte esteja do nosso lado!";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "Mil diabos! Excelente trabalho, Charles! O saque acabou sendo muito mais valioso do que eu imaginava! Acho que essa viagem valeu muito a pena.";
				link.l1 = "Concordo totalmente com você, Steven! Hoje é definitivamente o nosso dia!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "Bom trabalho, amigo. Mas temos que admitir que perdemos muitas presas.";
					link.l1 = "Concordo, Steven, poderíamos fazer melhor. Mas o que temos também está bom!";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "Droga! Era uma ideia tão boa... E no fim, as despesas dessa campanha foram maiores que os lucros. Charles, eu realmente te dei o comando, e você conseguiu perder tudo!";
					link.l1 = "Não diga nada... Eu mesmo estou uma fera. Quanta presa escapou das minhas mãos!..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "Bom, nós dois fizemos um ótimo trabalho. Eu bolei o plano e consegui as informações sobre o mensageiro, e você executou tudo com maestria. E nós dois lutamos de igual para igual pela nossa presa. Portanto, proponho que dividamos conforme as leis dos Irmãos da Costa: igualmente!";
			link.l1 = "Vamos fazer isso!";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "Bem, agora estou de partida para Isla Tesoro. Preciso consertar o navio e celebrar direito a primeira viagem bem-sucedida na minha nova embarcação. Boa sorte, amigo! Sempre fico feliz em te ver na minha residência!";
			link.l1 = "Fico feliz que nosso negócio tenha sido tão lucrativo. Com certeza vou te visitar algum dia. Boa sorte!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "Tudo bem, fique com tudo pra você. Se é que sobrou alguma coisa. Não me importo com esses pequenos. No fim das contas, fui eu que te meti nessa história toda.";
			link.l1 = "É, eu também errei... Desculpa, Steven.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "Não peça desculpas, ainda te devo a minha vida, e não vou esquecer disso. Agora estou de partida para a Ilha Tesoro. Precisamos consertar o navio e dar uma lavada nele... Embora, lavar o quê, né... Boa sorte, camarada! Sempre fico feliz em te ver na minha residência!";
			link.l1 = "Certo, qualquer coisa pode acontecer, derrotas acontecem. O importante é que estamos vivos. Com certeza vou te visitar algum dia, amigo! Boa sorte!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
