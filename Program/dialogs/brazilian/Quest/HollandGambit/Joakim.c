// Жоаким Мерриман - португальский сумрачный гений
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
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Bom dia, senhor! Sou o doutor Joachim Merriman. Tenho o prazer de falar com o capitão "+GetFullName(pchar)+"?";
					link.l1 = "Sim, sou eu. Como diabos você sabe meu nome? Não me lembro de já ter te visto antes.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "Fico feliz em vê-lo, capitão. Pelo seu jeito animado, vejo que está prestes a me deixar muito contente. Você trouxe o crânio de Yum Cimil?";
					link.l1 = "Eu tenho o crânio de que você fala. Ele praticamente pulsa de energia, como uma fornalha em chamas.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Tem mais alguma coisa a dizer, capitão?";
				link.l1 = "Não, senhor Merriman. Eu estou indo embora..";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Bom dia, senhor! Sou o doutor Joachim Merriman. Tenho o prazer de falar com o capitão "+GetFullName(pchar)+"?";
					link.l1 = "Sim, sou eu. Como diabos você sabe meu nome? Não me lembro de ter te encontrado antes.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "Fico feliz em vê-lo, capitão. Pelo seu jeito animado, já percebo que você vai me deixar muito satisfeito. Trouxe o crânio de Yum Cimil?";
					link.l1 = "Eu tenho o crânio de que você fala. Ele praticamente pulsa de energia, como uma fornalha em brasa.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Tem mais alguma coisa a acrescentar, capitão?";
				link.l1 = "Não, doutor Merriman. Eu estou indo embora.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Bom dia. Você quer algo de mim?";
			link.l1 = "Não, desculpe.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "Se você veio ver o Doutor Merriman, ele não está aqui. Ele não mora mais aqui.";
			link.l1 = "Entendi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "Se você veio ver o doutor Merriman, preciso avisar que ele não está em casa. Ele está viajando no momento e não sei quando vai voltar.";
			link.l1 = "Entendi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "Se você veio ver o doutor Merriman, ele não está aqui. Ele não mora mais aqui.";
			link.l1 = "Entendi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Seus assuntos não são tão privados quanto você imagina, capitão! Mas não se assuste, tenho uma proposta para você! Sou um homem de ciência, um tipo de filósofo natural, estudando a fascinante cultura dos pagãos indígenas do litoral espanhol e das Índias Ocidentais. Você poderia me acompanhar até minha casa para conversarmos sobre detalhes potencialmente muito lucrativos na minha sala de estar?";
			link.l1 = "Você tem minha curiosidade e minha atenção. Mostre o caminho.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "Você não vai recusar isso, senhor! Minha casa fica perto daqui. Venha comigo!";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Podemos conversar aqui sem medo de ouvidos curiosos. Você visitou recentemente meu vizinho, Solomon Shneur. Eu estava apenas passando e, me perdoe, Capitão, acabei ouvindo sem querer alguns detalhes da sua conversa com Solomon. Estava tudo tão interessante que precisei escutar até o fim!";
			link.l1 = "Um bisbilhoteiro com medo de outros bisbilhoteiros, hein?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "Calma, calma, capitão! Não é nada disso! O Salomão é meu vizinho e sempre vem me visitar. Somos bons amigos, apesar das nossas diferenças religiosas! Sei das desventuras dele... assim como todo mundo em Willemstad! Salomão vive contando suas aflições pra quem quiser ouvir, de manhã, à tarde e à noite. Mas chega disso. O velho judeu já deve ter te falado de um crânio de jade antigo que está escondido junto com o ouro dele numa ilha desconhecida. Ele te contou sobre isso?";
			link.l1 = "Ele me falou sobre um crânio, mas não disse que era feito de jade. Também disse que era o crânio do avô dele. Pra ser sincero, achei que fosse alguma coisa cabalística assustadora, ou que o velho era meio maluco da cabeça.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "Não, capitão, Solomon é perfeitamente são, só um pouco excêntrico. O crânio realmente existe. É um antigo tesouro indígena, o crânio de jade de Yum Cimil! Não faço ideia de como o velho judeu conseguiu pôr as mãos nisso. Passei metade da minha vida procurando por ele. Encontre aquela ilha onde Solomon escondeu a fortuna da família. O crânio deve estar lá, no baú dele. Traga esse crânio de jade para mim e eu te pago meio milhão de pesos.";
			link.l1 = "Meio milhar? Isso mal vale o meu tempo— espera aí... você disse meio milhão de peças de oito?! Você tá brincando comigo? Nunca vi tanto dinheiro junto na minha vida!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "Você ainda é um homem jovem, capitão... Então, vai aceitar? Você me entrega o crânio de jade e eu te dou quinhentos mil peças de oito em troca. Fechado?";
			link.l1 = "Ha, uma fortuna por um crânio velho? Claro que eu topo.";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Excelente. É sempre um prazer trabalhar com alguém que entende de lucro. Se precisar de mim, estarei aqui em casa. Boa sorte!";
			link.l1 = "Obrigado, doutor Merriman. Não vou te fazer esperar muito.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "Oh, sim! Você está absolutamente certo sobre o poder disso... Mas chega de conversa, deixe-me ver, estou tremendo de impaciência.";
			link.l1 = "Aqui, por favor, pegue. Espero não ter me enganado?";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "Ah, incrível! Sim, é isso mesmo. Excelente, capitão, simplesmente excelente! Finalmente! Está comigo, finalmente! Esperei por esse momento durante tantos anos!";
			link.l1 = "E o dinheiro que você prometeu, Doutor Merriman?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "Ah, sim, claro! Meio milhão de peças de oito. Pegue, você merece.";
			link.l1 = "Foi um prazer fazer negócios com você. Difícil acreditar que uma coisa tão pequena possa valer tanto...";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "Coisa pequena? Você não faz ideia do que está falando. Isto é... bah, sua mente de filisteu mal consegue compreender a magnitude do poder incrível por trás deste crânio precioso. Pra falar a verdade, nem tenho tempo a perder agora\nObrigado, capitão, pelo que fez. Agora é hora de me despedir. Preciso ir.";
			link.l1 = "Adeus, Doutor Merriman. Talvez nos encontremos novamente.";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Podemos conversar aqui, capitão. Sei que você é um conhecido próximo de Abigail Shneur, filha do meu vizinho Solomon. Ela partiu no seu navio para encontrar seu amante... mas isso não importa de verdade.";
			link.l1 = "O que está querendo dizer, doutor?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "Se você conhece o Solomon, então deve saber da história dele sobre o naufrágio e os tesouros perdidos que ele escondeu em alguma ilha desconhecida. Ele já contou essa história para todo mundo em Willemstad.";
			link.l1 = "Por que você acha que eu não só ouvi falar disso, mas também me importo com as desgraças do velho judeu?";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "Você não gosta do Solomon? Te garanto, ele é só um velho excêntrico inofensivo. Esqueça ele. Vamos falar de negócios\nTive várias conversas longas com Solomon. Você nem imagina como me senti quando descobri que esse velho judeu possui um artefato antigo e inestimável que procuro há anos! O velho maluco escondeu isso, junto com seu dinheiro miserável, em alguma ilha e nem consegue lembrar onde fica\nEu preciso desse artefato. Traga-o para mim e eu te pago meio milhão de peças de oito.";
			link.l1 = "Meio milhão de peças de oito? Só pode estar brincando, doutor. Nunca vi tanto dinheiro junto na minha vida!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "Você ainda é um homem jovem. Então, vai aceitar? Você me entrega o crânio e eu te dou quinhentos mil peças de oito em troca. Além disso, pode ficar com o dinheiro do Salomão também. Segundo o velho, deve ter por volta de duzentos mil pesos... Então, setecentas mil peças de oito no total pra você. Negócio fechado, capitão?";
			link.l1 = "Que eu caia morto! Claro que é um acordo! Mas como é que eu vou encontrar essa ilha?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Fale com a Abigail. Talvez ela se lembre de algo. Pergunte ao Solomon. Veja, se eu soubesse onde encontrar a ilha, não estaria pedindo sua ajuda em primeiro lugar.";
			link.l1 = "Entendi. Desculpe pela minha pergunta tola. Agora, preciso encontrar essa ilha. Só garanta que estará esperando com o meu pagamento.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Exatamente. Fico feliz que nos entendemos, capitão. Boa sorte na sua busca. Pode sempre me encontrar aqui na minha casa.";
			link.l1 = "Não vou te fazer esperar muito, doutor Merriman. Até logo!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "Yesssss. As pedras do sacrifício estão manchadas com o sangue dos meus inimigos! Yum Cimil me concedeu o poder de comandar os mortos! Com esse poder, em breve dominarei os vivos!";
			link.l1 = "Muito melodramático, Merriman. O que você pretende fazer com seu exército de cadáveres ambulantes? Vai bancar o César e tentar conquistar o mundo?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "Silêncio, seu tolo! Você realmente achou que eu revelaria meu plano secreto em um monólogo?! Bem, não vejo motivo para não fazê-lo, já que você não vai sobreviver a este encontro! Minhas legiões de mortos-vivos vão ocupar primeiro todas as cavernas escuras e masmorras do Caribe. Meus postos avançados estarão em cada vila, aguardando meu sinal. E quando chegar a hora, meus cadáveres ambulantes vão marchar e tomar as terras dos vivos!\nPena que você não vai estar vivo para ver isso, seu patético certinho, esse protagonista de araque! Você entrou no meu santuário – e não vai sair daqui com vida! Eu vou liderar meu exército das trevas!";
			link.l1 = "Escuta, camarada, você não está liderando nada além do João e porcaria nenhuma, e até o João já foi embora da cidade.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "Oh ho ho! Você ousa me desafiar e enfrentar meus servos esqueléticos?! Então veja quem eu realmente sou, e trema de medo!";
			link.l1 = "Vem pegar um pouco.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "Ahhh! Doce Jesus!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "Agora você entende quem está na sua frente, seu verme chorão?! Eu tenho uma conta a acertar com você! O próprio Yum Cimil está do meu lado! Eu vou devorar sua alma!";
			link.l1 = "Beleza, cabeçudo. Vamos dançar.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é um "+GetSexPhrase("Ladrão, senhor! Guardas, peguem ele","Ladra, menina! Guardas, peguem ela")+"!!!","Olha só isso! Assim que virei as costas, você foi mexer no meu baú! Ladrão! Peguem o ladrão!!!","Guardas! Roubo! Peguem o ladrão!!!");
			link.l1 = "Droga!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
