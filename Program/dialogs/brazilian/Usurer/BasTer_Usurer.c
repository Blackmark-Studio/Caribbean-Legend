// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são as suas dúvidas?","Como posso ajudá-lo?"),"Você tentou me fazer essa pergunta não faz muito tempo...","É, deixa eu adivinhar... Dando voltas de novo?","Ouça, eu cuido das finanças aqui, não respondo perguntas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar a minha memória...","Você adivinhou, me desculpe...","Entendi...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "Eu sou o capitão "+GetFullName(pchar)+". Seu homem disse que você queria me ver. Estou ouvindo.";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "Sou eu de novo, monsieur "+GetFullName(pchar)+". Eu trouxe Bertrand Pinette. Ele está no meu porão de carga.";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "Eu de novo, monsieur "+GetFullName(pchar)+". Vamos conversar.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "Sou eu de novo, monsieur "+GetFullName(pchar)+". Vamos conversar.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "Sou eu de novo, monsieur "+GetFullName(pchar)+". Suponho que você não esperava me ver novamente.";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "A-ah, Capitão "+GetFullName(pchar)+"! Que alegria te ver! Estive esperando por você já faz um tempo... Ótimo. Preciso te fazer uma pergunta. Há algum tempo, um homem chamado Bertrand Pinette te procurou no porto, querendo embarcar no seu navio. Um sujeito com cara de rico, usando uma peruca luxuosa. Isso te lembra alguma coisa?";
			link.l1 = "Sim, é isso mesmo. Ele realmente veio falar comigo com esse exato propósito.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			DelLandQuestMark(npchar);
			Log_Info("You have received a heavy purse");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "Ele queria contratar você e seu navio? Capitão, você me faria um grande favor contando todos os detalhes desse caso. Eu vou recompensá-lo por isso. Aqui, pegue esta bolsa cheia de moedas. É sua, agora por favor me conte sobre Bertrand Pinette.";
			link.l1 = "Muito bem. O senhor Pinette contratou meu navio para levá-lo, junto com dois amigos, de Guadalupe até o continente espanhol. Mais precisamente, à Baía dos Mosquitos, perto de Portobelo. Cumpri o serviço, eles desembarcaram e seguiram direto para a selva.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Entendo. E o Monsieur Pinette mencionou qual seria o destino final dele? E quanto aos companheiros dele?";
			link.l1 = "Segundo ele mesmo disse, eles estavam indo para o Panamá. Os amigos dele eram bem curiosos: dois oficiais, um espanhol e outro francês. Ainda não entendi o que os uniu, mas não fui pago para fazer perguntas.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Um oficial espanhol? E um oficial francês? Ora! Isso sim é interessante! Muito bem, monsieur Pinette! Que astúcia! Até aqui, você achou um jeito de ganhar dinheiro! Panamá, foi isso que disse?";
			link.l1 = "Sim, e eu já te contei tudo o que sei. Posso me retirar?";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "Espere, capitão. Tenho uma proposta de negócio para você. Que tal ganhar algumas moedas? Mas antes, deixe-me contar algo sobre seus passageiros.";
			link.l1 = "Bem, vamos ouvir.";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "Monsieur Bertrand Pinette chegou à nossa colônia há dois anos e imediatamente começou a fazer negócios com capitães. Negócios, bem, também um tanto obscuros... Eles lhe entregavam mercadorias que são muito escassas por aqui — objetos de valor, contrabando, até escravos às vezes... Ele pegava empréstimos sistematicamente para suas operações ilegais no meu escritório, mas sempre pagava tudo com todos os juros.\nAntes de deixar a ilha com sua generosa ajuda, ele fez um empréstimo grande, bem maior do que o habitual. Ele é... era um cliente de confiança, com um histórico de crédito impecável, por isso concedi o empréstimo. Grande erro. Monsieur Pinette fugiu e, obviamente, não tem intenção nenhuma de devolver meu dinheiro.";
			link.l1 = "Qual é o valor da quantia, se me permite perguntar?";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "É enorme. Cerca de cento e cinquenta mil pesos em dobrões. Dez baús, cada um com cento e cinquenta dobrões. E isso sem nem contar todos os juros.";
			link.l1 = "Hm... Ele vinha te pagando por dois anos, te deixou acostumado, pegou um empréstimo considerável e depois sumiu. Esperto.";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "Exatamente, capitão. É por isso que quero contratá-lo para um serviço: encontre esse canalha e traga-o até aqui. O governador, o comandante e eu vamos dar um jeito de fazê-lo quitar a dívida. Você já viu esse homem, ele foi seu passageiro, o que significa que tem mais chances de encontrar o monsieur Pinette do que qualquer outra pessoa. Claro, também vou contratar caçadores de recompensas profissionais para ir atrás desse infeliz, mas tenho a sensação de que sua ajuda será mais eficaz.";
			link.l1 = "E quanto à recompensa?";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "Por fazer o serviço, vou te dar um baú cheio de dobrões, cento e cinquenta moedas.";
			link.l1 = "Eu diria que isso seria uma recompensa bem patética por caçar e sequestrar uma alma viva numa cidade espanhola.";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "Capitão, presumo que Monsieur Pinette tenha lhe pago bem com o meu dinheiro, já que valoriza tão pouco a minha proposta. Garanto que vale a pena. É claro, você tem todo o direito de recusar... mas tenho algo a lhe dizer, e certamente isso vai fazê-lo mudar de ideia.";
			link.l1 = "E o que é isso?";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "Alguns dias antes da fuga de Pinette de Guadalupe, um prisioneiro escapou da prisão em Basse-Terre. O nome dele é Don Carlos de Milyar, um grande nobre espanhol e oficial. Ele conseguiu isso graças à traição de um oficial francês, um tenente dos Fuzileiros... Você entende o que quero dizer?";
			link.l1 = "Hm... E o que isso tem a ver comigo? Eu só estava transportando passageiros, nada além disso.";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "Claro que estava! Pessoalmente, não tenho dúvida de que você não teve nada a ver com a fuga do Don de Milyar. Mas não é assim que o nosso governador, junto com o comandante, pode enxergar a situação. Se tiver sorte, vão te acusar de cumplicidade, e se não tiver... Prefiro nem continuar. Veja você mesmo, capitão: você acolheu um oficial espanhol fugitivo a bordo, provavelmente em alguma enseada escondida... estou certo, capitão?";
			link.l1 = "Entendi. Você está me chantageando. Foi um erro ter vindo aqui...";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "O que me diz, capitão?! Eu não estou te chantageando! Só estou pedindo sua ajuda em troca de uma boa recompensa. Poderia ser gentil o bastante para encontrar o monsieur Pinette e levá-lo até Basse-Terre? Estarei esperando seu retorno. Acredito que dois meses sejam suficientes para ir até o Panamá e voltar.";
			link.l1 = "Você não me deixa escolha. Embora eu duvide que esse tipo de abordagem comercial vá nos tornar amigos. Adeus, monsieur.";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - Старт квеста "Мерзкий Божок"
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ótimas notícias, capitão! Vou mandar meus homens buscarem esse desgraçado no seu navio imediatamente. Dessa vez esse sujeito não vai escapar de mim... Você ganhou sua recompensa, pegue este baú. Por favor, não fique bravo comigo, aqui está um amuleto para você. Considere um presente.";
			link.l1 = "Minha gratidão. Imagino que seu silêncio também faz parte da minha recompensa?";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("You have received a chest full of doubloons");
			Log_Info("You have received a 'Fisherman' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "Silêncio? Sobre o quê? Ficarei feliz em tê-lo entre meus clientes. Sabe o que dizem sobre o silêncio e o ouro?";
			link.l1 = "Às vezes, vale muito mais do que ouro, monsieur. Lição aprendida. Adeus!";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "Estou ouvindo. Presumo que Bertrand Pinette está no seu navio?";
			link.l1 = "Não. Mas tenho algo muito melhor para você. Leia isto.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "O que é isso?";
			link.l1 = "Continue lendo, monsieur. Continuaremos depois.";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(lendo) Hum ... O que é essa bobagem sobre um paciente febril?";
			link.l1 = "Está falando sério? Muito bem, vou levar essa 'história' ao governador. Acredito que ele ficará bastante interessado em saber a verdade sobre o desaparecimento do 'Courage' e sua carga de diamantes... Por que ficou tão pálido?";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "Então, você acabou encontrando o Pinette...";
			link.l1 = "Sim. Então eu lhe proponho um acordo. Esqueça Carlos de Milyar, Jean Deno e os outros cavalheiros, faça isso e eu esquecerei esta carta.";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "Muito bem, capitão... Concordo com seus termos.";
			link.l1 = "Que ótimo. Espero que não esteja zangado comigo, acho que terminamos por aqui. Adeus.";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "Ha... Você tem razão, capitão.";
			link.l1 = "Tenho algo para você. Pegue isto e leia.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "Então, você acabou encontrando o Pinette...";
			link.l1 = "Sim. Então eu lhe proponho um acordo. Restaure meu bom nome nas colônias francesas e eu esquecerei esta carta.";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "Mas...";
			link.l1 = "Não me importa como você vai fazer isso. Se a caçada pela minha cabeça não acabar até amanhã, o governador vai saber de tudo.";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
