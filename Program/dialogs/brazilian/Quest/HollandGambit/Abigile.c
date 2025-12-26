// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Bom dia, senhor. O que o traz à nossa casa?";
					link.l1 = "Bom dia, Abigail. Meu nome é "+GetFullName(pchar)+". Eu sou um capitão a serviço da República e da Companhia Holandesa das Índias Ocidentais.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Meu Deus, você encontrou o dinheiro do meu pai? É verdade? Ah, estou tão feliz! Rápido, vá falar com meu pai, ele quer conversar com você. Vá vê-lo!";
					link.l1 = "Estou a caminho, madame.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "Você nos salvou do completo desespero, capitão! Sou tão grato a você! Agora o bom nome da família Shneur pode ser restaurado!";
					link.l1 = "Apenas cumprindo meu dever de cavalheiro, madame. Espero que nada mais a impeça de se casar com meu patrono.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Precisa de algo, capitão?";
				link.l1 = "Agora não, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Salve, Rainha Santa, nossa vida, nossa doçura e nossa esperança. A ti clamamos, pobres filhos exilados de Eva. A ti elevamos nossos suspiros, gemendo e chorando neste vale de lágrimas... ah, senhor, você me assustou! O que o traz aqui?";
					link.l1 = "Com licença, Abigail, presumo? Richard Fleetwood me enviou...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Quer alguma coisa, capitão?";
				link.l1 = "Agora não, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "O que está acontecendo aqui? Que barulho é esse? Papai, quem é esse homem estranho?";
					link.l1 = "Bom dia, madame. Abigail Schneur, presumo? Fico feliz em vê-la. Peço que me perdoe pela ousadia, mas tenho aqui uma carta urgente endereçada a você de... bem, eu adoraria lhe contar, mas seu querido pai não permite nem que eu entre em sua casa, quanto mais entregar esta mensagem pessoalmente.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ah, aqui está você, Charles. Estou pronto para te seguir aonde for!";
					link.l1 = "Então vamos.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "Já chegamos em St. John's, Charles? Vou ver o Richard em breve?";
					link.l1 = "Yes, madam, we are in St. John's. Unfortunately, Richard is not in town at the moment; he was ordered to patrol near Barbados two days ago. Don't worry, he should return in a week.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charles! Que bom te ver! Alguma notícia do Richard?";
					link.l1 = "Alas, my dear madame. Richard had to stay in Bridgetown for a while on a secret and important mission; it has something to do with the Dutch. I take it Richard has told you what he does for a living, right?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Charles! É você! Finalmente voltou!";
					link.l1 = "Saudações, madame. Fico feliz em vê-la.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ah, finalmente estou em casa! Estou tão feliz por ver o papai de novo! Charles, obrigada por tudo o que fez por mim!";
					link.l1 = "Por favor, não há necessidade de falar assim, madame. Só estou cumprindo meu dever de cavalheiro ajudando uma dama em apuros.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Papai, se lembrar de alguma coisa, por favor, diga! Charles, ele é... ele é de confiança. Eu diria que ele é o único que pode nos ajudar!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "Vou rezar por você dia e noite! Diga... diga que vai fazer isso! Que vai encontrar a ilha!";
					link.l1 = "Farei o que puder, senhora.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ah, Charles! Você voltou! Diga logo, encontrou a ilha? Mal posso esperar mais um minuto!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Sim, Abi. Eu encontrei a ilha e o dinheiro do seu pai. Vim aqui para devolvê-lo a você.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Infelizmente, madame. Não consegui encontrar nem o capitão Keller nem a sua ilha. Fiz o que pude, mas...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "Ah, é você, Charles! Precisa de algo? Posso te oferecer um café?";
				link.l1 = "Não, nada. Por favor, não se incomode.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Bom dia, senhor. O que deseja?";
			link.l1 = "Nada, madame. Peço desculpas. Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "É uma honra conhecê-lo, capitão "+GetFullName(pchar)+". Ouvi todo tipo de história sobre você das outras damas da cidade. Você é o homem que capturou o navio fantasma pirata e o trouxe como prêmio para Willemstad. Diga-me, capitão... é verdade que esse navio estava sob o comando de... Richard Fleetwood?";
			link.l1 = "Tudo o que a senhora ouviu é verdade. Fiquei tão chocado quanto qualquer um ao descobrir a verdade. É um escândalo! Um oficial naval da Comunidade Inglesa saqueando mercadores do próprio país como um pirata qualquer! Esse canalha tentou encobrir seus atos desprezíveis fingindo ser um 'navio fantasma' renegado sob a proteção da Companhia Holandesa das Índias Ocidentais. Ele usou essa fachada para culpar a Companhia e também atacar navios holandeses.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "Minha cabeça está girando... É difícil ouvir coisas tão terríveis, capitão. Eu conhecia Richard Fleetwood pessoalmente, nunca imaginei que ele...";
			link.l1 = "Madame, I have been informed by my patron Lucas Rodenburg about your voyage to Curacao from Recife. Now it is clear. Fleetwood sank your ship and then returned to 'save' you and your father from being marooned on that lost island. I read the pirate's journal myself; he recorded every detail in his logbook.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Que pesadelo... Parece que meu pai estava certo o tempo todo. Ele vivia dizendo que o Richard era o pirata por trás de todas as nossas desgraças. Acho que deveria ficar aliviada por finalmente saber a verdade... ah, me desculpe, capitão. É que é tanta coisa pra minha cabeça... o que um homem tão importante como o senhor pode querer com uma garota comum como eu?";
			link.l1 = "Abigail, estou aqui por causa de um assunto muito complicado e delicado. Você pode me ouvir?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Claro, senhor. Estou todo ouvidos.";
			link.l1 = "Como já disse, sirvo à Companhia. Lucas Rodenburg não é apenas meu comandante militar, mas também um grande amigo. Ele me enviou até você com um recado. Nada o faria mais feliz do que se você aceitasse sua proposta de casamento. Estou aqui para pedir que se case com meu protetor. Ele está disposto a fazer qualquer coisa no mundo pela sua felicidade.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "Oh, capitão! Agora entendo por que o senhor Rodenburg não quis fazer isso ele mesmo... Meu pobre papai ficaria tão feliz, mas eu...";
			link.l1 = "Madame, percebo que algo está lhe incomodando. Você duvida da sinceridade do senhor Rodenburg? Talvez eu possa ajudá-la a repensar isso?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "Ah não, capitão, não duvido da sinceridade do senhor Rodenburg. Lucas fez tanto por mim e pelo meu pai, não sei o que seria de nós se ele não cuidasse da gente. Mas, por favor, precisa entender minha situação! Minha família não é dos Rothschild, mas nunca fomos pobres. Os Shneur são conhecidos entre os bancos da Europa pela nossa fortuna... mas agora esse pirata terrível nos arruinou! Não aguento mais esses boatos maldosos que sei que circulam pelas nossas costas, não suporto mais. Toda dona de casa tagarela e criada desta cidade acha que estou atrás do senhor Rodenburg só pelo dinheiro dele. 'Bem coisa de judia', dizem elas. Que crueldade! Se ao menos meu pai lembrasse onde fica a ilha! Ele escondeu lá o que restou da nossa fortuna para salvar das mãos daqueles piratas malditos que mataram minhas irmãs e meu irmão! Mas meu pobre pai não é marinheiro, ele simplesmente não consegue lembrar onde fica a ilha nem onde está o nosso dinheiro! Por favor, fale com meu pai, capitão! Talvez ele consiga lembrar de algo que seja útil para sua experiência. Por favor, encontre essa ilha e nossa fortuna! O senhor vai salvar uma pobre moça da vergonha e da desonra!";
			link.l1 = "Muito bem, Abigail. Vou falar com seu pai. Tenha fé, garota, farei o que puder.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Obrigada, senhor. Vou rezar por você dia e noite. Que o Deus dos nossos pais esteja com você!";
			link.l1 = "Adeus, Abigail. Eu volto com boas notícias, eu juro.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "Oh, sim! O senhor Rodenburg é um homem honrado e bondoso. Vou lhe dar meu consentimento sem hesitar, e ficarei feliz em chamá-lo de meu marido.";
			link.l1 = "Então considero minha missão cumprida. Agora preciso ir até o senhor Rodenburg e lhe contar as boas notícias. Desejo sinceramente que seja feliz, senhora.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "Richard te mandou?! Santa Maria, obrigada! Ah, senhor! Ouvi dizer que o pobre Richard foi ferido e está à beira da morte. É verdade? Diga-me, ele está vivo?! Ele está bem?!";
			link.l1 = "Richard está vivo e... quase saudável. Agora as más notícias: ele está um pouco debilitado e ficou temporariamente cego, mas está se recuperando. Agora as boas notícias: Richard quer que você viaje com ele para a Inglaterra, onde vocês vão se casar. O tempo dele no Caribe acabou e ele está esperando sua resposta.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ah, meu caro mensageiro, diga a Richard que, pela nossa felicidade, estou pronta para ir com ele aonde ele quiser. Mas temo que nossa fuga vá matar meu pobre pai... Senhor, estou desesperada e não sei o que fazer. Queria tanto que Richard encontrasse aquela ilha maldita e o baú com o ouro da nossa família... Talvez isso consolasse um pouco meu papai na minha ausência.";
			link.l1 = "Entendi... Minha missão era levar você até Antígua, mas isso complica um pouco as coisas. Se eu encontrar a ilha e o baú e trouxer para você, aí sim você vai comigo para St. John's e para o Richard?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "Oh sim, senhor, vou lembrar de você nas orações da nossa família! Vou dar seu nome ao nosso primeiro filho! Muito obrigado, capitão! Vou rezar por você! Vá, e que Cristo e a Santíssima Mãe estejam com você!";
			link.l1 = "Não vou fazê-la esperar muito, madame. Voltarei em breve.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Oh... Você tem uma carta dele? Ah, papai, não seja tão duro com nossos convidados! Você está me envergonhando com essas fantasias neuróticas! Senhor, por favor, venha comigo, quero conversar com você.";
			link.l1 = "Obrigada, senhorita. Fico feliz em ver que pelo menos alguém nesta casa fala com sensatez.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Perdoe meu pai, senhor. Ele é realmente um homem bom e generoso, mas as nossas... desventuras o destruíram.";
			link.l1 = "It is all right, mistress, I understand. Let me introduce myself, I am Charlie the... Knippel. I am here on the orders of Richard Fleetwood; he wants me to bring you to him. Here, please, read the letter.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Oh Richard...(lendo). Meu Deus! Ele decidiu... devolver todo o dinheiro perdido do meu pai! Que generosidade! Querido, doce Richard! Mynheer, você traz notícias boas como o próprio Gabriel! Richard, onde ele está? Ele está em Curaçao?";
			link.l1 = "Não, senhorita. Tentaram matar ele e ele ficou gravemente ferido. Agora ele está em Antígua... você não terminou de ler a carta.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "Santíssima Maria, concebida sem pecado, rogai por nós que recorremos a vós! Diga-me, ele está a salvo? O ferimento dele é grave?";
			link.l1 = "Não se preocupe assim, senhorita! Richard não é do tipo de homem que deixaria uns canalhas matarem ele tão fácil. Agora ele está descansando e se recuperando. Ele pediu pra eu levar você até ele. Depois vocês dois vão zarpar para Londres... por favor, termine a carta, senhorita, está se adiantando.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ah, sim... Me desculpe (lendo). Myheer Knippel, estou pronto para zarpar com você. Preciso de um dia para arrumar minhas coisas e conversar com meu papai. Volte amanhã e irei com você.";
			link.l1 = "Certo, senhora. Estarei aqui amanhã. Não se preocupe, minha tripulação e eu vamos protegê-la de qualquer perigo durante a nossa viagem.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, que pena. Mas acho que posso esperar mais uma semana, como já esperei antes...";
			link.l1 = "Muito bem dito, senhorita. E para tornar sua espera mais agradável, proponho trocarmos esta cabine austera pela casa do meu amigo. Lá terá uma cama macia e boa comida preparada para você.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "Você é tão gentil, Charlie. Obrigada. Vai ser bom sentir terra firme de novo... Estou meio enjoada depois de tanto balançar nas ondas.";
			link.l1 = "Por aqui, por favor, senhorita.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "Fico feliz em conhecê-lo, John. Agradeço pela hospitalidade de vocês, senhores!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "Oh Charlie, eu só vi o Richard algumas vezes e ele nunca me contou muito sobre o que faz.";
			link.l1 = "Estou realmente surpreso que ele esconderia um segredo tão grande da mulher que ama... Senhorita, Richard não é apenas um capitão comum. Ele também é um agente especial do Conselho Privado da Inglaterra. Um homem muito importante, que lida com missões delicadas diretamente ordenadas pelo Lorde Protetor. Neste momento, sua missão é destruir o poder comercial da Companhia Holandesa das Índias Ocidentais no Caribe.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Senhor, do que está falando?";
			link.l1 = "Sim, senhorita. O seu amado Richard – meu amigo – é um homem muito importante. Sempre tive orgulho de ser amigo dele, mas ele ficou muito reservado, até mesmo comigo. É óbvio que ele está em alguma missão secreta. Sinto muito que essa missão não permita que ele se encontre com você.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, você está me assustando. Tem certeza de que ele está bem?";
			link.l1 = "Tenho certeza disso. Só que... não aprovo a maneira como ele está te tratando agora. Entendo que a missão dele é vital e que ele não pode trair o dever, nem mesmo por você.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Oh, meu querido Charlie... Vou esperar por Richard até o fim dos tempos, se for preciso. Talvez eu possa ficar no andar de cima da taverna... Não posso continuar abusando da hospitalidade do John por tanto tempo.";
			link.l1 = "Pare de falar bobagem, senhora! Sua presença nos honra e eu não me chamo Charlie Knippel se eu expulsar a noiva do meu querido amigo Richard Fleetwood de casa!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... Fico realmente comovida com o que sente por mim. Sou apenas uma moça comum, e ainda por cima judia...";
			link.l1 = "Senhorita! Eu sei que isso é conversa imprudente, você é uma jovem cristã exemplar! E nem pense em tavernas! Eu nunca me perdoaria se falhasse com você no meu serviço ao Richard.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Obrigado, Charlie. Fico feliz que você seja um... homem tão bom.";
			link.l1 = "It is my duty, miss. Now, I am sorry, but I have to go. You are free to walk around the town now; you must feel quite lonely confined in this house, am I right?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Bem... John é uma companhia bem interessante. Ele consegue falar por horas sobre seus pós, misturas e várias... doenças. Além disso, é um homem educado e gentil. Também costumo ir à igreja, o padre local é bem bondoso... mas, claro, sinto muita falta do Richard.";
			link.l1 = "Acho que ele volta logo. Charlie Knippel está à sua disposição se precisar de alguma coisa.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "Ouvi rumores sobre o Richard... dizem que ele sumiu. Você sabe de algo sobre isso, Charlie?";
			link.l1 = "Eu sei, Abigail. Me desculpe... Richard Fleetwood voltou para a Inglaterra e não vai mais voltar. Ele foi promovido ou transferido, algo assim... de qualquer forma, depois do que ele fez com você, não quero mais saber dele.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ah, eu sabia que ia acabar assim....(chora) Por que eu não ouvi o papai! Pelo menos, ele teria ficado feliz se eu tivesse me casado com o Lucas Rodenburg.";
			link.l1 = "Me perdoe mais uma vez, senhorita...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "Por quê, Charlie? Você não tem culpa de nada. Sempre foi só gentil comigo!";
			link.l1 = "For me to tell you even more bad news. I've just returned from Curacao; Lucas Rodenburg has been arrested for sedition and treason against the Republic. He is being sent back to Amsterdam in chains to stand trial. He tried to murder Peter Stuyvesant, director of the Company. On top of that, he attempted to overthrow the governor of Willemstad and is suspected of the murder of at least one other person, so I doubt the Stadtholder is going to let him off with a slap on the wrist.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Meu Deus! Que pesadelo! Acho que vou desmaiar! Charles, é verdade? Não, por favor, diga que não é!";
			link.l1 = "Desculpe, senhorita, mas fica ainda pior. Durante a investigação das ações de Rodenburg, descobriu-se que o pirata que afundou seu fluyt agiu sob as ordens de Lucas Rodenburg. Ele travava uma guerra particular contra navios ingleses. Sinto muito, Abigail. Todos os homens que você enfrentou aqui no Caribe foram mentirosos, ladrões e assassinos.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Oh... Estou arruinada. Charles... por favor... me leve de volta para casa, para Willemstad. Eu preciso do meu papai...";
			link.l1 = "Claro, minha querida. Infelizmente, não há nada para você aqui em St. John's. Vá, arrume suas coisas, despeça-se do John e zarparemos imediatamente.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "Não, Charlie, eu é que devo agradecer a você. Se não fosse por você e pelo John, nem sei o que teria acontecido comigo. Vocês são os únicos homens honestos que conheci no arquipélago.";
			link.l1 = "Hm... você está me deixando sem graça, Abigail. Fiquei feliz em te ajudar. E sinto muito por toda essa confusão.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "Sabe, Charlie, estive pensando muito durante nossa viagem para Curaçao. Agora tudo está claro – Richard Fleetwood, Mynheer Rodenburg – tudo isso parece um pesadelo horrível que finalmente acabou. Estou de novo com meu pai e podemos voltar a uma vida normal\nMas não vai ser fácil – estamos sem dinheiro. Mas vamos superar, tudo vai dar certo. A Santa Mãe vai cuidar de nós, ela nunca esquece seus filhos, nem mesmo meu velho teimoso de pai que nega o Filho Dela.";
			link.l1 = "Senhorita Abigail, eu vou te ajudar.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "Ajudar a gente? Mas como, Charlie?";
			link.l1 = "Richard me contou sobre o naufrágio do seu navio e seu resgate. Também sei que seu pai conseguiu esconder os pertences dele em uma ilha desconhecida. Vou encontrá-la e trazer seu dinheiro de volta.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Oh Charlie... Neither my father nor I can tell you where that ill-fated island is... We are not sailors. On top of that, I was terrified for my life during the attack; I don't remember a thing besides blood and the smell of death.";
			link.l1 = "Abigail, tente se lembrar. Por favor, qualquer detalhe pode me ajudar, mesmo os menores. Aconteceu algo antes do ataque? Como é essa ilha?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "Ilha... Parece uma ilha? Uma baía, selvas. Nada me chamou muita atenção. Ah, lembrei! Talvez isso te ajude. Pouco antes do ataque dos piratas, encontramos um fluyt e chamamos o capitão dele. Ele foi convidado a bordo do nosso navio e jantou com o nosso capitão. Nós também estávamos lá. Talvez ele saiba algo sobre essa ilha.";
			link.l1 = "Isso é interessante! Quais eram os nomes do fluyt e do capitão dela?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "Eu não me lembro, Charlie. De verdade, não lembro...";
			link.l1 = "Tente se lembrar, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "Estaremos esperando por você. Ajude-me, Charlie Knippel. Você é nossa única esperança... Vou rezar por você! Que Deus te acompanhe!";
			link.l1 = "Estou a caminho. Adeus, Abi. Adeus, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Ah, que pena... Estávamos com esperança, mas... mesmo assim, obrigado, Charlie, por ao menos tentar nos ajudar quando ninguém mais quis. Parece que esse é o destino que Deus reservou para mim.";
			link.l1 = "Adeus, Abigail. Espero que você fique bem.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "É... é verdade? Você realmente trouxe nosso dinheiro perdido de volta? Oh, Charlie!";
			link.l1 = "Sim, é verdade. Eu tenho. Aqui, pegue. É todo seu.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "Como eu posso te agradecer?! Como?!";
			link.l1 = "Não precisa me agradecer, Abi. Foi o mínimo que eu poderia fazer por você. Agora você pode começar uma nova vida, sem Rodenburgs, Fleetwoods ou qualquer outro homem estranho tentando se aproveitar de você. Tenho certeza de que seu pai vai saber como fazer esse dinheiro render... parece ser um talento de família.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Charlie, não seja tão atrevido! Você fez tanto por mim, por mim e pelo meu pobre pai. Veja só, já me acostumei com a sua presença na minha vida. Tenho rezado incansavelmente por você todos os dias, e vou continuar rezando por você e pela sua tripulação à Santa Mãe todos os dias daqui pra frente! Você é o nosso anjo da guarda. O próprio Senhor te enviou para a nossa família, acredite se quiser\nAntes de você partir, quero que saiba que as portas da nossa casa estarão sempre abertas para você, a qualquer hora. E... por favor, deixe-me te beijar, meu querido Charlie...";
			link.l1 = "Bem... sim, claro, Abi... se você faz questão.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "Deus te abençoe, Charles. Nada mudou para nós... Eu peço esmolas na porta da igreja.";
			link.l1 = "Fique firme, senhorita. Que Deus esteja com você.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charles, é você! Que bom te ver! Por favor, sente-se! Vou preparar um café!";
			link.l1 = "Também estou feliz em te ver, Abi. E fico contente que você esteja bem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Ah, então é isso?! Eu te recebi como meu convidado e você decidiu me roubar?! Guardas!!!";
			link.l1 = "Cale a boca, garota tola.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
