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
				dialog.text = "Saudações, "+pchar.name+". Come in; I've already been informed.";
				link.l1 = "Informado? Deve haver algum engano, Vossa Excelência. Vim relatar o sucesso da sua missão, mas vejo que não está no melhor dos ânimos.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Fico feliz em vê-lo, "+pchar.name+". Fui informado sobre suas conquistas e, mais importante, você cumpriu sua missão! Você se mostrou da melhor forma possível, e fico feliz por não ter me enganado a seu respeito.";
				link.l1 = "Posso receber uma ordem por escrito do senhor para libertar meu irmão agora?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Fico feliz em vê-lo, "+pchar.name+"Ouvi falar dos seus feitos e, mais importante, sua missão está cumprida! Mas devo dizer, esperava uma ideia mais engenhosa do que um ataque frontal. Uma pena pelos soldados franceses mortos.\nMas guerra é guerra, sempre há baixas. Você cumpriu seu dever, e fico satisfeito por ter confiado em você.";
				link.l1 = "Posso receber uma ordem por escrito do senhor agora para libertar meu irmão?";
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
					dialog.text = "Que bom ver você, Charles. Antes de tudo, permita-me parabenizá-lo por ter cumprido com sucesso a difícil missão de proteger a colônia de Saint-Pierre dos invasores espanhóis. Trabalho brilhante, meu amigo!";
					link.l1 = "Obrigado, Chevalier.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Que bom ver você, Charles. Antes de tudo, permita-me parabenizá-lo por ter cumprido com sucesso a difícil tarefa de proteger a colônia de Saint-Pierre dos invasores espanhóis. Trabalho brilhante, meu amigo! Trago-lhe mais uma oportunidade de colaborar com a Marinha. A França precisa urgentemente de oficiais como você. Espero que desta vez seja mais sensato... Pegue o patente, Capitão Charles de Maure!";
					link.l1 = "Obrigado, Chevalier. Fico feliz em ajudar o país e estou ansioso para continuar servindo!";
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
					dialog.text = "Charles, você me decepciona. Por causa das suas atitudes imprudentes, você perdeu seu patente e seu posto na Marinha Real. Não há mais espaço para qualquer cooperação entre nós. Está dispensado.";
					link.l1 = "Hmm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Fico feliz em vê-lo, Charles. Relate!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "O trabalho está feito, o resgate da colônia de San Jose foi recebido. Mas há más notícias: na batalha com o forte, o 'Eclatant' foi afundado. Eu avisei o capitão para ter cuidado, mas ele não me ouviu, e...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "O trabalho está feito, o resgate da colônia de San Jose foi recebido.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Monsieur, de hoje em diante, só entre nos meus salões vestido de maneira apropriada!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "Barão, Capitão! Que bom ver você!";
					link.l1 = "A missão está concluída, Chevalier.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", capitão. Que notícias você traz?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Os espanhóis realmente planejaram um ataque a Port-au-Prince. No extremo oeste de Hispaniola, encontramos um esquadrão inimigo poderoso. Ele foi completamente destruído. No entanto, o 'Éclatant' foi afundado.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "Os espanhóis realmente planejaram um ataque a Port-au-Prince. No extremo oeste de Hispaniola, encontramos um poderoso esquadrão inimigo. Ele foi completamente destruído.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Como está o senhor Stuyvesant?";
					link.l1 = "Everything's fine, Chevalier. The delivery was successful; here's the reply to your letter.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Charles, Barão... Já voltou?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "Não gosto dessa sua cara fechada, Charles. O que Stuyvesant disse? Fale logo!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Literalmente, ele disse: 'Diga ao Chevalier que ele não está mais no comando de Sint-Maarten. Chega dele. E quanto à inspeção do estado-mãe – que ele invente alguma coisa. Nunca foi difícil para de Poincy virar tudo de cabeça para baixo.' Depois de entregar essa mensagem, o senhor holandês me expulsou da residência. Assim terminaram nossas negociações.";
					else link.l1 = "Bem, foi isso que ele disse: 'seu senhor anda ganhando demais em Sint-Maarten ultimamente, então está na hora de controlar essa fome insaciável.' Depois disso, ele tentou me prender. Tive que abrir caminho até o navio na ponta da espada. Bela diplomacia holandesa, não?";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Capitão, estávamos esperando por você. Expliquei a situação ao barão, e ele apoiou totalmente minha decisão. Os holandeses vão pagar pela arrogância deles.";
					link.l1 = "Então é guerra?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "Então, meu amigo, vejo que você capturou o navio das Índias Orientais com a mercadoria. Excelente!";
						link.l1 = "Estou entregando o navio a você, dê ordens aos oficiais do porto, Chevalier.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "Tem alguma dúvida, Charles?";
						link.l1 = "Agora não, Monsieur. Vou indo então...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "Finalmente você chegou, Capitão! Há uma emergência em São Cristóvão!";
					link.l1 = "Um esquadrão hostil?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "Está pronto para assumir o nosso lugre de correio?";
					link.l1 = "Sou eu.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "Capitão de Maure, senhor Doily! Que bom vê-lo! A cidade inteira assistiu enquanto você dava uma lição àqueles canalhas hispano-holandeses que cobiçavam nossa colônia!";
					link.l1 = "Era meu dever, Chevalier.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Vamos começar, certo?";
					link.l1 = "Claro, Chevalier. É por isso que estou aqui.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "Fico feliz em receber o Vice-Almirante da Marinha Real da França no meu gabinete! Sim, meu amigo, você não se enganou: fui eu quem assinou pessoalmente a ordem da sua nomeação. Formalmente, ela ainda precisa ser aprovada na França, mas não tenha dúvida de que isso vai acontecer. Parabéns!";
					link.l1 = "Eu sirvo à minha nação!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "will be ready soon and"; // в зависимости от времени сколько добирался
					else sTemp = "is ready and";
					dialog.text = "Você teve sucesso em suas tarefas? O coronel Doily ficou satisfeito?";
					link.l1 = "Deu tudo certo, Chevalier. A caravana de Stuyvesant foi capturada, todos os escravos foram levados para a Jamaica, o esquadrão do coronel "+sTemp+" a caminho de Curaçao.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "Glória aos vencedores! Parabéns, parabéns, meu amigo! Você nunca deixa de me surpreender.";
					link.l1 = "Obrigado, Chevalier. Stuyvesant foi punido e está pronto para pagar indenizações, a paz foi restaurada, e Saint Martin agora pertence somente à França.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Então, meu amigo, fico feliz em vê-lo novamente. Descansou bem?";
					link.l1 = "Sim, Chevalier. Foi uma pausa muito necessária... O senhor mencionou um assunto delicado?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "Meu amigo, você deve ser um feiticeiro! Conseguiu realizar um verdadeiro feito! Nosso barão não quer mais fundar uma Companhia de Comércio aqui.";
					link.l1 = "Acredito que o único desejo dele agora é voltar para Paris.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, você soube do barão? Ele foi capturado por piratas...";
					link.l1 = "Sim, Chevalier. Infelizmente, o barão está morto. Tenho certeza disso.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, como está o seu progresso? Fiquei sabendo que o barão embarcou no seu navio...";
					link.l1 = "Sim, Chevalier. Ele estava a bordo, eu cuidava dele, mas... ele morreu de febre.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, como está o seu progresso? Disseram-me que o barão embarcou no seu navio...";
					link.l1 = "Sim, Chevalier. Ele estava a bordo, eu cuidava dele, mas... ele morreu na batalha.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "Meu amigo, você deve ser um feiticeiro! Conseguiu realizar um feito e tanto! Nosso barão não quer mais fundar uma Companhia de Comércio aqui.";
					link.l1 = "Ele provavelmente está indo para Paris agora.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "Você tem alguma pergunta, Charles?";
				link.l1 = "Agora não, monsieur. Vou indo então...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "O que deseja, monsieur?";
			link.l1 = "Nada sério, só uma visita de cortesia. Já estou de saída...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Bom dia para você, Charles. Permita-me apresentar: sou Philippe de Poincy e eu...";
			link.l1 = "Por que diabos você me colocou na prisão? Isso é um absurdo! Eu sou um nobre francês e...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "Boa... tarde? Essa foi boa, senhor. Como sabe quem eu sou?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "Jovem, peço que não me interrompa! Você está falando com o Governador-Geral das colônias francesas no arquipélago do Caribe! Vou perdoar seu tom insolente apenas porque você não poderia saber quem estava diante de você. Mas recomendo que seja mais comedido.";
			link.l1 = "Hum... Me desculpe, Vossa Graça.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "Escute-me, rapaz, e não me interrompa! Você está falando com o Governador-Geral das colônias francesas no arquipélago do Caribe! Vou relevar o seu tom apenas pela sua ignorância sobre com quem estava falando. Mas recomendo que seja mais comedido no futuro.";
			link.l1 = "Hm... perdoe-me, Vossa Excelência.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Melhor. Agora, sobre sua pergunta anterior – você foi erroneamente considerado um espião espanhol e preso até que sua situação fosse esclarecida. Esses malditos castelhanos têm ficado mais ativos ultimamente, então ordenei a detenção de todas as pessoas suspeitas. Mas agora já sabemos quem você é – você é realmente Charles de Maure, irmão de Michel de Monper, e eu mesmo desci aqui para libertá-lo. E você grita comigo como um garoto mimado!";
			link.l1 = "Perdoe-me mais uma vez, excelência. Posso ir agora?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Sim, você está. Mas quero falar com você em particular antes que o sargento abra sua cela. Você sabia que seu irmão, um dos mais valorosos guerreiros da Ordem de Malta, foi preso e está sob custódia?";
			link.l1 = "Eu só sabia que meu irmão estava em apuros e precisava de ajuda. Foi por isso que vim de Paris.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Fico feliz em ouvir isso. Quero que saiba que Monsieur de Monper está em sérios apuros. Tenho todos os motivos para suspeitar dele por abuso de autoridade, desvio de bens e falso testemunho. Mas você pode ajudá-lo.";
			link.l1 = "Monsieur, poderia me explicar melhor? Não entendo, Michel era o orgulho da Ordem e...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Eu também pensei assim. Todos nós pensamos! Mas as ações recentes dele nos deixaram... incertos quanto à lealdade dele à Ordem, então ele foi preso. O próprio Michel vai te contar os detalhes. Ele vai explicar como você pode ajudá-lo a lidar com as acusações e evitar a desonra.";
			link.l1 = "Onde está meu irmão agora? Você disse que ele estava na prisão, mas eu não o vi por aqui...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Eu disse preso, rapaz? Você está me ouvindo?! Eu disse que ele está detido! Não é a mesma coisa. Michel de Monper está sendo mantido sob custódia na base subterrânea de Saint Pierre, que pertence à Ordem de Malta.\nEu permito que você visite a base sem restrições e converse com seu irmão sempre que achar necessário. Os oficiais e soldados da Ordem estão cientes das minhas instruções e não vão te impedir.";
			link.l1 = "Onde fica aquela base subterrânea?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "Está aqui, em Saint Pierre, claro. Encontre a prisão local e entre pela porta marcada com os símbolos da Ordem. Desça até a casamata no segundo nível do porão. Monsieur Monper estará lá. Mas não se preocupe: ao sair da prisão, você será recebido e levado até seu irmão – já providenciei tudo... É isso. Espero que nos vejamos novamente, Charles. Sargento!";
			link.l1 = "Espere, excelência! E quanto aos meus... pertences? Minha espada e o resto?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "Seus pertences foram confiscados para pagar a dívida do seu irmão. Adeus, Monsieur de Maure.";
			link.l1 = "Mas que por...";
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
			dialog.text = "Aha, Charles de Maure em pessoa! Fico feliz em vê-lo. Imagino que veio conversar comigo sobre o destino do seu irmão?";
			link.l1 = "Estou pronto para pagar o que Michel de Monper deve à Ordem, e a você pessoalmente.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Hm... Mas onde está o dinheiro? Você tem um senso de humor estranho, rapaz, e eu não entendo.";
			link.l1 = "Com licença, Chevalier. Esqueci meu dinheiro no armário do navio. Já volto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "Trouxe o dinheiro, Charles?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "É claro! Espero que esta quantia cubra totalmente todas as suas despesas.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Ainda não...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Excelente! Vou ficar com eles. Você se saiu muito bem, Charles!";
			link.l1 = "Quando vou receber a ordem para a libertação de Michel de Monper?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "Não tenha pressa, rapaz. Só posso admirar que você pague as dívidas e proteja sua família arriscando a própria vida. Essa nobreza é rara hoje em dia... Mas o dinheiro não é o principal nesta triste história. Seu irmão recebeu uma quantia tão grande sob a condição de cumprir uma missão muito delicada.\nMichel de Monper, como fiel católico, jurou sobre o Livro que encontraria uma maneira de punir um herege insolente e restaurar a justiça que ele violou, para a glória da Ordem e da Santa Igreja...";
			link.l1 = "Mas ele não vai conseguir cumprir a palavra dele preso! Se o senhor soltá-lo, nós dois vamos conseguir completar a missão muito mais rápido do que se eu fizesse tudo sozinho.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Veja, meu amigo, seu irmão me deu um bom motivo para duvidar da sua decência. Não há garantias de que ele não vá fugir e quebrar sua palavra. Então, se quiser livrá-lo de todas as acusações, faça o juramento você mesmo. O Monsieur de Monper lhe explicará os detalhes.";
			link.l1 = "Hm... Eu não esperava por isso. Mas você não me deixa outra opção. Vou tomar minha decisão final depois de conversar com meu irmão.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Estou começando a gostar de você, Charles. Quem sabe um dia, talvez, possamos ser amigos. De qualquer forma, esta é a última vez que libero seu irmão. Dou minha palavra de que a reputação da sua família não será prejudicada, desde que você faça o que seu irmão não fez. E poderá contar com minha amizade no futuro.";
			link.l1 = "Eu entendo você perfeitamente. Adeus!";
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
			dialog.text = "Não se preocupe, "+pchar.name+", vou cumprir minha palavra. Seu irmão será libertado e todas as acusações serão retiradas. A reputação da sua família está a salvo agora. Eu diria que tudo isso é graças aos seus esforços, e só aos seus. Seu pai pode se orgulhar de ter criado um filho assim.";
			link.l1 = "Obrigado pelas palavras gentis, Chevalier. Posso partir para Martinica imediatamente?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Espere um momento, meu amigo. Espero que eu possa chamá-lo assim, não posso? Quero expressar minha gratidão pessoalmente. Venho acompanhando seu progresso desde que chegou aqui, e conheço a maioria dos seus feitos. Você construiu uma reputação e tanto no Caribe e, sem dúvida, é bem conhecido e respeitado em certos círculos. A França precisa de pessoas como você\nCapitão "+GetFullName(pchar)+"! Pelo poder a mim concedido por Sua Majestade, o Rei da França, tenho a honra de lhe oferecer uma patente de capitão na Marinha Real e colocar sob seu comando uma embarcação da marinha francesa, a fragata leve 'Gryffondor'!\nSeu antigo capitão, de Fontenot, se tornará governador de Tortuga graças a você, e a melhor fragata leve do Caribe precisa de um capitão. Aceita esta proposta?";
			link.l1 = "Interessante. E o que você quer em troca?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Só um pouco. Um décimo do seu saque, e de vez em quando cumprir missões delicadas. Estou aguardando sua decisão.";
			link.l1 = "Ninguém recusaria uma oferta dessas, excelência! É uma honra servir à minha nação!";
			link.l1.go = "serve_3";
			link.l2 = "Perdoe-me pela falta de modéstia, mas preciso recusar sua oferta por enquanto. Questões familiares podem exigir meu retorno imediato à pátria.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Pity. I had hoped that you would agree... But nevertheless, I am forced to ask you for one more favour; actually, it is in your interest as well. Martinique is under attack. There is heavy fighting in the port and in the city itself.\nAlas, I have no one else to send there to help the garrison but you. I ask you, as a patriot of your Fatherland, to repel the assault by any means necessary. I hope that you have enough resources to do so.\nBesides, your brother is still there; you can save his life.";
			link.l1 = "Meu irmão está em perigo? Estou a caminho!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "Palavras honrosas! Fala de um verdadeiro soldado e filho leal da Pátria! Parabéns, monsieur "+GetFullName(pchar)+". Você está sendo promovido ao posto de comandante das forças navais da França. Aceite este uniforme de minhas mãos. Use-o com orgulho e faça jus a ele!";
			link.l1 = "Eu sirvo à minha nação!";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "A pesada corveta 'Gryffondor' está sob seu comando agora. A partir deste momento, este excelente navio é seu. Use suas ótimas qualidades para a glória de Sua Majestade e para fortalecer a influência francesa no arquipélago do Caribe!";
			link.l1 = "Já vou!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Mas seu esquadrão já está grande demais, então volte pelo 'Gryffondor' quando se livrar de um navio.";
				link.l1 = "Certo. Eu vou fazer isso.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "Junto com o navio, você receberá o capitão interino e a tripulação. Se quiser, pode mantê-lo sob seu comando ou retirá-lo do navio, e nós encontraremos outro posto para ele.";
				link.l1 = "Entendi!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "Mas tenho más notícias para você, capitão. Acabei de ser informado que Martinica está sob ataque. Há combates intensos no porto e na própria cidade.\nInfelizmente, não tenho ninguém além de você para enviar em auxílio à guarnição. Aqui está sua primeira missão:\n Proteja Saint Pierre! Além disso, seu irmão ainda está lá, você pode salvar a vida dele.";
			link.l1 = "Meu irmão está em perigo? Estou a caminho!";
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
			dialog.text = "Você está pronto para assumir o comando do 'Gryffondor'?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Ainda não, estou reposicionando meus navios no esquadrão...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Sou eu.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Excelente! Além do navio, você receberá o capitão interino e a tripulação. Se quiser, pode mantê-lo sob seu comando ou retirá-lo do navio e nós encontraremos outra posição para ele.";
			link.l1 = "Entendi!";
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
			dialog.text = "E isso é só o começo, Monsieur! Tenho certeza de que você irá longe com tanto talento militar! E já tenho outra tarefa para um excelente oficial naval, que tenho certeza de que você cumprirá com a mesma competência. Além disso, ela está diretamente ligada à sua missão anterior.";
			link.l1 = "Estou ouvindo, monsieur";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Mas deixe-me primeiro apresentá-lo à pessoa que entrou no meu gabinete. Este é o Barão Noel Forget, membro honorário da Companhia Francesa das Índias Ocidentais. Ele chegou ao arquipélago para inspecionar nossas colônias, expandir a organização das plantações de cana-de-açúcar e de outras culturas, além de explorar a possibilidade de desenvolver laços comerciais em nossa região. De Paris, foi determinado que lhe demos todo o apoio e assistência possíveis nesses assuntos, o que certamente faremos. Barão, apresento-lhe o Monsieur Charles de Maure, um dos capitães mais talentosos a serviço da França...";
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
			dialog.text = "Então, Charles, enquanto o barão e eu inspecionamos Saint Christopher, atribuo a você a seguinte tarefa. Ninguém pode atacar assentamentos franceses e esperar sair impune, e os espanhóis, embora já tenham recebido uma lição pela agressão em Martinica, devem responder por seus crimes com o bolso e compensar os danos causados à colônia. Junto com o barão francês, chegou um poderoso esquadrão, composto pelo formidável navio de 66 canhões 'Eclatant'. O capitão do navio é um marinheiro experiente, mas está no Caribe pela primeira vez, então ficará sob seu comando. Junto com o 'Eclatant', você irá até as costas da ilha espanhola de Trinidad e exigirá dos espanhóis uma compensação em dinheiro no valor de trezentos mil pesos pelo ataque a Saint Pierre.";
			link.l1 = "Cavaleiro, o senhor acredita mesmo que os espanhóis vão concordar?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Tenho certeza disso – depois que o 'Éclatant' e seu esquadrão reduzirem o Forte San Jose a escombros. Desembarcar tropas e tomar a cidade, perdendo soldados, creio que não será necessário. Ataque sem aviso, destrua o forte e então envie um sinal ao comandante dizendo que deseja negociar os termos. Nessa situação, os espanhóis não terão para onde correr e vão preferir pagar. O que você faria se estivesse no lugar do governador de uma cidade sem proteção?";
			link.l1 = "Hmm, parece razoável, Chevalier.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Está claro o que você tem que fazer?";
			link.l1 = "Sim, Vossa Graça.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = " Então vá em frente. Aqui está uma carta para o capitão do 'Eclatant' confirmando sua autoridade. Este excelente navio, com sua tripulação bem treinada, está agora à sua disposição. Charles, não se esqueça de que agora você serve à França, e para se comunicar adequadamente com oficiais como eu, é aconselhável usar o uniforme. Fica perfeito em você. Boa sorte, Capitão de Maure!";
			}
			else
			{
				dialog.text = " Então vá em frente. Aqui está uma carta para o capitão do 'Eclatant' confirmando sua autoridade. Este excelente navio, com sua tripulação bem treinada, está agora à sua disposição. Ah, e Charles: vista o uniforme de capitão, é uma ordem! Primeiro, não é digno de um oficial da Marinha Real Francesa parecer um comerciante ou algum corsário, e segundo, o uniforme lhe cai muito bem. Cumpra minha ordem imediatamente, Capitão de Maure!";
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
			dialog.text = "'Eclatant' afundou? Charles, isso é uma tragédia! O que o ministro vai dizer agora? Você me decepcionou, Charles! Eu tinha certeza de que podia confiar na sua experiência, e você... Infelizmente, você será responsabilizado por isso. Vou escrever um relatório, e é melhor você sumir por um tempo. Seu serviço na Marinha Real acabou.";
			link.l1 = "Hmm... Me desculpe, Monsieur. Acho mesmo melhor eu sumir por um mês ou dois, até o ministro esfriar a cabeça. Adeus, e mais uma vez, sinto muito por ter decepcionado você.";
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
				dialog.text = "Perfeito!";
				link.l1 = "Aqui, por favor, fique com esses trezentos mil.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Perfeito, mas onde está o dinheiro, Charles?";
				link.l1 = "Hã, está no baú do navio. Vou entregar em um instante!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Então, Charles, trouxe o resgate de Trinidad?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Sim, Monsieur. Aqui está.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "Vou trazer em um instante!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Estou satisfeito com você, Charles, você nunca me decepciona. A tarefa não foi fácil, e você receberá uma quantia de 50.000 pesos do valor do resgate como recompensa. Pegue, é toda sua.";
			link.l1 = "Meu agradecimento, Chevalier.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Já tenho uma nova tarefa para você. Monsieur Forget concluiu a inspeção em Saint Christopher e agora deseja visitar nossas colônias do norte. Peço que leve o barão até Tortuga e Hispaniola, ajude-o em tudo que precisar e atenda aos seus pedidos. Está claro, Charles?";
			link.l1 = "Claro, Chevalier.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "O Barão está com pouco tempo, então peço que não se distraia com outros assuntos e não demore mais de dois meses na viagem.";
			link.l1 = "Claro, Monsieur. A viagem entre as ilhas não leva muito tempo, a menos que os assuntos do Monsieur Forget nas colônias sejam demorados.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Perfeito. Então o Barão viajará no seu navio. Dê a ele a melhor cabine disponível.";
			link.l1 = "Claro, Chevalier!";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "And one more thing, Charles: you're without your officer's uniform again! This is your last warning. From this moment onwards, I ask you to come to me only in uniform; otherwise, I will not listen to you. You are on duty, and discipline should be everything, especially in the appearance of a naval officer!";
			link.l1 = "Me perdoe, Chevalier. Isso não vai acontecer de novo.";
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
			dialog.text = "Eu não tinha dúvidas de que sua jornada seria bem-sucedida. Alguma novidade de Tortuga ou de Port-au-Prince?";
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
			link.l1 = "Sim, Chevalier, trago notícias, mas não são muito agradáveis. Primeiro, o governador de Port-au-Prince tem certeza de que os espanhóis estão preparando um ataque à colônia e, para isso, estão reunindo um esquadrão militar em... hm, como se chama mesmo... em Santiago, isso. E não parece ser apenas boato. Acredito que não podemos ignorar esse assunto, ainda mais porque as plantações de Port-au-Prince estão entre as melhores que já vi.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Os espanhóis estão se preparando para atacar Port-au-Prince? Hmm... Muito bem. Vamos lhe dar instruções para lidar com isso, Capitão Charles de Maure. O 'Éclatant' está recém-reparado, equipado e pronto para zarpar...";
			link.l1 = "E mais uma coisa, Monsieur: em Paris, a ilha de Saint Martin, que fica ao norte daqui, é considerada uma colônia francesa, mas o Capitão Charles de Maure me disse que os holandeses estão no controle por lá. É verdade isso, Chevalier?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Hum... Em parte, está certo. Saint Martin é uma colônia francesa. No entanto, Barão, do ponto de vista econômico, essa ilha é absolutamente inútil – a área é pequena, o solo é pobre e árido, a água potável é escassa, e o pouco que existe nos poços é turvo e amargo. Cheguei a ouvir que lá até recolhem água da chuva para beber. Por isso, Saint Martin foi arrendada à Companhia Holandesa das Índias Ocidentais por um longo período, e eles a usam como ponto de trânsito ao norte para os navios da Companhia que vão da região para a metrópole. Os holandeses expandiram o povoado de Philipsburg, construíram um forte e um porto, e para quem chegou ao arquipélago há pouco tempo, como o capitão Charles de Maure, Saint Martin pode até parecer uma colônia holandesa.";
			link.l1 = "Mas de jure a ilha pertence a nós?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Claro. Mas como eu disse, é mais lucrativo ganhar dinheiro com o aluguel do que usar seus recursos escassos.";
			link.l1 = "Me parece que esta ilha seria muito útil para a Companhia Francesa das Índias Ocidentais quando ela surgir no Caribe. O significado que você acabou de mencionar — o posto avançado ao norte no caminho para a Europa. Preciso visitar essa colônia, e é bem provável que o arrendamento da ilha aos holandeses seja interrompido.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Primeiro, você precisa enviar um pedido a Willemstad, ao diretor da Companhia Holandesa das Índias Ocidentais, o Mint de Peter Stuyvesant. Ele deve conceder permissão para a inspeção da ilha – afinal, os holandeses estão lá há muito tempo.";
			link.l1 = "Então precisamos enviar um mensageiro para Willemstad.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "O problema é que o senhor Stuyvesant raramente está em Willemstad, está sempre viajando e cuidando dos assuntos da Companhia em seu galeão...";
			link.l1 = "Mas pelo menos às vezes ele está lá, imagino? De qualquer forma, os holandeses têm a obrigação de permitir que os verdadeiros donos inspecionem a ilha. Por que não enviamos uma carta ao governador de Philipsburg?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Mynheer Martin Thomas, with all due respect to him, is just a simple employee; the real management is carried out by the Company. Baron, I will solve this problem, don't worry. It will take some time.";
			link.l1 = "Bem, tenho tempo de sobra. Afinal, ainda precisamos visitar as colônias do sul, Guadalupe e Martinica. É uma pena que o capitão Charles de Maure não me acompanhe desta vez – ele deve mais uma vez partir para Hispaniola...";
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
			dialog.text = "Sim, sim, estamos atrasando nosso querido capitão com nossas conversas entediantes! Charles, leve o 'Éclatant' até o esquadrão, avance para Hispaniola e descubra se há alguma ameaça real dos espanhóis contra Port-au-Prince. Se houver, resolva a situação. Mas não sou eu quem vai te ensinar, você entende disso melhor do que eu. Se não encontrar nada, não perca tempo à toa, preciso de você aqui. Aguardo seu relatório em até um mês. Boa sorte, meu amigo!";
			link.l1 = "Obrigado, Chevalier. Partirei imediatamente.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "And one more thing, Charles: I heard you have problems with the Dutch authorities? Please, settle this issue as soon as possible; in the near future, you will have to visit their colonies. As you understand, that would be impossible under fire from the forts.";
			link.l1 = "Muito bem, Monsieur, será feito.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "E mais uma coisa, Charles: aviso você, evite qualquer conflito com os holandeses. Em breve, você terá que visitar as colônias deles. Como deve entender, isso seria impossível sob o fogo dos fortes...";
			link.l1 = "Certo, Monsieur. Sem brigas com os holandeses.";
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
			dialog.text = "'Eclatant' afundou? Charles, isso é um desastre! O que o ministro vai dizer agora? Você me decepcionou, Charles! Eu tinha certeza de que podia confiar na sua experiência, e você ... Infelizmente, você será responsabilizado por isso. Vou escrever um relatório, e é melhor você sumir por um tempo. Seu serviço na Marinha Real acabou.";
			link.l1 = "Hum... Me desculpe, Monsieur. Acho que é mesmo melhor eu sumir por um mês ou dois, até o ministro esfriar a cabeça. Adeus, e mais uma vez, sinto muito por ter decepcionado você.";
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
			dialog.text = "Excellent! While we have captains in our navy like you, we need not fear the trickery of the Castilians. I will send a courier to Port-au-Prince tomorrow with a dispatch and a letter from France, and at the same time I will drop a hint in a personal letter to Monsieur Jeremy Deschamps du Mussaca that it would be fitting to thank you for your service, so I can assure you, Charles, that you will receive a well-deserved reward.\nAnd now, let's move on to your next assignment. Yes, my friend, I have a new task for you; however, this time it is not a military one, but rather a very delicate matter, and I would like you to handle it.";
			link.l1 = "Estou ouvindo, Chevalier.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Suponho que você se lembra da minha conversa com Monsieur Forget sobre Saint Martin? Precisamos garantir ao barão que a colônia foi inspecionada, e você irá até Curaçao, para Willemstad, ao diretor da Companhia, Peter Stuyvesant. Ele está lá neste momento, e ficará por mais três semanas. Além disso, você deverá escoltar o fluyt com as mercadorias da Companhia até Curaçao e entregar ao senhor Stuyvesant uma carta minha.";
			link.l1 = "São essas todas as tarefas?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Sim, capitão. Informe-me sobre a resposta do senhor Stuyvesant. Devemos chegar a tempo, antes que Monsieur Forget volte de sua viagem à Martinica e Guadalupe, e ele finalmente poderá visitar Saint Martin, que há muito deseja conhecer.";
			link.l1 = "Muito bem. Posso ir?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "Pode ir, Charles. Mas não demore, o barão não gosta de esperar. E quando for visitar Peter Stuyvesant, não se esqueça de usar seu uniforme! Tudo precisa parecer oficial, se é que me entende.";
			link.l1 = "Claro, Chevalier. Adeus!";
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
			dialog.text = "Obrigado, capitão, me entregue... (lendo)... Muito bem, excelente! Peter Stuyvesant diz que o Barão Forget poderá visitar Saint Martin para inspeção e que o governador de Philipsburg será avisado e irá cooperar. Acho que, após a visita, o barão tomará a decisão certa – deixar a ilha para ser arrendada aos holandeses.\nE agora, a notícia mais reconfortante, capitão! Tenho algumas coisas para lhe contar. Primeiro: levando em conta todos os seus feitos militares, você está promovido ao posto de 'Comodoro'. Aceite meus parabéns, Monsieur!";
			link.l1 = "Eu sirvo à França!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "E em segundo lugar: o governador de Port-au-Prince nos enviou um navio mercante cheio de mercadorias para você: 500 grandes sacas de café e mais 500 sacas de cacau. São todas as colheitas das plantações de Hispaniola, aquelas que você protegeu dos ataques espanhóis. Além disso, uma carga especialmente valiosa foi destinada a você – 50 unidades de pau-ferro. Acho que não preciso explicar o que é isso. Seus bens estão guardados na loja de Capsterville, e você pode buscá-los com o comerciante a qualquer momento.";
			link.l1 = "Obrigado, Chevalier! Que notícia maravilhosa!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "E agora, quanto à sua próxima tarefa: o Barão Forget deve voltar a Saint-Christopher a qualquer momento. Você irá escoltá-lo até Saint Martin e garantir que ele esteja bem protegido. Além disso, digamos assim, observe atentamente o que está acontecendo em Philipsburg e depois me informe. Não deixe a cidade, capitão, assim que o barão chegar – meu criado irá encontrá-lo e avisar.";
			link.l1 = "Tudo certo. Posso ir?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Pode sim. Alguns dias de descanso em terra vão lhe fazer bem e serão úteis.";
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
			link.l1 = "Sim, Chevalier, já estamos de volta! Seus amigos holandeses perto de Saint Martin nos receberam com fogo dos canhões do forte e nos atacaram com um esquadrão de três navios. Só graças à habilidade do capitão Charles de Maure e sua tripulação conseguimos escapar! Parece que o senhor Peter Stuyvesant não quer mesmo ver os enviados do rei francês em Philipsburg. O que acha disso, Chevalier?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "O quê?! Aqui está uma carta do Stuyvesant com a assinatura dele, na qual ele garante...";
			link.l1 = "Mas o comandante do forte de Philipsburg claramente recebeu uma carta diferente de Stuyvesant, mandando atirar à vontade e armar uma emboscada contra nós com um esquadrão! Foi um acidente, Chevalier?! Não! Eles estavam obviamente nos esperando lá! Com balas de canhão e chumbo!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Barão, eu lhe peço... Deixe isso comigo. Vamos imediatamente enviar nosso estimado capitão, Charles de Maure, novamente a Curaçao para se encontrar com Stuyvesant. O capitão tem muita experiência em lidar com situações delicadas... Agora, vou pedir aos criados que preparem um banho e um bom almoço para o senhor.";
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
			dialog.text = "Charles, meu amigo, você precisa ir depressa para Willemstad. Talvez Stuyvesant ainda esteja lá. Se não, descubra onde ele está e vá atrás dele. Durante a reunião, conte a ele sobre o incidente e exija uma explicação. Estou confiando na sua experiência e autoridade, e deixo as negociações sob sua responsabilidade. Depois, sem perder um minuto, volte e me informe o resultado da reunião.";
			link.l1 = "A tarefa está clara, Chevalier. Vou preparar o navio e partir imediatamente.";
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
			dialog.text = "Não acredito nisso...";
			link.l1 = "Além disso, no caminho de volta fui atacado por um esquadrão naval holandês. Por favor, explique-me, Chevalier, o que está acontecendo aqui?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Meu amigo, sei o quanto você é perspicaz, então não vou esconder nada de você. Só peço que o que ouvir aqui não saia desta sala. Você me promete?";
			link.l1 = "Claro, Chevalier.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Certo. Tenho certeza de que uma grande carreira na marinha francesa espera por você. Com a minha ajuda, é claro, você pode chegar ao posto de vice-almirante! Mas estou me adiantando... Agora, sobre os holandeses e Saint Martin.\nMuito antes de você chegar a Saint Martin, já haviam sido descobertos grandes depósitos de sal por lá. No começo, ninguém ligou, mas depois os espanhóis em Cuba e Hispaniola demonstraram grande interesse — para salgar carcaças de bois. Como você deve imaginar, não podemos negociar diretamente com a Espanha, então...";
			link.l1 = "...você criou um 'negociador' na forma da Companhia Holandesa das Índias Ocidentais...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Exatamente! Você pensa rápido – e com precisão, Charles! Agora, sabendo da inspeção vinda de Paris, Stuyvesant decidiu assumir o negócio do sal por conta própria, apostando que não queremos sair por aí contando para todos sobre nosso acordo com os espanhóis. Mas aí ele se enganou. Ninguém ousa tirar nada das mãos do Governador-Geral francês sem ser punido! E vamos mostrar isso a ele.";
			link.l1 = "Pelo que entendi, o Barão Forget não pode saber disso...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Meu amigo, você está absolutamente certo, o barão não precisa saber dos detalhes. Já aconteceu o bastante: uma tentativa de assassinato contra o representante do rei da França, o ataque aos navios da missão diplomática — ou seja, a você — e, o mais importante: a anexação de fato da ilha de Saint Martin! Isso já basta para justificar uma ação militar contra os holandeses.";
			link.l1 = "Guerra?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Exatamente! Meu amigo, o cargo de vice-almirante não está tão distante para você, entendeu? Imagine-se nas negociações no Louvre, vestindo o uniforme de almirante, e o próprio Luís XIV recebendo um convidado tão ilustre... Precisamos colocar os holandeses no devido lugar! Stuyvesant vai se arrepender do que fez. Concorda?";
			link.l1 = "Concordo, Chevalier. Os holandeses devem responder por suas ações ultrajantes e vis.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Excelente. Avisarei o barão da nossa decisão e enviarei mensageiros às colônias francesas imediatamente! E você, meu amigo, pode descansar depois da longa viagem, e por favor me visite amanhã após as nove da manhã. Vou preparar uma missão de combate para você.";
			link.l1 = "Muito bem, Monsieur. Permita-me retirar-me.";
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
			dialog.text = "Eu não chamaria isso de guerra, na verdade é mais como impor uma paz. E se Stuyvesant mudar de ideia, vai ser ainda melhor para nós. Por isso, agora precisamos mostrar a ele que, ao tentar tomar a ilha de Saint Martin, ele vai perder muito mais do que pode ganhar. É aí que você entra, Charles.";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Saint Martin é uma base de transbordo para navios holandeses com destino à Europa. Os navios da Companhia costumam ancorar na baía de Philipsburg. Até agora, essas águas têm sido bastante seguras para eles. Até agora, Capitão!.. Você vai zarpar rumo às costas de Saint Martin, patrulhar a região e capturar os navios mercantes da Companhia.   Para transportar mercadorias valiosas, a Companhia usa East Indiamen—navios robustos, bem armados e com grandes porões. Esses serão seus alvos. Capture cinco desses navios junto com sua carga e traga-os como prêmio para Casterville. Depois disso, continuaremos as negociações com Stuyvesant e, talvez, ao contabilizar os prejuízos, ele mude de ideia.";
			link.l1 = "A tarefa está clara. Posso ir?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Monsieur, sou obrigado a perguntar, mas poderia participar do financiamento desta operação? Serão meses de navegação, constantes reparos e perdas...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "Receio que nossas reservas estejam esgotadas, Charles. A manutenção do Ecliaton e as batalhas já nos custaram meio ano do orçamento das colônias francesas. Agora, isso é tudo que posso lhe dar. Pense nas recompensas futuras, Charles! Um grande futuro espera por você!";
			link.l1 = "Sim, senhor!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Vá, meu amigo, e que a sorte acompanhe cada passo seu.";
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
				dialog.text = "Você cumpriu a tarefa, capitão. Obrigado pelo excelente serviço! Você tem direito a uma parte dos lucros da venda dos troféus – duzentos mil pesos.";
				link.l1 = "Fico feliz em ouvir isso, Monsieur!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "Então, você só tem "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" Restam apenas os navios holandeses para trazermos ao nosso porto.";
				link.l1 = "Sim, Chevalier!";
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
			dialog.text = "E isso não é tudo. Estava pensando outro dia... Charles, você realmente fez muito pela França. A eliminação, francamente, do traidor Levasseur, a defesa de Saint-Pierre contra o ataque traiçoeiro da Espanha, a bem-sucedida tomada do forte na colônia de San Jose, e ainda a indenização recebida dos espanhóis como punição pela ousadia deles... E depois disso, você mesmo escoltou o representante da coroa francesa, que veio da Europa, e até salvou a vida dele ao escapar de uma emboscada holandesa nas águas perto de Philipsburg!";
			link.l1 = "Monsieur, por favor, não me deixe sem jeito... Só estou cumprindo meu dever.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Você continua tão modesto quanto sempre, meu amigo. E agora, ao cumprir a última missão de forçar a Holanda a aceitar a paz, você mais uma vez não me decepcionou. Sem exagero, você é um herói da nação! Como governador-geral das colônias francesas no arquipélago, tenho comigo algumas cópias da mais alta honraria da França e... Mas, aliás, peço que leia este documento.";
			link.l1 = "Por serviços notáveis prestados à França... em nome de Sua Majestade, o Rei da França... conceder a um oficial naval a serviço da França, o Capitão Charles de Maure, filho de Henri de Montpe... Chevalier, está brincando comigo?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "De modo algum, meu amigo. Tenho a honra de recompensá-lo como você merece, presenteando-o com a mais alta condecoração da França – a Ordem de São Luís! Todo cidadão do nosso país deve conhecer seu herói! E Saint-Pierre lhe deve muito! Você merece essa Ordem, Charles.";
			link.l1 = "De verdade, não sei nem o que dizer... Muito obrigado, Governador-Geral! Juro continuar servindo à França com orgulho e nunca recuar diante do inimigo!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("You've received the Order of Saint Louis! You are the hero of the nation!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "Palavras de um verdadeiro oficial! Estou realmente orgulhoso de você, Charles. Agora descanse um pouco. Você merece. Enquanto isso, vou cuidar das negociações com Stuyvesant – talvez ele já tenha percebido que é muito menos lucrativo para ele estar em conflito conosco do que ser nosso aliado. Não deixe a cidade, vou precisar de você em dois dias.";
			link.l1 = "Muito bem, Monsieur. Aguardarei novas instruções.";
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
			dialog.text = "Sim. Parece que Stuyvesant começou a responder com ações militares em aliança com a Espanha. Um esquadrão conjunto holandês-espanhol cercou Saint-Christopher. Os fortes de sentinela me informam a cada hora sobre cada movimento deles.";
			link.l1 = "Um cerco?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Obviamente. Eles não tentaram um ataque direto, e isso na verdade é bom. Precisamos agir rápido, capitão, antes que o inimigo consiga bloquear toda a ilha.";
			link.l1 = "O que precisamos fazer?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "Em Saint-John's, em Antígua, está baseada a esquadra da Marinha Inglesa sob o comando do Coronel Doily. Neste momento, ele está visitando Sir Jonathan Fox. Você precisa passar despercebido pelos navios inimigos e chegar até Antígua. Lá, você encontrará o Coronel, entregará minha carta a ele e pedirá ajuda.";
			link.l1 = "Você acha que o Coronel vai concordar em nos ajudar?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "I hope so. The letter should convince him that the reward for his help will be quite sizeable... Also, we need to send a letter to the captain of the 'Eclatant', currently near the shores of Guadeloupe; he must hurry to Saint-Christopher. The firepower of the 'Eclatant' will help us considerably in battle. As you can't be in two places at once, our courier lugger will join your squadron - you must get it through the circle of enemies undamaged, and it will depart for Guadeloupe before the 'Eclatant' heads south...";
			link.l1 = "Entendi. Supere o cerco, escolte a chalupa do mensageiro e corra para Saint-Jones entregar sua carta ao coronel Doily.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Exatamente. Está pronto para aceitar mais um navio em seu esquadrão?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Vou me livrar de um navio e volto para falar com você.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Sim.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Excelente. Pegue a carta, a chalupa está pronta e esperando suas ordens.";
			link.l1 = "Não vamos perder tempo, Chevalier!";
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
			dialog.text = "Sim, sim, meu amigo, conheço bem a sua modéstia. Você é um verdadeiro oficial! E receberá uma recompensa, pode ter certeza! Imagino que, depois de uma batalha tão dura, você precise descansar um pouco, não? Tem uma semana inteira. Venha ao meu gabinete daqui a sete dias – a cidade vai preparar uma recompensa para o seu herói.";
			link.l1 = "Sim, Monsieur. Posso ir?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Vá descansar bem. Mais tarde teremos que lidar com questões sérias – como pode ver, a paz com os holandeses é impossível neste momento. Por enquanto, o coronel e eu vamos discutir alguns assuntos importantes.";
			link.l1 = "Então nos encontraremos em uma semana, Chevalier.";
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
			dialog.text = "We've had a discussion with Colonel Doily and he has agreed to help me. England will support us in the war against the Dutch. You and I must strike back and restore justice – the isle of Saint Martin must return to France. I assign this task to the best navy captain – you, Charles de Maure! The enemy has not yet recovered from their squadron's defeat; we will attack Philipsburg and take it.\nThe battle will not be easy. First, we must destroy the fort, then break through the garrison's defences... (whispering) You will also need to make a forced march through the jungle to the salt deposit I told you about, and kill the enemies encamped there...";
			link.l1 = "A tarefa é bem difícil, Chevalier...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Eu entendo perfeitamente, meu amigo. Seu esquadrão será reforçado. Os governadores de Basse-Terre e Saint-Pierre já devem ter preparado um navio cada—uma fragata. Você só precisa ir até Guadalupe e Martinica para assumir o comando dessas fragatas. Se, é claro, quiser essas embarcações—não vou insistir na sua escolha de navios. Também estou lhe concedendo um subsídio de 20.000 pesos para comprar mantimentos e equipamentos para sua nau capitânia. Aqui, pegue...";
			link.l1 = "Muito bem, Monsieur.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Além disso, como de costume, o navio 'Eclatant' está sob seu comando. Ele foi reparado e equipado, está aguardando na enseada e, após falar com o capitão, você poderá assumi-lo a qualquer momento.";
			link.l1 = "Excelente!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Não podemos perder tempo, capitão. Meus espiões me informaram que os holandeses já perceberam o perigo para Saint Martin e pretendem reforçar suas defesas. Mas você ainda tem dois meses. Precisa concluir a missão a tempo!";
			link.l1 = "Eu vou... (sussurrando) Onde fica o depósito de sal em Saint Martin? Não está marcado em nenhum mapa da ilha...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(sussurrando) Quando você atacar a cidade, interrogue o vice-rei de Philipsburg, Mynheer Martin Thomas, ele vai te contar. Aquele holandês é um covarde e não vai resistir, eu te garanto.";
			link.l1 = "Entendo. Então, posso me retirar?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Espere um momento, Charles. Você ainda não recebeu sua recompensa por salvar Saint Christopher. Aceite estes baús de ouro do povo da cidade, junto com nossa mais sincera gratidão, que nenhuma quantia em dinheiro pode expressar!";
			link.l1 = "Obrigado, Monsieur!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Agora pode ir. Boa sorte, capitão! Todos estamos esperando pela sua vitória!";
			link.l1 = "Adeus, Chevalier.";
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
			dialog.text = "Quem diria, há apenas um ano, que você seria promovido ao posto de vice-almirante, meu amigo? Só posso imaginar o orgulho que seu pai sentirá quando essa notícia chegar à França!";
			link.l1 = "Meu querido pai vai ficar muito contente com isso.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "Você conquistou seu lugar na frota! Saint Martin voltou para a França, Stuyvesant aprendeu uma lição dura. Foi uma grande vitória! Mas não podemos parar, não podemos deixar os holandeses descansarem nem por um minuto. Eles vão pagar pela traição! O coronel Doily está em Port Royal neste momento, preparando seu esquadrão naval: vamos quebrar a espinha do inimigo atacando Curaçao. Mas isso será depois, por enquanto precisamos matar dois coelhos com uma cajadada só, Charles.   A Companhia não acumulou toda a sua fortuna apenas com o comércio. A principal fonte de renda dos holandeses na região é o trabalho escravo nas plantações. Se você não sabe, Charles: a Holanda é a maior nação escravocrata e traficante de escravos. Os navios da Companhia das Índias Orientais, carregando o 'marfim negro', chegam regularmente a Curaçao vindos da África Ocidental. E por acaso eu sei de algo sobre isso, infelizmente para Stuyvesant.   Neste momento, dois navios holandeses das Índias Orientais estão vindo da Guiné para o Caribe. Os porões estão cheios de prisioneiros negros. Daqui a uns dez dias, o comboio vai passar perto da ilha de Trinidad, rumo a Curaçao. Sua missão é encontrar o comboio e capturar esses dois navios e sua carga. Você deve destruir as escoltas e levar os escravos para o nosso aliado, coronel Doily, na Jamaica. Isso é muito importante, Charles, assim vamos conquistar a confiança dele... Espero que compreenda.   Sinto não lhe dar tempo para descansar, mas esta tarefa é importante e delicada, e só posso confiar a você.";
			link.l1 = "Serviço não é doce, Chevalier. Eu sei disso melhor do que ninguém. Vou preparar meu navio e partir assim que puder.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Desejo-lhe bons ventos e uma viagem segura, vice-almirante. E quando retornar a Saint-Christopher, nosso amigo em comum, Monsieur Noel Forget, já terá terminado sua inspeção em Philipsburg, e eu vou garantir que parte dos troféus tomados dos holandeses vá diretamente para você.";
			link.l1 = "Ficarei muito grato, Chevalier. Posso ir?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Vá. Boa sorte para você, meu amigo!";
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
			dialog.text = "Excelente! Você realmente não conhece a palavra 'impossível', Charles. Eu costumava achar que seu irmão era o melhor oficial da marinha no Caribe, mas ele ainda tem muito o que aprender com você, se me permite essa comparação direta. Acho que você já sabe quem vai procurar nosso estimado coronel para participar do ataque a Willemstad.";
			link.l1 = "De jeito nenhum, Monsieur! Como eu poderia saber!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Ah, seu famoso senso de humor, meu caro amigo! Ha-ha! Claro que será você, vice-almirante. O mais digno de todos. Está pronto?";
			link.l1 = "Claro, Chevalier. Só preciso de alguns reparos, um pouco de equipamento – e estou pronto para partir.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "Não se esqueça de assumir o comando do 'Eclatant'. O navio já foi consertado e equipado, está esperando por você no cais. O Marquês Hubert Dassier já está ficando impaciente e ansioso para partir para outra batalha ao seu lado.";
			link.l1 = "Ótimo. Um navio poderoso com culverinas de longo alcance é exatamente o que preciso para bombardear o forte.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Espere um instante, Charles. Nosso amigo, Barão Forget, trouxe notícias para você de Saint Martin.";
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
			dialog.text = "Tenho notícias para você de Paris. Sua nomeação para o cargo de vice-almirante foi assinada pelo Rei. Você receberá os documentos correspondentes. Então, meus parabéns!";
			link.l1 = "Obrigado, Monsieur! É uma honra servir à França e ao Rei!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "E eu, como sempre, fico muito satisfeito em ouvir essas palavras de você. Charles, talvez queira compartilhar um pouco de vinho comigo? Veio direto de Paris, não se encontra desse tipo por aqui nem viajando um dia inteiro!";
			link.l1 = "Obrigado, chevalier, mas acho que vou recusar. Preciso voltar ao navio mais tarde, e não seria apropriado para o Vice-Almirante da França estar bêbado no convés.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Ora, por que não? Não é todo dia que tenho a chance de tomar um drinque com o próprio governador-geral!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Bem, você pode tirar uma folga, não precisa voltar ao navio imediatamente. Mas a escolha é sua, e eu respeito isso. Muito bem, vamos direto ao assunto.";
			link.l1 = "Estou ouvindo atentamente.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "E nem todo governador-geral tem a sorte de ter seu vice-almirante não só como o melhor oficial da marinha, mas também como um amigo, com quem pode sentar à mesma mesa e beber um vinho trazido de uma terra distante!";
			link.l1 = "Por França!";
			link.l1.go = "patria_coat_03";
			link.l2 = "À sua saúde, chevalier!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "E pelo rei!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "E ao seu, Charles!";
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
			dialog.text = "Hum, vinho requintado! Você não acha?";
			link.l1 = "Sim, você estava certo. Isso me lembra o vinho que fazem lá em casa, na Gasconha...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Você errou por pouco, meu amigo — é Bordeaux. Mas tenho certeza de que o vinho da Gasconha é tão bom quanto!";
			link.l1 = "Acho que estou começando a esquecer o gosto disso... Quanto tempo já passou desde que deixei a França? Um ano? Dois?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Ah, Charles, parece que nos conhecemos há pouco tempo... e não nas circunstâncias mais agradáveis. Perdoe-me por tocar nesse assunto, mas se alguém me dissesse naquela época que o homem diante de mim naquela cela se tornaria meu futuro braço direito nas colônias francesas, eu provavelmente teria caído na risada.";
			link.l1 = "Inscrutáveis são os caminhos do Senhor.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Com licença, o que foi que você disse agora?";
			link.l1 = "É latim, chevalier. Os caminhos do Senhor são insondáveis. Ninguém sabe o que a vida reserva.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Você nunca deixa de me surpreender, Charles. Veja só – eu não fazia ideia de que você também sabia falar latim. Mas, por outro lado, até certo ponto, nós mesmos forjamos nosso destino, não é?";
			link.l1 = "Acho que as duas coisas são verdadeiras. Só o Senhor sabe o que nos espera. Mas Ele recompensa os perseverantes.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "Não poderia concordar mais. Lembro, por exemplo, de ter lhe entregue a patente de oficial naval e lhe dado aquele uniforme. E agora, diante de mim, está um vice-almirante, nada menos!";
			link.l1 = "O tempo voa, chevalier.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "Indeed... And even on your uniform, I see the cuts left by sabers; some cuts have been stitched, and some are clearly fresh. This needs to be corrected.";
			link.l1 = "O que o senhor tem em mente, Governador-Geral?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "Além do seu novo cargo como Vice-Almirante da frota francesa no arquipélago do Caribe, tenho mais um presente para você.";
			link.l1 = "Você está me deixando sem graça, chevalier. Que presente?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "Já acertei com meu alfaiate pessoal – o melhor das colônias francesas! – para costurar um uniforme à altura do seu posto. Não se preocupe com o pagamento, já cuidei de tudo.";
			link.l1 = "Estou realmente agradecido! Com certeza vou visitar o seu alfaiate. Onde posso encontrá-lo?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Ele deve estar no escritório do porto agora mesmo – acabou de chegar um navio-correio do continente com alguns pequenos pacotes. Nosso alfaiate sempre encomenda materiais difíceis de encontrar por aqui.";
			link.l1 = "Vou até o escritório do porto então. Obrigado mais uma vez, monsieur!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "E agora, tenho certeza de que você precisa descansar bem. Dou-lhe um mês, então aproveite esse tempo com sabedoria. Nada de trabalho, nada de preocupações. Deixe tudo nas mãos dos seus oficiais e descanse de verdade. Pode usar os aposentos da minha residência. Os criados vão garantir que sua estadia seja a mais confortável possível. Nos veremos novamente em um mês – e terei um assunto delicado para tratar com você.";
			link.l1 = "Muito bem, Chevalier. Adeus!";
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
			dialog.text = "Sim, Charles. Achei que poderia resolver isso sozinho, mas... infelizmente, preciso pedir sua ajuda mais uma vez. Mas antes, preciso lhe entregar algo: trezentos mil pesos e cinco baús de dobrões. Isso é uma grande parte da contribuição que Stuyvesant me pagou conforme o acordo. Acho que você merece tudo isso, já que fez praticamente todo o trabalho. Aceite. Está satisfeito, meu amigo?";
			link.l1 = "Dinheiro nunca fez mal a ninguém, Monsieur, aprendi bem essa lição.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ah, vice-almirante, espero que não guarde ressentimentos pelo que aconteceu no passado?.. Agora você é um herói da sua nação, sabia? Como se sente nessa nova posição? Lembre-se: muitos oficiais competentes passaram décadas subindo de patente, mas sem uma mão experiente... acabam ficando apenas como comandantes. Mas você, meu amigo, tem uma habilidade única de sempre realizar o impossível! E ainda conta com um amigo influente, que também é seu protetor, então se tiver qualquer problema no futuro, estarei aqui para ajudá-lo.";
			link.l1 = "Obrigado por essas palavras gentis, excelência. Sinto que já conquistei quase tudo nesta região. Com a sua ajuda, é claro. Suponho que agora posso cuidar dos meus próprios assuntos em paz? Preciso pensar na minha família.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "Você quer se casar, Charles? Ah-ha-ha! Aponte para qualquer bela mulher em Paris – e ela será sua na mesma hora! Mas, infelizmente, isso vai ter que esperar. Preciso de você aqui, meu amigo, pelo menos por enquanto.";
			link.l1 = "Parece que a França está mais forte do que nunca no Arquipélago. Uma aliança com os ingleses, uma trégua com a Companhia. Não restou nenhum... 'Levasseur' problemático. Certo?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Nações, assim como as pessoas, sempre querem mais, não importa o quanto já tenham... E de fato temos um novo 'Levasseur', Vice-Almirante...";
			link.l1 = "Sério? E quem é?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "É o nosso velho conhecido, Barão Noel Forget. Você se lembra por que ele veio aqui?";
			link.l1 = "Hum... Você mencionou algo sobre a Companhia das Índias Ocidentais. Paris resolveu criar uma organização igual à dos holandeses?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Exatamente. Muito parecido com a Companhia Holandesa. Mas criar uma do zero é extremamente difícil. Veja, Stuyvesant tinha décadas de experiência negociando com diferentes continentes, uma rede de agentes bem desenvolvida e uma poderosa frota de navios mercantes. A França não tem isso e, caso não saiba, Charles, o Rei, está enfrentando uma séria falta de recursos neste momento. Eles esperam resolver a situação financeira da metrópole trazendo o comércio para cá, mas não entendem o que teremos que enfrentar.\nRivalidade tanto com os ingleses quanto com os holandeses, as ambições territoriais dos espanhóis, a pirataria florescendo como nunca antes. Cada fluyt mercante precisa ser escoltado por um navio de guerra, ou corre o risco de nunca chegar ao seu destino. E nós não temos uma frota poderosa como a Companhia Holandesa das Índias Orientais, nem os grandes galeões dos espanhóis.";
			link.l1 = "Mas você explicou tudo isso ao barão? Inclusive sobre os piratas?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Claro que sim. E também sobre a expulsão dos piratas de Tortuga depois da sua missão contra Levasseur, algo que eles não esqueceram e nunca vão nos perdoar. Organizei encontros com várias pessoas que confirmaram minhas preocupações, mas, infelizmente, isso não teve efeito nenhum sobre o barão. Ele foi enviado pelos ministros, e tem dívidas com eles... É assim que as coisas são.";
			link.l1 = "Hã...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "E não vamos esconder o fato de que uma companhia comercial no Arquipélago, sob controle direto de Paris... você e eu, vice-almirante... não precisamos disso aqui.";
			link.l1 = "Entendi.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Veja bem, meu amigo, estou sendo extremamente sincero com você... Então, eu realmente esperava de coração que Monsieur Forget mudasse de ideia sobre criar essa companhia de comércio, mas... isso não aconteceu. Gastei toda a minha influência com o barão, e agora você precisa entrar em cena.";
			link.l1 = "Hum... Igual aconteceu com Levasseur?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "Meu Deus, não, quem você pensa que eu sou, Charles?! O barão é uma figura influente, amigo do Ministro das Finanças! E além disso, eliminar ele fisicamente não adiantaria nada: outro político seria enviado de Paris. Precisamos destruir a própria ideia de organizar uma companhia dessas, entende, Charles? Assim o barão voltaria para a França e relataria que seria financeiramente arriscado, sem sentido...";
			link.l1 = "Tem alguma ideia, Monsieur?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Infelizmente não, Charles. Já tentei de tudo. Amedrontei-o com a falta de navios e dinheiro, com os holandeses, piratas... Nada adiantou.";
			link.l1 = "Parece que precisamos de algo mais sério do que simples palavras. Hm... Piratas, você diz?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "Vejo que você tem uma ideia, meu amigo? Eu não tinha dúvidas. Você tem uma mente brilhante. Convença esse barão, e eu vou garantir que seu pai tenha dinheiro suficiente para encher sua casa inteira com riquezas dignas do Louvre. Eu te prometo, Charles.";
			link.l1 = "Muito bem, Chevalier. A tarefa está clara.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Eu juro, Charles, você não vai se arrepender se conseguir. Pode ter certeza disso. Já te traí alguma vez, meu amigo?";
			link.l1 = "De jeito nenhum, Monsieur. Onde posso encontrar o Barão?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "Neste momento, ele está em Port-au-Prince. Ele disse que acha os campos e vales sem fim de Hispaniola muito encantadores...";
			link.l1 = "Ótimo. Agora, permita-me retirar-me.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Exatamente isso. O barão me contou tudo. Depois de tudo que ele passou... Mas você consegue explicar as coisas de forma clara, como ninguém, vice-almirante! Eu deveria aprender isso com você!";
			link.l1 = "Aprendi muito com você, Chevalier.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Meu amigo, eu lhe devo muito. Garanto que seu querido pai terá tudo o que precisar nesta vida, e a casa da sua família será a mais bela da província... e uma das melhores da França. Além disso, vou lhe pagar 100.000 pesos – espero que isso cubra sua dívida com os piratas...";
			link.l1 = "Que bom ouvir isso, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "Também preparei um presente especial para você. Tenho certeza de que saberá reconhecer o valor deste item e a sinceridade da minha gratidão pelo seu serviço leal! Então, Vice-Almirante Charles de Maure, apresento-lhe minha espada cerimonial pessoal da Ordem de Malta! Esta arma preciosa, acredito, combinará perfeitamente com seu uniforme! Se decidir retornar a Paris, o Barão Noel Forget prometeu apresentá-lo ao Rei — você deve ir a ele em traje de gala: vestindo seu uniforme e empunhando esta excelente lâmina! Oportunidades ainda mais gloriosas de carreira na marinha francesa esperam por você!";
			link.l1 = "Esta espada é incomparável em sua beleza! Obrigado, Monsieur, eu realmente não mereço essa honra...";
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
			dialog.text = "Sim, você! E enquanto estiver aqui, grandes mudanças o aguardam. Mudanças boas. Vice-Almirante Charles de Maure, eu o nomeio Governador de Saint Martin!";
			link.l1 = "Hah!   Eu ouvi direito?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Sim, meu amigo. Agora você é o governador de Saint Martin, que protegeu com tanta dedicação.";
			link.l1 = "Cavaleiro, permita-me recusar essa honra. Não quero ficar preso a esta ilha miserável! E todos esses problemas domésticos... Não foi para isso que nasci!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "Eu não aceito sua recusa. Meu amigo, não tenha medo: sua vida continuará como antes. Todos os assuntos tediosos ficarão a cargo do atual governador interino. Você será o governador de fato. Charles, você não entende por que foi justamente você quem foi escolhido para governar Saint Martin? Agora é o momento perfeito para isso, quando ninguém vai questionar nada. Eu preciso de um dos MEUS homens como governador lá, entende o que quero dizer?";
			link.l1 = "A mina de sal?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Claro! E a segunda boa notícia: a partir de agora, todo dia 15 de cada mês, você vai receber uma parte do lucro da mina, assim como do comércio do Doily. Sua renda passiva será de 100.000 pesos por mês.";
			link.l1 = "Hah! Fico feliz em ouvir isso! Obrigado, Chevalier. Bem, se eu não for obrigado a ficar preso lá, aceito o cargo de governador. E se eu decidir navegar para a França?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Quando você decidir — irá embora, e eu, embora muito desapontado, vou encontrar um substituto para você. Mas isso não é tudo. Tenho aqui uma carta do seu pai. Dê uma olhada.";
			link.l1 = "Do meu pai? Estou emocionado!.. Muito bem, Monsieur, está combinado. Posso ir agora? Quero ler a carta... Não há novas tarefas para mim?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Agora não, Governador, mas se eu encontrar algum trabalho, sei onde te achar. Boa sorte, Charles!";
			link.l1 = "E para você também, Chevalier!";
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
			dialog.text = "Maldição, que desastre! Agora temos mais problemas para resolver. Você é o responsável por isso, Charles? Fale a verdade. Foi um acidente?";
			link.l1 = "Bem, alguma coisa deu errado...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "Maldição, que desastre! Agora temos ainda mais problemas para resolver. O Barão escolheu um lugar péssimo para morrer! Tem certeza de que não ajudou ele a partir deste mundo?";
			link.l1 = "O que está dizendo, Chevalier?! Claro que não!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "Maldição, que desastre! Agora temos ainda mais problemas para resolver. Tem certeza de que não ajudou ele a deixar este mundo?";
			link.l1 = "O que está dizendo, Chevalier?! Claro que não!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "Certo. Bem, meu amigo, talvez nem tudo esteja perdido. Febre é febre, não é? E até que chegue um novo inspetor do ministério, vamos limpar essa bagunça aqui e esperar nossos convidados, bem armados... Agora, Charles, precisamos encerrar todos os nossos contatos. Espero que entenda o motivo, não é?";
			link.l1 = "Claro.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "Certo. Bem, meu amigo, talvez nem tudo esteja perdido. Batalhas no Caribe são de se esperar, não é? E até que um novo inspetor do ministério chegue, vamos arrumar essa bagunça aqui e esperar nossos visitantes bem armados... Agora, Charles, precisamos encerrar todos os nossos contatos. Espero que você entenda o motivo, não é?";
			link.l1 = "Claro.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "Certo. Bem, meu amigo, talvez nem tudo esteja perdido. Piratas são piratas, não é? E até que um novo inspetor do ministério chegue, vamos dar um jeito na bagunça aqui e esperar nossos convidados bem armados... Agora, Charles, precisamos encerrar todos os nossos contatos. Espero que compreenda o motivo.";
			link.l1 = "Claro.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "De qualquer forma, meu amigo, você fez tudo o que pôde. E isso já é melhor do que nada. Fico feliz que o destino tenha nos colocado no mesmo caminho. Pode manter seu posto, e tenho certeza de que uma grande carreira o espera na França. E acho que chegou a hora de você voltar para Paris. Aqui, uma carta do seu pai. Pegue.";
			link.l1 = "Meu pai? Isso é uma ótima notícia!.. Está bem, Monsieur, entendi. Nenhum contato, total sigilo, e assim que possível – ir para Paris. Posso ir agora? Quero ler a carta...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Vá, Charles. Boa sorte!";
			link.l1 = "E para você também, Chevalier!";
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
			dialog.text = "Exatamente. Você consegue explicar as coisas como ninguém, vice-almirante! Eu devia aprender isso com você!!";
			link.l1 = "Aprendi muito com você, Chevalier.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Meu amigo, estou em dívida com você. Garanto que seu querido pai terá tudo de que precisar, agora e no futuro, e sua casa de família será a mais bela da província... e uma das melhores da França. Além disso, vou lhe pagar 100.000 pesos – espero que isso cubra suas despesas de viagem e lhe permita desfrutar de um merecido descanso.";
			link.l1 = "Que bom ouvir isso, Monsieur!";
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
			dialog.text = "Como pôde, Charles! Como pôde fazer isso comigo?!";
			link.l1 = "Hum...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "Eu sei que foi você! Você fez isso! Não negue! Sem a sua ajuda, o Barão Forget nunca teria recebido os relatórios do administrador da mina, nem a localização da mina, nem mesmo os documentos de Peter Stuyvesant. Seu nome não foi mencionado ali, mas deixe-me dizer uma coisa: eu sei com certeza, foi você. Por quê, Charles?.. Só me responda... Por quê? Michel? Um milhão de pesos? Levasseur? Ou talvez o cargo de Governador-Geral?";
			// belamour legendary edition -->
			link.l1 = "Você se lembra do nosso primeiro encontro, Chevalier? De como você me colocou no meu devido lugar? De como arrancou um milhão de pesos de mim? Eu só queria que um dia pudéssemos trocar de lugar. Não tenho mais nada a dizer a você.";
			link.l1.go = "patria_prison_2";
			link.l2 = "Por Levasseur. Uma dívida de um milhão, até consigo entender. Trabalhei, matei, ganhei, roubei, mas te recompensei por todo o prejuízo. E mesmo assim não foi suficiente pra você. Você, Chevalier, me mandou numa missão suicida contra a Coroa só pra fortalecer ainda mais o seu poder pessoal! Sua traição exigia uma resposta. E você teve!";
			link.l2.go = "patria_prison_2";
			link.l3 = "Ambição, Chevalier. Neste novo mundo estranho, eu já tinha conquistado quase tudo o que podia. O cargo de governador-geral me parecia um objetivo digno. Aprendi muito com você. Adeus!";
			link.l3.go = "patria_prison_2";
			link.l4 = "Para ser sincero, nem eu sei ao certo. Talvez seja porque admiro o barão e sua lealdade ao nosso país? De qualquer forma, agora você terá bastante tempo para refletir sobre isso por mim. Adeus!";
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
				dialog.text = "Que bom ver você, Charles. Ouvi falar das suas façanhas. Trabalho brilhante!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Isso não é tudo, Sua Excelência.";
					link.l1.go = "PZ_2";
				}
				else
				{
					link.l1 = "Posso receber uma ordem por escrito do senhor para que meu irmão seja libertado agora?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Greetings, Charles. Come in; I've already been informed.";
				link.l1 = "Informado? Deve haver algum engano, Vossa Excelência. Vim relatar o sucesso da sua missão, mas vejo que o senhor não está no melhor dos ânimos.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ_2":
			dialog.text = "É mesmo? O que quer dizer com isso, Capitão?";
			link.l1 = "Consegui capturar Levasseur vivo e trazê-lo até você. Assim que terminarmos, vou mandar trazê-lo até você.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Eu nunca imaginei que algo assim fosse possível! De fato, um trabalho brilhante, Charles! Duvido que até mesmo seu ilustre irmão teria feito melhor. Seu pai teria orgulho de você, meu amigo.";
			link.l1 = "Obrigado pelas suas palavras gentis, Monsieur Philippe.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ_5":
			dialog.text = "Muito bem, Charles. Estou satisfeito com você.";
			link.l1 = "Posso receber uma ordem por escrito do senhor para que meu irmão seja libertado agora?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "Talvez eu devesse ter levado em conta que você não é seu irmão — não é um militar, nem um agente secreto, e ainda não tem experiência em operações delicadas. Você não devia ter enfrentado soldados abertamente nas ruas de Tortuga. Haverá investigações, inclusive sobre mim. E de gente séria, como você entende.";
			link.l1 = "Peço desculpas, Chevalier. Como o senhor sabe, Levasseur não teria desistido sem lutar.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "É verdade, mas... deixa pra lá. Nada mal para uma primeira missão. Vou relatar que ele atacou o Auditor Real e sua escolta durante uma inspeção oficial.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Excelência, se ajudar, posso trazer Levasseur até você. Meus homens e eu tivemos a sorte de capturá-lo em um lugar isolado depois que os capangas dele tentaram nos prender nas ruas.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "Posso receber uma ordem por escrito do senhor para que meu irmão seja libertado agora?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "O que você disse, Charles? Repita isso.";
			link.l1 = "François Levasseur está no meu porão agora, pronto para ser entregue ao senhor, Monsieur Philippe.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Esqueça tudo o que eu disse antes. Eu realmente exagerei. Trabalho brilhante. Não tenho certeza se nem mesmo seu ilustre irmão conseguiria fazer isso.";
			link.l1 = "Obrigado, Chevalier.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Você tem um grande potencial, meu amigo. Gostaria que seus talentos fossem usados mais vezes em benefício do país. Mas, por favor, tente ser mais... discreto daqui pra frente. Nosso trabalho normalmente exige um toque delicado. Ah, sim, e mais uma coisa.";
			link.l1 = "Sim, Vossa Senhoria?";
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
