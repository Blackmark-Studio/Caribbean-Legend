// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "O que deseja, señor? Me desculpe, é que eu estou...'soluça'... ah... me desculpe.";
					link.l1 = "Por que está tão triste, minha senhora? Lágrimas em um rosto tão bonito? O que aconteceu?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! "+UpperFirst(GetAddress_Form(NPChar))+", socorro! Assassinato!";
				link.l1 = "Hã? Matar quem? Onde? Isso é uma piada, meu caro?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Que bom te ver de novo... Obrigada por passar aqui... mas receio que agora não seja o melhor momento para conversarmos. Volte quando estiver sozinho. Aí podemos falar... de assuntos mais pessoais.";
							link.l1 = "Sempre um prazer conversar, mas preciso ir. Talvez a gente se encontre de novo.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"... Eu já estava começando a achar que você tinha esquecido o caminho até a nossa taverna. Que pena que você não está sozinho. Eu esperava que pudéssemos conversar em particular.";
							link.l1 = "Acho que o destino ainda vai nos dar uma chance de conversar em particular.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Eu sabia que você não me deixaria esperando por muito tempo. Não quero perder mais um minuto. O quarto lá em cima está livre... só pra nós. Você não vai dizer não, vai?";
							link.l1 = "Você sabe como me conquistar... Bem, não tenho motivo para resistir. Vamos?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Receio que hoje eu realmente tenha assuntos importantes para resolver. Mas prometo que, da próxima vez, vou compensar você.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"! Eu já estava começando a achar que você gostava de me fazer esperar. Não vai ficar aí parado feito uma estátua, vai? Existem maneiras bem melhores de passar o tempo.";
							link.l1 = "Ninguém resiste ao seu charme... Não faz sentido perder tempo – já estou subindo.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Você é mesmo uma tentação, Betsy... Mas infelizmente, preciso estar em outro lugar agora.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "Quero te fazer algumas perguntas.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Eu pedi pra você subir. Não fique aqui chamando atenção.";
					link.l1 = "Tá bom, eu vou, não quero te meter em encrenca...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Sou novo aqui, então, por favor, não me distraia do meu trabalho. Ainda não consegui me acostumar com isso...";
					link.l1 = "E onde está a garçonete que trabalhava aqui antes de você? "+pchar.questTemp.different.FackWaitress.Name+", pelo que me lembro...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Volte sempre, querido. Talvez a gente se divirta mais. Se ao menos eu tivesse mais tempo livre...";
					link.l1 = "Claro que vou, você foi incrível!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "Eu não te conheço, então não me incomode...";
					link.l1 = "Onde está o meu dinheiro?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Desculpe, "+GetSexPhrase("bonito","bonitinha")+", estou muito ocupado agora. É uma boa hora para a taverna, mas não para conversar!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Por favor, capitão, não brigue aqui! Dá muito trabalho limpar este lugar.";
					link.l1 = ""+GetSexPhrase("Hm... Eu nem ia fazer isso.","Eu pareço uma bêbada procurando briga? Sou só uma moça, igual a você, não se preocupe.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("Oh, capitão! Quer dividir a cama comigo esta noite? Não gosto de me gabar, mas...","Sente-se, capitão. É sempre um prazer encontrar um verdadeiro lobo do mar como você.")+"";
						link.l1 = "Que pena, estou com pressa agora. Fica para a próxima!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "Com muito prazer, querida!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Sente-se, capitão. Experimente nosso rum, jogue uma partida de cartas ou dados. Fique à vontade! É sempre um prazer conhecer um verdadeiro lobo do mar como você.";
						link.l1 = "Obrigado, linda.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Fale com o dono se quiser pedir alguma coisa. Ele está atrás do balcão.";
					link.l1 = "Obrigado pelo conselho.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Se quiser descansar e recuperar suas forças, alugue um quarto então. Ficar no salão a noite toda não vai te ajudar muito.";
					link.l1 = "Meu agradecimento.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Quero te fazer algumas perguntas.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "Então escute. Alugue um quarto aqui na taverna. Vá até lá e me espere. Eu vou entrar de fininho um pouco depois...";
			link.l1 = "Ha! Pode deixar, querido! Vou estar te esperando!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Ela não trabalha mais aqui, está aposentada... Me desculpe, tenho trabalho a fazer.";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Escuta bem, seu idiota tarado. Eu não sei onde está o seu dinheiro! E se continuar me pressionando, vou chamar os guardas e você vai acabar na cadeia!";
			link.l1 = "Tudo bem, não precisamos de guardas... Que idiota...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Exatamente, que tolo. Da próxima vez, seja mais esperto e decente.";
			link.l1 = "Eu vou tentar... (sussurrando) Maldita vadia...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Você consegue me ouvir?";
			link.l1 = "Ughh...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Não está se sentindo bem? Está com dor de cabeça?";
			link.l1 = "Droga... onde estou?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Não se lembra? Eles te roubaram.";
			link.l1 = "O quê? Ah... Minha cabeça... Quem ousaria?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "Como eu ia saber? Eles entraram correndo, ameaçaram matar, revistaram seus bolsos e foram embora.";
			link.l2 = "Entendi... Droga... Queria um pouco de água... Obrigado.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "Não, não é nada, señor... obrigado pela sua gentileza, mas eu... (chorando)";
			link.l1 = "Alguém te ofendeu? Calma, linda, me conta tudo.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Não, não, señor, não é nada. Me perdoe pela falta de controle, é só que... É o meu irmão. Dizem que ele está morto, mas eu não acredito. Eu não sei no que acreditar, mas sinto no meu coração que ele está em grande perigo. E eu não tenho ninguém além do Angelo depois que nossos pais morre... (chorando)";
			link.l1 = "Eu entendo, mas peço que se acalme, por favor. O que aconteceu com seu irmão?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Senhor... por favor, não me entenda mal, mas por que um capitão como o senhor se importaria com uma garota comum e simples da taverna? Eu nem tenho nada para lhe prometer em troca da sua ajuda... ";
			link.l1 = "Na verdade, você tem razão. Altruísmo não é pra mim, então seja forte, todos nós perdemos nossos entes queridos. C'est la vie, como dizemos na França...";
			link.l1.go = "exit";
			link.l2 = "Uma mulher sempre encontra um jeito de agradecer a um homem... Ha-ha. Agora, pare de chorar e me conte qual é o seu problema.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Jovem senhorita, você não sabe que a nossa Igreja nos ensina a ajudar uns aos outros? Vou tentar ajudá-la se eu puder, é claro.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				Notification_Reputation(false, 36, "high");
				dialog.text = "Isso foi uma 'dica'? Com licença, foi um erro meu falar com você! Adeus, 'caballero'...";
				link.l1 = "Como quiser, querido.";
				link.l1.go = "exit";
			}
			else
			{
				Notification_Reputation(true, 36, "high");
				dialog.text = "Então... Pelo menos você é honesto sobre o que deseja. Prometo que, se encontrar o Angelo ou me contar o que realmente aconteceu com ele, você terá o que pediu...";
				link.l1 = "Querida señorita, é um prazer fazer negócios com você... Agora vamos direto à história do seu irmão.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "Você está brincando comigo? Você realmente quer me ajudar de graça?";
			link.l1 = "Só um homem ruim não ajudaria uma moça chorando. Fique tranquila, eu quero mesmo te ajudar. O que exatamente aconteceu com o Angelo?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Muito bem, señor. Meu irmão, ele... ah, é difícil segurar as lágrimas, me desculpe... Nós éramos muito pobres por causa do meu... talvez por eu não ter tido sucesso no trabalho... E o Angelo começou a trabalhar com os contrabandistas locais. Ele achou que o barquinho de pesca dele daria mais dinheiro transportando algumas coisas para fugir da alfândega.";
			link.l1 = "Resumindo, seu irmão virou um criminoso, certo?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Não, señor, você não entende... ele não é assim! Ele fez isso por mim! Para me salvar de ganhar dinheiro por fora aqui... você entende o que quero dizer. Estávamos endividados e ele fez isso pela minha honra e pela minha alma. E então... ele foi pego. Não era um grande problema, até peguei mais dinheiro emprestado para pagar a liberdade dele... Mas disseram que ele morreu.";
			link.l1 = "Disseram? Quem disse? E por que você não acredita neles? Ele morreu na prisão?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Sim. Quando eu trouxe o dinheiro para pagar pela liberdade dele, o comandante me disse que Angelo tinha morrido de tuberculose. Imagine só! Ele chegou lá com saúde e morreu duas semanas depois, bem ali naquelas celas. Eles... eles nem me deixaram ver o corpo. Disseram que enterram os prisioneiros ali mesmo, perto da baía, junto ao forte, para evitar uma epidemia.";
			link.l1 = "Uma epidemia? Parece bem plausível. Então você simplesmente se recusa a acreditar nisso, ou há um motivo mais sério?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "No... No! (crying) I know it sounds foolish, but I am sure I would know if he had died. You see, Angelo was always strong - a real sailor. But there is one more thing\nMy grandpa died of consumption when I was a child, and he, an old man, had been fighting it for years! I know how it works; consumption doesn't kill people in days, trust me!";
			link.l1 = "Hm... Você também me deixou com dúvidas, tem algo muito errado aqui. Não posso te prometer nada, mas vou tentar descobrir mais.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "Até mesmo uma simples promessa já é muito mais do que eu esperava! Você é muito gentil, señor! Estarei esperando aqui!";
			link.l1 = "Oh, juventude! Tão volúvel nos sentimentos... será que poderia me devolver minha mão, beleza, ainda preciso dela, ha-ha... Muito bem então, vou dar uma olhada por aí.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "Não, nada de brincadeiras! Lá em cima! Dois bandidos estão matando um nobre! Socorro, Capitão! Só você está armado aqui!";
			link.l1 = "Corra lá fora, chame os guardas! Eu vou subir!";
			link.l1.go = "FMQP_1";
			link.l2 = "Meu caro, você deve ter me confundido com um guarda. Chame uma patrulha em caso de assassinato.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "A-ah, guardas! Me ajudem!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
