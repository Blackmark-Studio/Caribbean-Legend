// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Um bug óbvio. Avise os desenvolvedores sobre isso.";
			link.l1 = "Ah, eu vou.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Oh, olá monsieur! Bem-vindo a Tortuga! Capitães tão nobres quanto você são raros por aqui...";
			link.l1 = "Saudações, mademoiselle. Agradeço pela calorosa recepção. Mas como assim? Achei que um porto tão importante sempre fosse frequentado por cavalheiros de fortuna muito mais nobres do que eu.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ah, monsieur... Você é claramente um recém-chegado, estou certa? Logo vai perceber. Você não faz ideia de como é difícil encontrar homens à altura para um baile no palácio do governador. Quem sabe você me acompanha...?";
			link.l1 = "Como posso ser útil a uma mulher tão bonita?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "Meu Deus, quanta gentileza! (risos) Quem sabe você não nos faz uma visita às seis horas hoje à noite? A esposa do governador costuma organizar encontros informais nos aposentos dos criados do palácio. É raro termos companhia interessante nesses eventos. Vai nos visitar? Por favor, venha, ficaríamos realmente encantadas.";
			link.l1 = "Seria uma honra, mademoiselle. Farei uma visita a você esta noite.";
			link.l1.go = "girl_3";
			link.l2 = "Perdoe-me, mademoiselle, mas tenho assuntos urgentes para resolver. Quem sabe em outra ocasião?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Que pena. Vou ter que encontrar outra pessoa para fazer companhia para mim e minhas amigas... Adeus.";
			link.l1 = "Adeus.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Muito obrigado! Eu te prometo, esta será uma noite inesquecível, monsieur! Au revoir!";
			link.l1 = "Até mais...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Olá, marinheiro! Que vento de sorte trouxe você aqui hoje? Raramente vemos homens tão distintos em Tortuga.";
			link.l1 = "Olá para você também, mademoiselle, seus elogios quase me fazem corar. Sou capitão do meu próprio navio e um homem ocupado, mas tenho certeza de que esta ilha tem o suficiente para manter um aventureiro como eu bem entretido.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(risadinha) Ah, sim, senhor, tenho certeza de que podemos ajudar com isso! Tortuga sempre tem algo a oferecer. E eu também... Ora, sou capaz de fazer quase *qualquer coisa* depois de ouvir uma boa história do mar. Eu adoro essas histórias! Um capitão uma vez me contou uma lorota sobre como conseguiu escapar de ser abandonado numa ilha deserta fazendo uma jangada com tartarugas marinhas. Que valentia! E você, conseguiria?";
			link.l1 = "Eu poderia o quê?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(risos) Você conseguiria fazer uma jangada com tartarugas marinhas?";
			link.l1 = "Eu posso te contar algo ainda melhor. Uma vez, quando era um aprendiz fugitivo, capturei o navio mais rápido da Marinha Inglesa usando só um machado. Também consigo prender a respiração por dez minutos. Quer ver?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Talvez mais tarde. Trabalho como criada no palácio do nosso governador. Vá até lá hoje à noite, por volta das seis, e encontre a mim e minha amiga no jardim. Aí você pode nos contar tudo sobre suas aventuras...";
			link.l1 = "Parece um convite para mostrar e contar que eu não posso recusar. Te vejo às seis da noite.";
			link.l1.go = "girl_9";
			link.l2 = "Invadir o palácio do governador? Isso é ousado demais pra mim. Vou deixar passar, querido. Me encontra na taverna se quiser a companhia de um homem de verdade. Yo ho ho!";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Ah, tanto faz. Vou encontrar um homem melhor e maior que você então. Seu braguilha parece pequena demais, afinal. Já vai tarde.";
			link.l1 = "Até um navio de guerra pareceria pequeno navegando pelo seu Estreito do Vento.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Estou ansioso por isso!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Ah, aí está você! Capitão "+GetFullName(pchar)+"! Que alegria conhecê-lo, faz tempo que não recebo a visita de alguém com tanta nobreza e prestígio!";
			link.l1 = "É uma grande honra e um prazer estar aqui na sua companhia, madame. Mas e os outros convidados? Cheguei cedo demais?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Ah, eles estão indispostos e não podem vir. Mas não ligue para eles, vamos beber vinho e conversar... Ah, se você soubesse como me sinto entediada e sozinha aqui! Tortuga é um antro imundo cheio de canalhas, malfeitores e piratas! Piratas! E finalmente, um verdadeiro cavalheiro na minha casa! Queria tanto que meu marido fizesse mais negócios com homens do seu nível e talento! Mas não, só piratas, piratas por toda parte! Você ouviu falar dessa nova moda que está ficando popular em Paris, na corte do Rei? O que acha disso?";
			link.l1 = "Desculpe, minha opinião sobre o quê exatamente? Piratas? Ou moda?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Oh senhor, você me entende tão bem! Nem consigo acreditar nisso. Meu marido me dá umas moedinhas enquanto ele ganha MILHÕES com os piratas dele, pode imaginar? Piratas! Tenho que mandar entregar vestidos aqui nesse buraco imundo, mas quando chegam já estão seis meses fora de moda! Como é que uma mulher do meu nível pode usar esses trapos? Ah, como eu queria ver e vestir as roupas de Paris! Você acha que eu ficaria linda com elas?";
			link.l1 = "Madame, você está realmente encantadora. Não precisa de roupas de Paris para isso, já é evidente para qualquer homem nesta bela ilha.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "Você é bondoso demais comigo... Capitão, preciso confessar, estou com um grande problema. Mas você vai ajudar uma pobre mulher, não vai?";
			link.l1 = "Certamente, madame. O que desejar.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "Cuidado aí, monsieur capitão, ou eu vou perder a cabeça! (risadinha coquete) Meu marido não me deu um centavo sequer ultimamente. Aquele bruto leva prostitutas para nossa casa e nem liga para mim!\nEu sei onde ele esconde parte do dinheiro sujo dele, está num baú no escritório. Esse dinheiro é meu por direito de esposa e de mulher. Me ajude a pegar o que ele me deve e você será recompensado... Com ouro e... outras delícias.";
			link.l1 = "Que proposta interessante. Muito bem, senhora, vou ajudá-la. Onde está esse baú e como faço para abri-lo?";
			link.l1.go = "wife_5";
			link.l2 = "Muito bem, madame, vou conseguir o conteúdo do baú para você. Vamos pegar o dinheiro e depois teremos uma 'conversa' bem agradável juntos. Que homem recusaria uma proposta dessas? Onde está esse baú e como faço para abri-lo?";
			link.l2.go = "wife_6";
			link.l3 = "Madame, está tentando me seduzir. Sinto muito, mas minha honra exige que eu recuse sua oferta. Tem minha simpatia, você merece mais, mas vai ter que encontrar outro ator para sua peça.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Pena. Então não temos mais o que conversar, monsieur. Vá embora e lembre-se: se contar uma palavra disso ao meu marido, vai se arrepender!";
			link.l1 = "Adeus.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Eu não esperava isso de você... O baú... Deixe para depois, primeiro precisamos encontrar a chave duplicada que foi roubada por um pirata imundo. Ele está se embriagando agora mesmo em uma espelunca local, bebendo como um porco. Vá rápido e traga a chave duplicada de volta para mim. Estarei esperando por você.";
			link.l1 = "Então não temos tempo a perder!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Você não vai se arrepender disso, capitão. Primeiro, precisamos encontrar uma chave duplicada que foi roubada por um pirata imundo. Ele está se embriagando agora mesmo em um antro local, bebendo como um porco. Vá rápido e traga a chave duplicada de volta para mim. Estarei esperando por você.";
			link.l1 = "Então não temos tempo a perder!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Capitão "+GetFullName(pchar)+"! Ora, ora! Que homem é esse nos meus aposentos privados! Está surpreso? Você é o único convidado aqui esta noite. (risadinha)";
			link.l1 = "Estou surpreso, senhora. Mas não me incomodo nem um pouco. Trata-se de negócios ou de prazer?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "Que abordagem direta! Gosto de homens assim. Tenho uma proposta de negócio para você, capitão. Vou encontrar uma forma de recompensar seus esforços se for bem-sucedido.";
			link.l1 = "Pode continuar.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ah... Meu marido tem um baú cheio de dinheiro e joias. Eu o odeio, e quero uma mesada maior pelos meus aborrecimentos.";
			link.l1 = "Madame, você está deslumbrante. Não precisa de mais joias ou modas de Paris para isso, já é óbvio para qualquer homem em Hispaniola.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "Você é bondoso demais comigo... Capitão, preciso confessar, estou em grande apuro. Vai ajudar uma mulher em dificuldade?";
			link.l1 = "Claro, madame. A honra exige isso. O que desejar.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "Cuidado aí, monsieur capitão, ou vou acabar perdendo a cabeça! (risadinha coquete) Meu marido não me deu um único centavo ultimamente. Aquele bruto leva prostitutas para dentro da nossa casa e nem liga para mim!\nEu sei onde ele esconde parte do dinheiro sujo dele, está em um baú no escritório. Esse dinheiro é meu por direito de esposa e de mulher. Me ajude a pegar o que ele me deve e você será recompensado... Com ouro e... outros prazeres deliciosos.";
			link.l1 = "Certo. Eu vou fazer isso. Onde está esse baú, e como eu abro ele?";
			link.l1.go = "wife_13";
			link.l2 = "Ha! Isso aí não é problema, eu faço isso por uma mulher como você. Não vai se arrepender, minha querida. Vamos pegar o dinheiro e aproveitar juntos. Onde está esse baú, e como eu abro ele?";
			link.l2.go = "wife_14";
			link.l3 = "Não eu, madame. Não sou um cavalheiro a ponto de cornear e roubar um homem na mesma noite. Pelo menos, não desse jeito. Procure outro ator para essa peça.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Oh... Estou gostando cada vez mais de você... Primeiro, precisamos recuperar uma chave duplicada que foi roubada por um pirata imundo. Ele está se embriagando em uma espelunca local, bebendo como um porco. Vá rápido e traga a duplicata para mim. Estarei esperando.";
			link.l1 = "Sem tempo a perder então!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Mantenha a calma, monsieur, haverá tempo de sobra para isso depois. (risadinha) Primeiro, precisamos recuperar uma chave duplicada que foi roubada por um pirata imundo. Ele está se embriagando numa espelunca local, bebendo feito um porco. Vá rápido e traga a duplicata para mim. Estarei esperando por você. Tem certeza de que consegue dar conta disso?";
			link.l1 = "Não duvide de mim, já estou a caminho.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Seu puritano de merda! Sai da minha frente! E nem pense em contar isso pro meu marido, senão vai se arrepender!";
			link.l1 = "Tchau, querida.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Capitão! Conseguiu a chave?";
			link.l1 = "Sim, eu tenho. Onde está o baú?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "Oh! Será que meu marido miserável finalmente vai ter o que merece? Você é um homem incrível, capitão! Tem um grande futuro pela frente, sabia? Esqueça o baú. Eu mesma resolvo isso. Venha me ver amanhã para receber sua recompensa. Não vai se arrepender, capitão...";
			link.l1 = "Tudo bem. Faça do seu jeito. Estou ansioso para te ver amanhã.";
			link.l1.go = "wife_17";
			link.l2 = "Não, sou um homem ocupado e não quero perder tempo esperando. Pra que esperar? Diga logo o que precisa ser feito e eu faço. Não posso deixar uma mulher tão bonita estragar essas mãos delicadas mexendo com fechadura e chave.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Venha me ver às seis horas, meu bravo cavaleiro...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Tem certeza? Pode ser perigoso pra você. Por que quer arriscar a vida assim, capitão?";
			link.l1 = "Tudo bem. Faça do seu jeito. Estou ansioso para te ver amanhã.";
			link.l1.go = "wife_17";
			link.l2 = "Já tomei minha decisão. O que exatamente devo fazer?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "Um coração de leão!... Vá até o escritório do meu marido, você vai encontrar o baú lá. Use a chave reserva. Ninguém está lá em cima a essa hora da noite, então vá com calma. Dentro daquele baú... há diamantes. Muitos diamantes. Pegue todos e volte para mim. Estarei esperando. Não traia minha confiança... por favor.";
			link.l1 = "Eu volto já.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh, capitão! Eu... Você... Já terminou? Ah, e quem é esse?! A-ah!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "Meu Deus! Capitão, você me salvou! Você... você é o meu herói! Era o capanga do meu marido, ele queria te matar! Eu implorei para ele não fazer isso! Você está ferido? Trouxe os diamantes?";
			link.l1 = "Ha. Sério? Seu marido é um homem ciumento... Tanto faz. Que se dane ele, eu tenho coragem.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh capitão! Eu... Você... Já terminou?";
			link.l1 = "Houve uma pequena complicação, mas já está resolvido. Por que está pálida, madame? Está tudo bem? Eu trouxe as joias, isso deve animá-la, não é?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Graças a Deus! Fui vingada! Meu cavaleiro! Quantos diamantes havia?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Seu cavaleiro voltou da aventura com um saco cheio de tesouros. Ele vai deixar metade para sua dama, assim ela pode comprar as melhores roupas de Paris. Cumpri minha promessa a você.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Ah, tinham muitos diamantes, mas você não vai receber nada. Você contratou um assassino para me matar, sua putain! Acha mesmo que eu dividiria com você depois de tudo isso? Se abrir a boca sobre isso, seu marido vai descobrir o seu plano de roubá-lo e traí-lo. Então é melhor ficar calada.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "Canalha! Desgraçado! Você não vai se safar dessa!";
			link.l1 = "Ah, já ouvi essa antes.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Você não é como... os outros. Você consegue o que quer. Tem um futuro brilhante pela frente. Eu sei que você é um homem ocupado, mas... fica comigo por um tempo? Ninguém vai nos incomodar, eu prometo.";
			link.l1 = "Sempre tenho tempo para uma mulher tão bonita quanto você. Quer que eu abra uma garrafa do vinho do seu marido?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Acho que posso viver sem eles. Existem muitas maneiras de gastar dinheiro por aqui. Tantos homens bonitos e interessantes em Tortuga... Obrigada por tudo, capitão. Só para você saber, por favor, não conte nada sobre esse caso ou meu marido vai mandar te enforcar num cadafalso. Ele não é um homem bom. Adeus.";
			link.l1 = "Assim mesmo? Foi uma experiência instrutiva. Adeus, senhora, sugiro que também guarde silêncio sobre isso, eu também não sou um homem bom. Mas você já sabe disso, não é?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "Quem é você e o que está fazendo aqui?";
			link.l1 = "O que você está tentando fazer? Nós tínhamos um acordo...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "Que acordo, monsieur? Sou uma mulher casada, não faço negócios com outros homens! Saia dos meus aposentos agora ou chamarei meu marido e os guardas dele!";
			link.l1 = "Assim mesmo, hein? Muito bem, então acho que vou esclarecer o seu bom marido!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Saia agora, seu insolente, ou meus homens vão jogá-lo no calabouço do Forte La Roche! Não me importo com suas ameaças! Fora daqui!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Quem é você? Ah, tanto faz. Não confie em mulher, camarada. Como diz a Bíblia... até a mais tola das rameiras pode te arrastar pro fundo do Inferno com as artimanhas dela. Senta aí, parceiro, toma um gole!";
			link.l1 = "Com prazer!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "O que você está olhando? Sirva logo!!";
			link.l1 = "Um brinde a você!.. Olha, amigo, não vou perder tempo aqui. Preciso daquela chave reserva que está com você, sabe do que estou falando. Me entrega e cada um segue seu caminho: você continua bebendo e eu continuo ajudando donzelas em apuros.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Poxa, camarada! Você não ouviu nada do que acabei de dizer! Deve parecer mais esperto do que realmente é... trabalhando praquela vadia. Sabe quem é o marido dela? Recentemente, o governador Levasseur mandou o negro de confiança dele, Kampacho, pra 'conversar' com um comerciante local muito respeitado. O sujeito espancou o coitado até a morte na própria loja! Esse comerciante só tinha mostrado um pequeno desrespeito à esposa do governador durante um baile ou algo assim. E essa mesma desgraçada me seduziu com o olhar e com os dobrões dele\nA chave duplicada existe. Eu era um arrombador decente lá na França, então foi brincadeira de criança. Se não fosse pela filha do comandante de Lyon... eu nunca teria virado pirata. Bah! Dane-se!";
			link.l1 = "Isso tudo é muito triste, mas vamos falar de negócios. Onde está a chave?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Está ouvindo? Estou fora desse jogo, camarada! Fui esperto o bastante pra perceber o que estava por vir! Vou embora daqui de uma vez assim que meu navio estiver pronto pra zarpar. Quer a chave, pague por ela. Não seja mão de vaca agora, acho que logo você não vai mais precisar de dinheiro.";
			link.l1 = "Sabe, você tem razão. Não quero ser brinquedo de mulher nenhuma. Obrigado pelo conselho, e se cuida no mar!";
			link.l1.go = "pirate_4";
			link.l2 = "Pagar por isso? Pra você? Você é um ladrão patético e um covarde. Devia ter ficado naquele buraco, Lyons. Vai saber, talvez o comandante de lá tivesse pena de você e deixasse um ladrão degenerado ser seu genro. Mas de mim você não vai ter pena nenhuma, pode ter certeza. Pode me entregar a chave do jeito fácil ou do difícil, a escolha é sua.";
			link.l2.go = "pirate_5";
			link.l3 = "(suspiro) Quanto?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Garoto esperto, essa é a escolha certa, camarada. Boa sorte. Espero que um dia encontre uma mulher de verdade, que te ame de verdade. De preferência uma ruiva ou uma loira, não é mesmo?";
			link.l1 = "Adeus, camarada...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Você me insultou! Saque sua espada, seu desgraçado!";
			link.l1 = "Vamos ver como você consegue arrombar cofres sem braços!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "Você é um homem de negócios, isso eu reconheço. Talvez você realmente consiga. Cinquenta doblões. Em cima da mesa.";
			link.l1 = "Cinquenta moedas de ouro? Por um pedaço de lata? Me poupe. Coloque a chave na mesa. Agora.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Que preço... Tudo bem. Fique com eles.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Que preço... Tudo bem. Vou trazê-los em breve. Fique aqui.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Trouxe cinquenta doblões?";
			link.l1 = "Sabe, acho que você pode viver sem eles. A chave. Está na mesa.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "É. Pode levar.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Eu ainda estou recebendo eles.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Vamos dançar?";
			link.l1 = "Eu vou na frente.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ótimo. Use a cabeça e talvez saia dessa com umas moedas de oito e a cabeça no lugar. Pegue a chave e ouça meu conselho. De graça. A mulher do Levasseur é mais burra que peixe, mas se acha esperta. Não confie nela. Segure a onda e fique de olho nos seus bolsos. Ela não é grande coisa, só tome cuidado e não envolva o marido dela nisso. Mais uma coisa – tem um baú no quarto dela onde guarda suas bugigangas, fácil de abrir. É lá que ela vai deixar a parte dela. Você me ouviu. Boa sorte no mar, irmão. Lembre-se, irmãos antes das mulheres.";
			link.l1 = "Boa sorte, camarada...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "Droga! Eu não esperava por isso... que se dane aquela mulher! Meu mestre me avisou pra ficar longe de gente assim. Mas trabalho é trabalho. No fim das contas, eu vou te pegar.";
			link.l1 = "Pois é, camarada... Parece que ela queria passar a perna em nós dois, não posso dizer que estou surpreso. Pra que continuar brigando? Quer um trabalho? Tenho um pra você. Você tem habilidade, preciso de homens como você na minha tripulação. Comida, cama, salário fixo, rum e uma parte justa de qualquer saque. Te dou minha palavra sobre isso. O que me diz?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "Você tem lábia e sua fama te precede, capitão, isso eu admito. Certo, estou dentro. Qual é o nome do seu navio?";
			link.l1 = "'"+pchar.ship.name+"'. Fale com o contramestre, ele vai te arrumar um beliche. Bem-vindo a bordo!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Ha! Estou subindo na vida. Dá um chute naquela vadia por mim.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
			dialog.text = "Você fala bonito. Mas não o bastante se quiser que profissionais de verdade entrem para o seu bando. Lembre-se disso para o futuro. Se é que vai ter um.";
			link.l1 = "Tente. Seja rápido, tenho um compromisso com uma dama.";
			link.l1.go = "mercen_5";
			link.l2 = "Hoje não tem segunda chance. Sou um homem ocupado, então vamos evitar sujeira no tapete. Não te pagam o bastante pra morrer por alguma putain de quinta categoria. Se é que te pagam alguma coisa.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "Você tem razão. Ninguém me pagou... ainda. Vou resolver isso agora mesmo. Faça o que quiser...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
