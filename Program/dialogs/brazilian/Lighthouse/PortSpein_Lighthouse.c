// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que você quer?","O que você gostaria de saber?"),"O que você precisa, "+GetAddress_Form(NPChar)+"?","Essa já é a terceira vez que você tenta me perguntar...","Já cansei de você, suma daqui!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Desculpe, mudei de ideia.","Não foi nada, me desculpe."),"Eu me esqueci, me desculpe...","Terceira vez é a certa, hein? Com licença...","Desculpa, desculpa! Eu já estou de saída então...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Escute, uma fragata sob o comando de Miguel Dichoso esteve por aqui em abril de 1654, mas depois sumiu. Você pode me contar mais sobre o navio dele? Talvez tenha visto o que aconteceu com ele ou para onde foi? Lembra de alguma coisa?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Ah, Senhor, aquilo foi uma cena e tanto! Coisas assim a gente não esquece, ha!";
			link.l1 = "Pode me contar o que aconteceu?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "A fragata do Señor Dichoso lançou âncora no porto de San Jose. Eu tive uma ótima visão de tudo, sim senhor. Te digo, era uma fragata excelente, uma verdadeira obra-prima, juro pelo meu coração sangrando! A tripulação se gabava da velocidade dela, podia chegar a dezesseis nós! Ficaram aqui um dia, depois zarparam direto para a ilha de Tobago. E aí, você não vai acreditar, coisas estranhas começaram a acontecer com o tempo assim que eles sumiram no horizonte. O tempo estava ótimo fazia dias, nem uma nuvem no céu! E mesmo assim, uma tempestade terrível apareceu do nada. Parecia que o próprio Netuno tinha vindo nos visitar, de verdade! Subi até o topo do meu farol para acendê-lo, mas então eu vi ela... Santa Quiteria! Ela avançava sobre ondas enormes, acompanhada de um tornado gigante! A fragata passou voando pelo meu farol como uma faísca e foi levada pela tempestade para noroeste! Ninguém viu a Santa Quiteria desde então. Só uma hora depois, o vento, a chuva e as nuvens sumiram e o sol voltou a brilhar, sem sinal nenhum da tempestade! Nunca vi nada igual! Embora eu tenha recolhido tanto âmbar na minha baía naquele dia...";
			link.l1 = "Então a tempestade fez a fragata voltar para o Mar do Caribe?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Tem sim! Bem lá pra bandas da Martinica. Duvido que o Dichoso tenha sobrevivido àquela tempestade, mas ele fez o que pôde! A fragata não afundou, mas a Santa Quiteria já deve estar no fundo do mar, entre os corais... Na verdade, você não é a primeira pessoa que me pergunta sobre o Dichoso e a fragata dele.";
			link.l1 = "Sério? Quem mais estava interessado no Miguel?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Um capitão elegante da frota espanhola, nada menos! Ele se apresentou como... ah... acabei esquecendo... Ah! Señor Diego. O nome dele era Diego, mas o sobrenome... de Montagna ou de Montoya. Algo assim. Ele me ouviu, igualzinho a você, agradeceu e foi embora. Nunca mais vi ele desde então.";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "Entendi. Muito obrigado pela sua história, você me ajudou bastante. Por favor, aceite minha gratidão em moedas. Até logo.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "Entendi. Muito obrigado por compartilhar sua história, você me ajudou bastante. Até logo.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
