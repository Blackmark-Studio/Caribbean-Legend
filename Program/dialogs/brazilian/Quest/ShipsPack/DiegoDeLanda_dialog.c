void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Triste história, não é?";
				link.l1 = "Quem é você?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Saudações, capitão.";
				link.l1 = "Espere! Nós já nos encontramos antes!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Um. Dois. Três.";
				link.l1 = "Vamos parar com esse teatro. Quem é você?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "Quatro.";
				link.l1 = "Faltam dois?";
				link.l1.go = "DiegoDeLanda_Meeting_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "Sabe o que há de especial neste túmulo? Aqui jazem duas almas ligadas pelo sangue. Pai e filho de Alameda. Um caiu nas mãos de pecadores, o outro... hmm, encontrou seu caminho até o Senhor.";
				link.l1 = "O diário de Dom Fernando me trouxe até aqui.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Você viu a Lady Bishop? Triste destino, não é? Mas receio que foi merecido.";
				link.l1 = "Você conhece a Elizabeth?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grim.";
				link.l1 = "Você o conhecia, não é?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_ClockTower"))
			{
				dialog.text = ""+GetCharacterName("Hendrik")+" "+GetCharacterName("van Doorn")+".";
				link.l1 = "Seu cliente?";
				link.l1.go = "DiegoDeLanda_ClockTower_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nMais três. Quando chegar a seis, você saberá de tudo.";
			link.l1 = " Se você não me der respostas claras agora, então eu...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nVocê está indo bem, capitão. Você merece saber meu nome. É Diego de Landa.";
			link.l1 = " Você é mesmo um padre?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Antes de tudo, sou um artista. Mas vamos com calma...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		
		case "DiegoDeLanda_Meeting_Fourth_2":
			dialog.text = "\nMuito bem, Capitão. O terceiro ato começa.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ah... O diário. Uma coisa notável — a palavra escrita. É como... um caminho na escuridão. Leva você até onde a revelação espera. Dom Fernando costumava visitar nossa paróquia. Especialmente no último ano.";
			link.l1 = "Você serve na paróquia local? Conhecia o Don Fernando?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "Eu... observei o caminho dele. E aquele livro que você pegou. Sabe o que há de especial nele?";
			link.l1 = "Parece antigo.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Velho? Não, de jeito nenhum. É... iluminado. A Bíblia de Don de Alameda Sr. Cada palavra nela é como um farol na escuridão. Pegue. Ajude seus irmãos em Cristo e então, talvez... isso te leve a algo... maior.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Ah, sim. Pobre mulher. O marido dela... não é o homem mais gentil. Dizem que as plantações dele são as mais produtivas de Barbados. E as mais cruéis. Sabe quantos escravizados morrem lá todo mês? Recentemente, ele espancou até a morte um médico de verdade vindo da Inglaterra — um homem de grande inteligência e talento. Mas o destino dela não é muito melhor, pode acreditar.";
			link.l1 = "Parece que você está muito bem informado.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "As pessoas vêm até mim para confessar, Capitão. Eu ouço coisas que elas têm medo de contar até mesmo para quem amam. Seus medos, seus pecados... suas dores.";
			link.l1 = "Você não tem medo de perseguição? Não é fácil para um padre católico em solo inglês.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Meus medos não são nada comparados ao que você acabou de deixar para trás daquela porta. E aquele livrinho que você pegou daquela pobre mulher... Se o medo tivesse uma forma, seria exatamente como aquilo.\n"+"Bom dia, Capitão.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Tigre, tigre, ardendo brilhante\n"+"Nas florestas da noite,\n"+"Que mão ou olho imortal\n"+"Poderia moldar tua terrível simetria?\n"+"Claro que eu conhecia ele, Capitão. Mas e você?";
			link.l1 = "Eu nunca conheci um homem com um destino mais trágico.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "Você já tem, só não percebeu ainda.\n"+"Então você não conhecia o Grim. Mesmo agora, segurando o crânio dele nas mãos.";
			link.l1 = "O quê?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "Isso não é jeito cristão de tratar os mortos. Aqui, pegue esta pequena instrução póstuma. Um presente meu para você.\n"+"Bom dia, Capitão.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Башня с часами
		case "DiegoDeLanda_ClockTower_2":
			dialog.text = "Engraçado, capitão. Você era cliente dele, e ele era meu.\n"+"Como vocês se parecem.\n"+"Você não esqueceu como entrou no registro, esqueceu? Primeiro você ajudou a gloriosa cidade de Willemstad. Só para depois afogar muitos de seus filhos em sangue.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_3";
		break;
		
		case "DiegoDeLanda_ClockTower_3":
			dialog.text = "Embora Hendrick não tenha conseguido fazer isso. Cliente difícil, muito difícil. Aqui, por exemplo. Leia quando puder — um verdadeiro mistério.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_4";
			// получаем документы Маартена
			ClockTower_AddVisserKey();
			
		break;
		
		case "DiegoDeLanda_ClockTower_4":
			dialog.text = "Cada pessoa é como um prédio. Quer saber o que realmente move alguém? Olhe para o porão dela.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_5";
		break;
		
		case "DiegoDeLanda_ClockTower_5":
			dialog.text = "Aqui.";
			if (CheckAttribute(pchar, "questTemp.ClockTower_GotHint"))
			{
				link.l1 = "Chave do porão? Eu já estive lá.";
				link.l1.go = "DiegoDeLanda_ClockTower_6";
			}
			else
			{
				link.l2 = "O que você guarda na sua adega?";
				link.l2.go = "DiegoDeLanda_ClockTower_7";
			}
		break;
		
		case "DiegoDeLanda_ClockTower_6":
			dialog.text = "\nEntão não temos mais nada para discutir, Capitão.";
			link.l1 = "Ofendido? Fico curioso, o que você guarda na sua adega?";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		case "DiegoDeLanda_ClockTower_7":
			dialog.text = "\nCada conversa que temos é um passo a mais lá embaixo, Capitão.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			ClockTower_AddBook_FromDiegoDeLanda(); // получаем ключ от подвала
		break;
		
		//<-- Башня с часами
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Me diga... Por quê? Isso foi perigoso e insensato. O que te move, Capitão? Qual é o seu fogo?";
				link.l1 = "Isso não é da sua conta.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Segundo.";
				link.l1 = "Da última vez você falou em enigmas. Vai fazer isso de novo?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Espere, de Landa. Eu não posso simplesmente deixar você pegar e sair assim.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "Nada além de pistas, encenações e nenhuma ação\n"+"Da minha parte, pelo menos. Você já teve ação de sobra.";
				link.l1 = "Tenho uma ideia de como resolver isso.";
				link.l1.go = "DiegoDeLanda_Leaving_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "Eu não entendo. Os outros — sim. Mas você, não. Ainda não.";
			link.l1 = "Os outros?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "Um, por exemplo, busca justiça. Outro... é obcecado pelas águas escuras da morte. As pessoas se perdem tão facilmente em seus desejos. Não acha?";
			link.l1 = "Você é um padre estranho, padre.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Eu devo ir.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Claro. Seu trabalho está só começando, Capitão.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nO verdadeiro enigma está diante de mim. Você já reuniu dois... artefatos. Gosta de colecionar essas coisas? É um colecionador?";
			link.l1 = "Como você sabe?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "Um caçador de troféus?";
			link.l1 = "Repito minha pergunta: como você sabe?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;
		
		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "Um caçador de emoções?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAh. Claro. Naturalmente. Bem, Capitão, não vou tomar mais do seu tempo.";
			link.l1 = "Espere, Padre. O senhor ainda não respondeu à minha pergunta.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Oh, Capitão. Eu não posso. Às vezes, as respostas machucam mais do que a ignorância. Vá em paz. E cuide bem da sua coleção... de troféus. Eles podem ser úteis na jornada que está por vir.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Vamos lá, Capitão. Não acha interessante? Não está se divertindo? Já tem troféus suficientes?\n"+"Esse é o seu fogo, Capitão. Você é curioso sobre o que vem depois. Ama navios belos e objetos fascinantes.\n"+"Você simplesmente não consegue evitar querer colecionar todos.\n"+"\n"+"Pode me atirar agora mesmo.";
			link.l1 = "O quê?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Vá em frente. Mas aí você não vai descobrir tudo e não vai conseguir o conjunto completo de troféus. Embora vá ganhar todos os navios de qualquer jeito...\n"+"Bom dia, Capitão.";
			link.l1 = "(Deixe ele ir)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Atire nele)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_Fourth_2": // Четвёртое прощание
			dialog.text = "\nTarde demais, Capitão. Você teve sua chance de atirar em mim. E que chance! Na contagem de três: um, dois, três... e nada. Mas não se preocupe. No seis, eu te dou ação. Falta pouco agora.\n"+"Bom dia, Capitão.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 