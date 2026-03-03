void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Sejam bem-vindos à minha casa, senhores. Em que posso ajudar?";
			link.l1 = "Levasseur manda lembranças, monsieur.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "Então é assim... Alicia! Nos deixe a sós, por favor. Esses cavalheiros têm assuntos comigo.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "Mas...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Eu te amo, querida. Vai lá então!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Anri_DlgExit_1");
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Obras maravilhosas, ó Senhor! Valeu a pena perder tudo para encontrar o amor da sua vida no fim do mundo! Senhores, estou todo à disposição. Imagino que não vamos conseguir chegar a um acordo?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "Não, e nem tente pedir misericórdia.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "Não é apropriado para um Cavaleiro da Ordem pedir misericórdia.";
			link.l1 = "Um ex-cavaleiro, no entanto.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "Nem todos os burocratas do mundo, com toda a tinta que têm, conseguiriam tirar esse título de mim.";
			link.l1 = "Nesse caso, prove.  Mas antes, mate minha curiosidade: Você é um traidor da Coroa? Caso contrário, não entendo por que Levasseur queria tanto a sua cabeça.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Sou fiel ao meu juramento, monsieur, então não me culpe por isso. Só digo que um traidor da Coroa me enviou para eliminar outro traidor. E ele vai continuar fazendo isso, vez após vez, até que um Irmão mais capaz do que eu tenha sucesso. Chega de conversa. Senhores, à batalha!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Anri_DlgExit_2");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "Ah-ah! Oh, obrigado, Capitão. Ele era um diabo duro de roer. Eu jamais teria conseguido derrotá-lo sozinho.";
			link.l1 = "De algum jeito, não me sinto muito feliz com essa vitória. Acho que terminamos aqui, não?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Não exatamente, primeiro precisamos limpar a área e eliminar a garota que fugiu tão rápido para o segundo andar.";
			link.l1 = "O quê?! Acalme-se! Você ficou louco, Claude? Eu não sou um carniceiro!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "Você não precisa fazer nada, capitão. Aliás, a culpa é toda sua: não devia ter falado do Levasseur pra ela.";
			link.l1 = "Isso é besteira e você sabe disso. E se ousar me dar outra bronca sem sentido, não vai sair impune.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Heh! Foi mal, Capitão. É verdade, as ordens do Levasseur deixavam claro que era pra eliminar não só o cavaleiro, mas todos os companheiros dele. Todos, entendeu? Esse pessoal não é de brincadeira e as exigências deles precisam ser levadas a sério. Não me impede de fazer meu trabalho, Cap. Só mais um serviço sujo e depois fico com você até o fim, eu juro!";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Confiável) (Honra) Você disse uma vez que eu estava destinado a voar alto, e ficou feliz em ajudar nisso.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
			}
			link.l2 = "Vai pro inferno! Faça seu trabalho sujo. Aceito seu juramento, e é bom que você o leve muito a sério. Estamos entendidos?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Por esse preço, não, Claude. Não vou deixar você matar aquela garota.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Heh! Acho que estávamos destinados a nos matar, hein, Capitão?";
			link.l1 = "Acho que sim. Vamos continuar de onde paramos em Tortuga, certo?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_3");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Sim, senhor, Capitão!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_4");
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "Está feito, capitão. Ela realmente me surpreendeu...";
			link.l1 = "Não quero ouvir sobre isso. Cumpri minha palavra. Agora é a sua vez.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "O ouro é uma coisa, mas arriscar a própria pele por um simples mercenário vale muito mais. Estou com você até o fim, Capitão.";
			link.l1 = "Nesse caso, terminamos aqui.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Sim, senhor.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_5");
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "Fiz sim. Qual é o seu ponto, capitão?";
			link.l1 = "Prove para mim que essas palavras não foram só conversa fiada. Quer ganhar um lugar na minha equipe? Uma parte do que viermos a conquistar? Siga minhas ordens. Não toque na garota. Por quê? Porque, se não fizer isso, vai ser um carniceiro para sempre, e eu não tenho espaço para gente assim.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "Esta é a segunda vez que você e eu estamos prestes a lutar até a morte, Capitão\nE mais uma vez, você vence graças ao seu dom de falar bonito! Ha ha! Você disse tudo! Bom, que se dane a garota. No fim das contas, sou mesmo um animal. Permissão para entrar na tripulação?";
			link.l1 = "Bem-vindo, Claude. Agora é pra valer.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Sim, sim, Capitão!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_6");
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Aconteceu uma coisa, capitão.";
			Link.l1 = "Deixa eu adivinhar: vai ameaçar pedir demissão e exigir um aumento de novo?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Heh! Dessa vez não... Não se preocupe, Capitão, enquanto você pagar, estou às suas ordens... dentro do razoável, claro. É assim que nós, mercenários, sobrevivemos. E até os melhores de nós recebem uma ninharia.";
			link.l1 = "Por que a gente não vai direto ao que interessa?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Lembra daquela vadia de Tortuga?";
			link.l1 = "Marceline? A esposa do governador? Uma mulher dessas não se esquece.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "Eu não vim à casa do Levasseur por acaso. Eu tinha negócios com aquele canalha e herege.";
			link.l1 = "É meio estranho você falar tão mal dos poderosos, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "Hã? Heh! Levasseur é o diabo! Ele é muito pior até do que os piratas que vivem às custas dele!";
			link.l1 = "Você mesmo acabou de dizer que fez negócios com ele. Não é um pouco hipócrita da sua parte?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Eu não sou nenhum santo, Capitão, e ganho a vida matando quem mandam. É por isso que você me valoriza tanto, não é? Mas até caras como eu ficam arrepiados ao ouvir os boatos sobre o que fazem com as mulheres em Tortuga, nos covis do Levasseur!";
			link.l1 = "Fofocas não me interessam. Esse homem é um nobre e servidor do Rei, e merece respeito.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "Então você roubou o criado do rei e ainda dormiu com a mulher dele? Heh! Você que sabe, Capitão. Vamos direto ao ponto. Sua Excelência me mandou encontrar e matar um homem. Um serviço bem comum, mesmo que raramente venha de alguém tão importante, e ainda por cima pessoalmente.";
			link.l1 = "E o que você quer? Que eu te solte pra você cumprir sua palavra e matar esse homem?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Quero que você me ajude com isso, Capitão. Quando as coisas ficaram feias pra mim em Tortuga, aceitei entrar pro seu serviço, mas não vou descansar enquanto não terminar esse trabalho. Se o Levasseur descobrir, ele me mata. Além do mais, deixar um serviço pela metade não é coisa de profissional.";
			link.l1 = "É profissional se envolver com a esposa de um cliente? É bem estranho ouvir esse tipo de pedido vindo de você, ainda mais se lembrarmos do início da nossa conversa, quando você descreveu muito bem a essência da nossa relação. Sangue por ouro, não é?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Se você me ajudar, não vai ganhar só minha espada, vai ganhar minha lealdade. Dá pra ver de cara que você nasceu pra voar alto, Capitão. Vou ter prazer em ajudar a fazer isso acontecer.";
			link.l1 = "Eu admito, prefiro ter um homem com suas habilidades me protegendo. Onde podemos encontrar esse seu alvo?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "Seu sabre basta por enquanto. Não sou um assassino. Fique tranquilo, oficial!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Tá certo, capitão. Não custava tentar, né.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_1");
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Heh! Esse é o problema, Capitão. Tudo que sei é que ele é um ex-cavaleiro da Ordem de Malta, foragido em algum lugar do território inglês. Um homem de sangue nobre, então não vai estar morando em um casebre.";
			link.l1 = "Cavaleiro da Ordem?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Um ex-cavaleiro. É, e já me arrependi de aceitar esse trabalho mil vezes. Cavaleiros lutam feito demônios, então posso garantir que você vai ter um belo teste das suas habilidades com a espada.";
			link.l1 = "Não gosto disso, mas vamos tentar. Então: não é um pobre coitado, é um nobre e está se escondendo com os ingleses? Levasseur não disse por que ele deve ser eliminado?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Claro que não vai! Mas é óbvio que é coisa política, senão ele teria mandado soldados.";
			link.l1 = "Vou tentar, mas não posso prometer nada.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Valeu, capitão.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_2");
		break;
		
	}
} 
