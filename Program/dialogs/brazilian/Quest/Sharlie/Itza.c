// диалоги Уракана, Канека и прочих индейцев ица
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Precisa de alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("Outro rosto pálido... O grande sacerdote vai adorar arrancar seu coração...","O rosto pálido sabe como chegar a Tayasal, mas ninguém sai da cidade!","Estou surpreso, rosto pálido: você ainda não foi para a terra dos espíritos... Caminhe enquanto pode, logo verá seus ancestrais.");
			link.l1 = LinkRandPhrase("Muito bem, muito bem. Vamos ver...","Não tente me assustar, guerreiro de pele vermelha. Já vi coisa pior do que isso.","Vai, vai. Tenta assustar as crianças.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("Abençoa-me para a batalha contra meu inimigo, grande Cavil!","Grande Cavil e grande Kukulcán nos honram com sua presença. Nem mesmo entre os antigos maias isso acontecia!","Passamos para nossos filhos a lenda da grande batalha entre Kukulcan e Cavil!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "Você é um grande guerreiro, rosto pálido. Levamos seu sangue aos deuses. Você morre com dignidade.";
			link.l1 = "Calma aí, guerreiro de pele vermelha. Não vou deixar seu Kanek me levar como sacrifício para Kukulcan ou qualquer outro, pra falar a verdade. Seus guerreiros não conseguiram me capturar. Todos eles caíram em combate.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "Sim, você é um guerreiro generoso, rosto pálido. Mas você não conseguiria enfrentar centenas de guerreiros Tayasal Itza. Mas você disse uma palavra interessante. Como sabe sobre o grande Kanek e Kukulcan?";
			link.l1 = "Bem, deixa eu adivinhar... Já que você não é Kanek, seu nome deve ser Urakan e você é filho do sacerdote Kanek?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "Seus lábios dizem a verdade, rosto pálido. Eu sou Urakan, e estou surpreso.";
			link.l1 = "Você vai ficar ainda mais surpreso quando vir isto... Olhe.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "Oh, deuses! Se o rosto pálido tem a máscara, então chegou a hora... Você é aquele de quem Kukulcan falou. Ele nos ordenou levá-lo até ele quando você chegasse a Tayasal. Ele sabe que você veio.";
			link.l1 = "Kukulcan?! Ele está aqui em Tayasal?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "Sim, guerreiro branco. Quetzalcoatl vem para Tayasal. Em breve ele partirá para levar luz aos ancestrais, à grande cidade dos maias.";
			link.l1 = "Droga! Então, ele já está aqui...(abaixando a voz) Urakan, eu sei de tudo. Eu sei que foi você quem mandou Ksatl Cha com o Guardião da Verdade procurar Ksocheatem e a máscara de Kukulcan...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "Vejo surpresa nos seus olhos, mas também dúvida, grande chefe Urakan. Você não está satisfeito com Kukulcan, estou certo?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "Todo guerreiro Itza está feliz porque o grande Kukulcán chegou, guerreiro branco. Você deve se apresentar diante de Kukulcán. Ele esperou por você por muitas noites. Ele é um grande profeta. Sabe de tudo antes de acontecer. Vá até a Serpente Emplumada, não há outro caminho para você. Não permitiremos que você deixe Tayasal.";
			link.l1 = "Você não entende que assim que Kukulcan atravessar os portões do tempo, todos vocês, inclusive você, vão deixar de existir? E o melhor de tudo é que você vai renascer em outra forma, em outro corpo... Talvez como um simples guerreiro, ou até mesmo como um aleijado ou mendigo...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "Vá, guerreiro de pele clara. Você encontrará Kukulcan no Grande Templo dos guerreiros Itza. Siga em frente pela ponte até ver a grande pirâmide. Entre pela porta inferior do templo e aproxime-se do santuário.";
			link.l1 = "Tudo bem. Eu vou até Kukulcan, pois vejo que não vamos escapar desse encontro. Mas já te avisei.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "Vá, guerreiro branco. Kukulcán espera por você.";
			link.l1 = "Estou a caminho...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Isso se tornou realidade! Quando vi como você lutou contra Kukulcan, soube que você era o próprio Cavil. Você veio a Tayasal para salvar o povo Itza da morte causada por meu pai e por Kukulcan. Meu pai, o grande sacerdote Kanek, condenou o povo Itza em nome dos ancestrais maias há muito mortos. Eu sou o chefe de guerra Urakan, que protegeu o povo Itza por muitos anos. Nenhum rosto pálido saiu vivo de Tayasal. Meus guerreiros e eu garantimos que o povo Itza permaneça protegido e vivo por muitos, muitos anos ainda. Eu não quero sacrificar todo o meu povo.";
			link.l1 = "Eu sabia disso, Urakan. E eu pedi sua ajuda na ponte.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "Nada escapa aos olhos do grande Cavil. Perdoe Urakan por não compreender quem você realmente é.";
			link.l1 = "Não se preocupe com isso, chefe. Eu derrotei a encarnação mortal de Kukulcán, mas ainda temos uma tarefa importante pela frente – fechar os portões para o passado. Esse buraco antinatural no tempo precisa ser selado. Você vai me ajudar?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "Com o que Urakan pode te ajudar, ó Cavil?";
			link.l1 = "Você enviou Ksatl Cha com o Guardião da Verdade para procurar Ksocheatem e a máscara de Kukulcan. Então, você sabe que ela pode ser usada para fechar os portais do tempo. Seu pai te contou sobre isso?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "Pai não fala. Eu estudo os escritos no Templo do Conhecimento e da Sabedoria. Mas muita coisa não é clara para Urakan. Talvez Cavil consiga entender?";
			link.l1 = "O que exatamente você descobriu?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "Decorei de cor. O texto diz: 'Quando o sol nascer contra a chuva, e o fogo se erguer entre eles formando um triângulo, bata a perna de Tohil contra a outra e incinere a máscara de Kukulcan no altar do tempo. E sele os portões de Itzamna até o fim dos dias.'";
			link.l1 = "O quê.";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "Sim.";
			link.l1 = "Jesus... Mostre-me os portões.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "Eles estão no templo de Kukulcan. Mas a porta lá está trancada. Só meu pai pode trancá-la e destrancá-la. Quando ele abre a porta do templo de Kukulcan, ele diz: 'O sol vem e vai, a água cai e recua, o fogo acende e se apaga, guerra e paz se alternam, mas só o céu é eterno. Acima do tempo, existe apenas o céu.'";
			link.l1 = "Interessante... Vamos lembrar disso e ver o que podemos fazer...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "Eu fico aqui, lá embaixo, perto do altar do tempo. Já vi todas as pirâmides e construções de Taysal por dentro. Encontre as chaves. Eu fico aqui.";
			link.l1 = "Se eu tiver alguma pergunta importante, com certeza vou procurar você.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "Urakan pode ajudar o grande Cavil com um conselho ou uma ação?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "Dá uma olhada neste tablete que eu encontrei. Pelo lugar onde achei, deve ter alguma relação com seu pai, e claramente não é um objeto comum...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "Encontrei outra entrada no topo do Grande Templo, mas está selada. Como faço para entrar? Talvez o que eu procuro esteja lá dentro.";
				link.l1.go = "treasure";
			}
			link.l9 = "Agora não, Urakan. Eu me viro sozinho...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "Placa de pedra de Deus. Meu pai tem várias peças diferentes e elas são muito valiosas para ele. Os antigos construtores de Tayasal usavam a placa para ativar mecanismos ocultos, abrir e fechar portas, até realizar rituais mágicos.\nElas funcionam se você colocá-las no lugar certo – é isso que meu pai faz. Mas eu sou um guerreiro como você, não sei usá-las direito. Talvez Cavil saiba?";
			link.l1 = "Vamos descobrir a verdade por trás disso...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "Esta é a porta para os tesouros de Tayasal. Lá estão as riquezas dos índios Itza. Só meu pai pode abrir e fechar a porta por dentro. Ninguém ousa entrar na câmara do tesouro sem ele. Nem mesmo eu.";
			link.l1 = "Como seu pai abriu a entrada?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "Meu pai diz: 'Toda riqueza tem dois lados. Só quem conhece esses dois lados pode acessar os tesouros de Tayasal.' O que isso significa – eu não sei. Talvez Cavil possa adivinhar?";
			link.l1 = "Vamos resolver essa também...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "Você conseguiu, ó grande Cavil! O povo de Itza agora está seguro. Eu, Urakan, filho de Kanek, prometo que não mancharei a honra que você me concedeu, e vou proteger Tayasal de qualquer invasão de rostos pálidos desonrados em seu nome.";
			link.l1 = "Eu acredito nisso, chefe. Bem, agora podemos comemorar: conseguimos impedir os planos traiçoeiros de Kukulcan. Ele nunca mais vai conseguir provocar uma revolução no tempo.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Glória ao grande Cavil! Para mim e para minha geração, é uma grande honra ter visto dois deuses em Tayasal. Escrevemos esta história para nossos filhos. Eles saberão sobre a batalha dos deuses em Tayasal! Glória a Cavil! Glória!";
			link.l1 = "Preciso de uma bebida...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "Você está diante da Serpente Emplumada, rosto pálido. O espírito do poderoso Kukulcán em carne humana. Você tem sorte de ser irmão dele pelo pai de sua encarnação, assim como eu tenho sorte de ser pai de sua mãe, a mulher que o trouxe ao mundo. É uma grande honra. Talvez seja por isso que você se tornou um guerreiro forte e ainda está vivo.\nMas seu tempo vai acabar, rosto pálido. Vamos iniciar uma nova era, o tempo dos grandes maias. Vamos estabelecer nosso próprio poder e nunca mais deixar que os rostos pálidos entrem em nosso mundo. Em breve. Eu, Kanek, o sacerdote, partirei para começar o ritual!";
			link.l1 = "Maravilhoso...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "Urakan, você ouviu o que nosso senhor disse. Renda-se agora!";
			link.l1 = "Quando os grandes se enfrentam, é melhor para nós, simples mortais, ficarmos de lado e observarmos de longe, pai...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "O quê?! Caia na real, filho!";
			link.l1 = "Este homem é irmão de Kukulcán e um grande guerreiro. Vejo nele a própria encarnação de Cavil! Ninguém além dele poderia enfrentar um deus DAQUELE porte. Não há espaço para hesitação num duelo de deuses, pai! E se trouxerem oferendas a Kukulcán, meus guerreiros derramarão seu sangue para Cavil!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "Você está em seu juízo perfeito, Urakan?";
			link.l1 = "Por muitos anos, eu, chamado Hurakan, defendi com sucesso nossas terras em nome de Cavil contra a invasão de forasteiros. Centenas deles caíram sob nossos tacapes, e nenhum jamais deixou Tayasal. Mas nunca em minha vida vi um guerreiro tão forte e ágil quanto esse rosto pálido. Se ele for capaz de derrotar Kukulcan, então ele é a própria encarnação do espírito de Cavil!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
