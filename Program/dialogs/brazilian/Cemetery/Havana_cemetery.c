// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Como posso ajudar você?","O que posso fazer por você?"),"Me diga, o que te aflige, "+GetAddress_Form(NPChar)+"?","Pela terceira vez, "+GetAddress_Form(NPChar)+", o que você precisa?","Já cansei de você. Cai fora!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, me desculpe.","Não é nada, com licença."),"Me perdoe, não é nada.","Você tem razão, já é a terceira vez. Me desculpe...","Desculpe.",npchar,Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Escute, você viu ou encontrou um homem chamado Joachim Merriman, aqui em Havana ou nas redondezas? Ele é um senhor de meia-idade, português, com bigode, barba em ponta e olhos penetrantes. Talvez em alguma enseada ou na selva? Estou procurando por ele.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "N-não, marinheiro, c-com certeza não. Raramente recebo visitas aqui embaixo, sabe, ahm... e eu... eu n-não vi ninguém parecido com o homem que você descreveu, então...";
			link.l1 = "Sério? Então por que está gaguejando e desviando o olhar? Não minta pra mim agora, você sabe a verdade. É melhor me dizer de novo – você viu esse homem?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "E-eu juro, senhor, n-não vi ninguém! E-eu gaguejo d-desde criança...";
			link.l1 = "Mentiras, tudo mentira. Vejo isso nos seus olhos. Onde ele está, onde está Merriman?! Fale, AGORA!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Eu não conheço nenhum Merriman! Nunca ouvi esse nome antes também! E nem pense em me ameaçar ou o Comandante vai te enforcar no forte! Então pense bem no que vai fazer, garoto!";
			link.l1 = "Ah, é mesmo? Muito bem. Agora, preste muita atenção: Joachim Merriman é um feiticeiro. A Santa Inquisição está atrás dele. Muitos anos atrás, na Europa, ele foi condenado à fogueira por profanar túmulos, violar os mortos e praticar bruxaria. E eu sei com certeza que agora ele está escondido em algum lugar, aqui, nos arredores de Havana...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "...recentemente eu limpei a caverna próxima dos zumbis e sei quem é o responsável! Ora, para onde mais Merriman iria, senão para o cemitério! Você sabe onde ele está. Mas tudo bem, não vou encostar um dedo em você, mas vou fazer uma visita aos Inquisidores em Santiago. O padre Vincento vai achar muito interessante saber que Joachim Merriman está se escondendo no cemitério de Havana com seu cúmplice, o vigia local...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "...Já ficou pálido? Dou-lhe minha palavra de nobre: um dia depois que eu relatar o que descobri, a ilha inteira vai estar cheia de soldados espanhóis. E você vai ser torturado, suplicando e chorando até contar onde esse feiticeiro está escondido. Logo depois, será queimado na fogueira como cúmplice dele, enquanto assisto ao auto de fé. O que acha disso?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "P-por favor, señor! Eu não tenho nada a ver com isso, eu juro! Eu... eu simplesmente não consegui fazer nada... Como eu poderia enfrentá-lo?! Ele é um homem terrível, ele pode... você não faz ideia do que ele é capaz! Misericórdia, eu imploro!";
			link.l1 = "Confie em mim, eu sei do que ele é capaz. Vi com meus próprios olhos. Então? Onde ele está? Me diga e eu prometo que não vou te envolver nessa história.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Ele... Ele está escondido numa caverna debaixo do cemitério. Só dá pra chegar lá pela porta da capela. Quando ele sai, eu me escondo em casa e fico lá. Você não faz ideia do quanto eu queria me livrar desse horror!\nMas eu não teria coragem nem de chegar perto. Eu... eu vi ele cavando uma cova nova, e então... então o morto se levantou e ficou vagando pelo cemitério ao luar! Quase perdi a razão naquela hora! Mas Merriman me proibiu de sair. Ele ameaçou que, se eu deixasse minha casa sem a permissão dele, nem que fosse por meio dia, ele me encontraria e me transformaria naquela abominação... um esqueleto ambulante!";
			link.l1 = "Com que frequência ele sai da caverna dele?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Bem, eu levo comida e poções de cura da cidade pra ele e... tudo mais que ele pedir. Ele sai uma ou duas vezes por mês... quando a lua está cheia. Deixa um bilhete na porta, escreve o que precisa... E-eu entrego e deixo na porta, e ele pega quando volta.";
			link.l1 = "Entendi. Aquela porta para o covil dele – está trancada de alguma forma?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "É sim. Está sempre trancado. É muito resistente, e a fechadura é enorme e complicada.";
			link.l1 = "Hm... Merriman não é nenhum tolo, com certeza ele deve ter outra saída do covil, igual à casa dele na Europa. Se a gente arrombar a porta, ele vai escapar e nunca mais será encontrado. Hmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Senhor, você jura que não vai me entregar para a Inquisição?";
			link.l1 = "Eu te dei minha palavra, e a palavra de um nobre é sagrada. Juro que não vou te entregar.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Oh, que Deus te abençoe, Señor! Eu sei como chegar até a caverna. Existe uma chave, uma segunda chave... Eu tenho ela. Merriman não sabe que há duas chaves para aquela fechadura. Eu jamais teria coragem de entrar, mas você...";
			link.l1 = "Me entregue a chave, e eu vou te livrar deste pesadelo.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Aqui está, senhor. Você vai mesmo entrar na toca dele?";
			link.l1 = "Sou eu. Tranque-se em casa e espere lá enquanto eu entro. Se eu não voltar, largue tudo e fuja o mais rápido que puder.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Mas tome cuidado, senhor. Sons assustadores foram ouvidos vindos da caverna dele e temo só de pensar quem poderia habitá-la. Mas Merriman não está sozinho — disso tenho certeza.";
			link.l1 = "Vou tomar todas as medidas que puder. Adeus.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
