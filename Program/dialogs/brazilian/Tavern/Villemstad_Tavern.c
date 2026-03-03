// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" às suas ordens. O que gostaria de saber?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Esta é a terceira vez hoje que você faz essa pergunta...","Você está repetindo as mesmas coisas feito um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","É...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "Ouvi dizer que houve problemas sérios na ilha... Escravos?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "Ouvi dizer que aquele canalha miserável, Bart, o Português, finalmente foi pego pela justiça! Ele está preso? Você sabe quando vai ser a execução dele? Quero ir assistir, tenho uma conta a acertar com esse desgraçado...";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "Escute, "+npchar.name+", ouvi dizer que você contratou uma garçonete linda há pouco tempo... e ela já sumiu?";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "Me conte, "+npchar.name+", na noite em que a Betsy desapareceu, você notou alguém suspeito por perto? Talvez ela estivesse conversando com alguém?";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{			
				sld = CharacterFromID("Villemstad_waitress");
					if (CheckAttribute(sld, "model") && sld.model != "Marquesa")
					{
						link.l1 = "Bem, "+npchar.name+", boas notícias – sua preciosa garçonete está viva e bem. Você vai ter que reabastecer o rum, logo o povo vai voltar.";
						link.l1.go = "TBP_Tavern3_21";
					}
					else
					{
						link.l1 = "Bem, "+npchar.name+", está feito – sua preciosa garçonete voltou. Melhor começar a estocar rum de novo, logo o pessoal vai voltar.";
						link.l1.go = "TBP_Tavern3_21_1";
					}
				
			}
			//<-- Тайна Бетси Прайс
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Pois é, nunca houve uma confusão dessas... Mais de mil negros se revoltaram. Duas plantações foram queimadas até o chão e cada um dos seus donos foi assassinado. O comandante está preocupado que os escravizados possam atacar a cidade, então ele decretou lei marcial. E tudo começou por causa de dois negros, um chamado Tamango e uma chamada Isauri...";
			link.l1 = "Parece bem dramático. Conte-me a história toda, quem são esses negros?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango e Izaura — escravizados na plantação Blenheim, a primeira a ser incendiada. Esses dois negros se amavam. Mas o filho do fazendeiro, Leonsio, chegou da Europa e se encantou pela moça. Queria fazer de Izaura sua concubina particular. Tamango não gostou nada da ideia, e Izaura também não — ela amava de verdade aquele diabo negro. Dizem que Tamango era uma espécie de chefe ou algo assim lá na África... Um homem enorme — mais escuro que a noite e mortal com um machado, os outros negros o temiam e respeitavam. Então ele liderou os outros escravizados numa revolta. Atacaram os guardas à noite, mataram todos os brancos fora da casa grande, até os mulatos. Depois Izaura abriu as portas da fazenda e os rebeldes mataram todos lá dentro. Blenheim foi reduzida a cinzas. Depois disso, os escravizados fugiram para a mata e sumiram...";
			link.l1 = "Então, que história, hein? Parece até enredo de romance! Uma revolta de escravos de verdade, igual na Roma Antiga. Como foi que você descobriu tudo isso, aliás?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Boatos, senhor, o mundo está cheio deles. O rum solta as línguas, é só prestar atenção...";
			link.l1 = "E como tudo isso terminou? Eles encontraram aqueles negros?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "Ha, nem pensar! Até que os reforços finalmente conseguiram chegar, ninguém se atreveu a entrar na selva. Depois, um navio de guerra da Companhia apareceu com um destacamento de soldados e eles vasculharam a ilha. Não encontraram nem sinal, nem um fio de cabelo de um único negro fugitivo.";
			link.l1 = "Olha só! Mil negros simplesmente desapareceram no ar?";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Na verdade, dentro d'água.";
			link.l1 = "Do que você está falando, "+npchar.name+"? Você sabe tão bem quanto eu que negros não sabem nadar.";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "He-he... ah, não, aqueles pretos não viram comida de tubarão tão rápido assim. O lance é que, na noite seguinte ao motim, uma barca sumiu do cais. Pode me pintar de preto e me fazer tocar banjo e dançar pra você se não foi aquele tal de Tamango e os negros dele! Por isso que eles não estão mais na ilha.";
			link.l1 = "Ha, agora eu ouvi de tudo, "+npchar.name+". Você espera que eu acredite que um bando de negros meio selvagens consegue manejar velas e navegar? Eu acreditaria mais se um navio cheio de macacos viesse desgovernado da Guiné.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Eu também não acreditei, senhor, mas a prova está no navio desaparecido. Vai ver algum daqueles negros já trabalhou como camareiro em um navio e aprendeu umas manhas de navegação. Ou então usaram feitiçaria, vai saber! Passe aqui de novo para me visitar, "+pchar.name+", vou ter mais histórias para você da próxima vez.";
			link.l1 = "Obrigado! Bem, está na hora de eu ir.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Sim, é isso mesmo. Pegaram aquele pirata. E você acredita como? Encontraram ele sozinho num barquinho no meio do mar. Nem teve tempo de reagir antes de ser jogado no porão junto com os ratos. Engraçado, né? Um pirata tão perigoso ser capturado desse jeito, feito um marinheiro de primeira viagem!";
			link.l1 = "E por que ele estava sozinho no mar?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Provavelmente ele resolveu se separar dos capangas, sem dúvida... Não conseguiram dividir o saque de forma justa. Agora ele está nas mãos da própria Companhia, e aquele pessoal não gosta de brincadeiras. Dizem que ele se apossou de um dos barcos da Companhia com algo valioso. Pelo visto, só não está pendurado numa corda porque querem arrancar alguma informação dele.";
			link.l1 = "Então, você sabe quando vai ser a execução dele?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Nobody knows. I think once the Company finds out what it wants, they'll fasten a hemp tie around his neck. The Portuguese is in prison right now under reliable guard\nRecently they brought his boatswain over here as well. His story was even more surprising; he turned himself in to the Dutch in Philipsburg. So, they've set him up in a cell right next to his former captain, so they're neighbours now, he-he...";
			link.l1 = "Milagres acontecem! Tudo bem, vou ficar de olho nas novidades. Não quero perder esse enforcamento. Tchau, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "Ah, se você tivesse visto ela, Capitão! Betsy... tanta graça, um sorriso encantador! Os homens vinham aqui só para olhar para ela. E as moedas de prata que deixavam na minha taverna... Mas faz três dias que ela não aparece para trabalhar. Claro que mandei gente até a casa dela, mas ela não estava lá. O lugar estava uma bagunça, os pertences dela tinham sumido\nJá não sei mais o que pensar. Os guardas, como sempre, só deram de ombros. Disseram que têm coisas mais importantes para fazer do que procurar uma moça desaparecida. Falaram que ela provavelmente só saiu e logo volta. Capitão, será que você poderia encontrá-la? Se trouxer ela de volta, te pago cem dobrões. Não posso simplesmente perder essa garota, entende? Ela é um verdadeiro tesouro! Preciso trazê-la de volta custe o que custar!";
			link.l1 = "Vamos ver o que posso fazer. Ela agiu de forma estranha antes de desaparecer, ou recebeu alguma notícia ruim?";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "Procurar por uma garota que provavelmente só fugiu? Tenho coisas mais importantes pra fazer. Resolva isso você mesmo.";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "No último dia antes de sumir, ela saiu animada, até feliz! Nenhum sinal de problema, nem uma palavra sobre ir embora. Simplesmente desapareceu!";
			link.l1 = "Interessante... Onde posso encontrar a casa dela?";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "Ela morava mais acima na rua, numa cabana logo atrás da casa em frente à mansão com a varanda azul. Não fica longe daqui.";
			link.l1 = "Então tá, não vou perder tempo. Se eu descobrir alguma coisa, te aviso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "Desconfiado? Sempre havia uma multidão de pretendentes ao redor dela, e cada um era suspeito à sua maneira! Ela era uma grande sedutora, sabia como chamar atenção.";
			link.l1 = "Isso eu já percebi"+GetSexPhrase(""," fora")+" já. Mas teve alguém que se destacou?";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "Hmm... Bem, teve um. Naquela noite, ele deu a ela um pingente com pedras preciosas. Ficou sentado aqui, olhos grudados nela, rondando por aqui a noite toda.";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "Esse pingente, por acaso, não seria este aqui? (Mostra o camafeu comprado do mendigo)";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "Pingente com pedras preciosas, é isso que você diz...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "É esse mesmo! Exatamente! Capitão, já encontrou alguma coisa?";
			link.l1 = "Depois te conto os detalhes, "+npchar.name+", agora não temos tempo a perder.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Given: Cameo pendant", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "Isso é maravilhoso, Capitão! Já estava começando a achar que nunca mais a veria. Então, o que aconteceu? Ela realmente queria fugir?";
			link.l1 = "Digamos que ela precisou lidar com alguns problemas do passado. Mas parece que tudo isso já ficou para trás, e logo ela estará de volta ao trabalho.";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "Bem, digamos que ela precisava de uma pausa de olhar pra sua cara sem graça. Ha-ha! Não faça essa cara, estou brincando. Toda dama tem direito aos seus segredinhos...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "Bem, o mais importante é que ela vai voltar ao trabalho. Você merece sua recompensa, Capitão. Aqui, pegue – cem doblões, como combinado. E também, leve este mapa. Um dos clientes deixou aqui e nunca mais voltou. Parece que leva a um tesouro.";
			link.l1 = "Então tá, vou dar uma olhada. Valeu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune":
			dialog.text = "Bem, o principal é que ela vai voltar ao trabalho. Você merece sua recompensa, Capitão. Aqui, pegue – cem dobrões, como combinado. E também, leve este mapa. Um dos clientes deixou ele aqui e nunca mais voltou. Parece que leva até um tesouro.";
			link.l1 = "Então tá, vou dar uma olhada. Valeu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		
		case "TBP_Tavern3_21_1":
			dialog.text = "Você me salvou, capitão! Eu já tinha quase perdido as esperanças de vê-la de novo... Mas me conta, o que aconteceu afinal? Ela realmente estava pensando em fugir? Eu não tive coragem de perguntar pra ela mesmo.";
			link.l1 = "Digamos que ela teve que resolver alguns assuntos pendentes do passado. Mas parece que tudo isso ficou para trás agora, e logo ela estará de volta ao trabalho.";
			link.l1.go = "TBP_Tavern3_22_leadership_1";
			link.l2 = "Bem, digamos que ela precisava de uma pausa de ficar olhando pra sua cara sem graça. Ha-ha! Não faz essa cara feia, tô só brincando. Toda mulher tem direito aos seus segredinhos...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership_1":
			dialog.text = "Bem, o importante é que ela voltou ao trabalho. Você merece sua recompensa, capitão. Aqui está – cem dobrões, como combinamos. E também, leve este mapa. Um dos hóspedes deixou aqui e nunca mais voltou. Pelo que parece, ele leva até um tesouro.";
			link.l1 = "Tá certo, vou dar uma olhada. Obrigado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune_1":
			dialog.text = "Bem, o importante é que ela voltou ao trabalho. Você merece sua recompensa, capitão. Aqui está – cem dobrões, conforme combinamos. E também, leve este mapa. Um dos hóspedes deixou aqui e nunca mais voltou. Pelo que parece, ele leva a um tesouro.";
			link.l1 = "Tá certo, vou dar uma olhada. Valeu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
