// Арчибальд Колхаун
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

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
		
		case "portroyal":
			dialog.text = "Ha, Monsieur de Maure!  Bem-vindo a Port Royal!  Ainda se lembra de mim?";
			link.l1 = "Hmm... Você é o sr. Calhoun, não é? Henry Calhoun?";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "Quase... Archibald Calhoun.";
			link.l1 = "Oh, me perdoe, Monsieur. Sim, eu me lembro de você. Nos conhecemos em Cabo Catoche, na baía. Seu capitão estava com você também, William Patterson. Reconheci o esquadrão dele.";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "Está certíssimo! Por favor, perdoe meu capitão. Ele sempre é grosseiro com quem não conhece. Você foi brilhante ao tomar de assalto o forte do Diego de Montoya, onde aproveitamos para afiar nossas garras...";
			link.l1 = "É em nome da justiça, devo acrescentar, que sem os preparativos prévios feitos pelo seu capitão, duvido que eu sequer teria conseguido correr até o prêmio sob o fogo dos canhões espanhóis. Seu comandante encontrou o que procurava?";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "Sim. Ele se enfiou bem fundo nas casamatas sob o forte e encontrou algum tipo de arquivo. Ficou indescritivelmente satisfeito. Aliás, se não for incômodo perguntar, o que te levou a atacar aquele forte na selva?";
			link.l1 = "Depois de ser derrotado por mim em Saint-Pierre, Dom Diego começou a tramar e acabou lançando um ataque aberto contra Cuba. Depois, ele interrompeu o combate e fugiu para as colinas em direção ao continente. Bem, decidi acabar de vez com esse covarde, para que ele nunca mais envergonhasse os franceses.";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "Sim, já ouvi muitas histórias lendárias sobre as façanhas heroicas do capitão Charles de Maure. Agora vi com meus próprios olhos...";
			link.l1 = "Sim, também ouvi algumas coisas sobre a coragem de William Paterson. Você tem sorte de ter um capitão como ele.";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "Sortudo eu, é verdade. Embora ele tenha se tornado um homem tão importante ultimamente, um homem da alta sociedade, audiências, bailes, desfiles e festas privadas... Você não consegue tirá-lo do palácio do governador toda vez que chegamos a Port Royal. Na verdade, ele está lá de novo agora mesmo. Capitão Charles de Maure, pode fazer um favor a um escocês bêbado? Junte-se à minha companhia e vamos bater um papo! Estou cansado de ver sempre as mesmas caras e você parece ser uma boa pessoa para conversar. Vá até minha casa, vamos relaxar e tomar um barril de uísque excelente. Eu pago!";
			link.l1 = "Hm... Tentador, mas...";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "Ah, pare com isso, Capitão, você também precisa descansar de vez em quando. Aliás, tenho uns petiscos ótimos, direto da loja do mercador local. Estou alugando um quarto bem acima da loja. Quando quiser comer alguma coisa ou tomar um drink, é só descer as escadas que já está pronto, haha! Prático, não é? Vamos, venha!";
			link.l1 = "Você me convenceu!";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "Ótimo. Venha comigo!";
			link.l1 = "...";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "Viu como aqui dentro é gostoso? Fresquinho... Olha só esses barris de uísque! Saúde, Capitão!";
			link.l1 = "Bem, vamos brindar ao nosso encontro inesperado e a uma boa companhia!";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "Encantado!... Ah! Você chegou recentemente ao Caribe, não foi, Monsieur de Maure?";
			link.l1 = "Relativamente há pouco tempo... ou talvez nem tão pouco assim. Na verdade, nem sei direito como dizer. Sinto que vivi aqui metade da minha vida.";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "Ah, eu sei bem como é isso... Embora eu mesmo já esteja aqui faz tempo. E quando pisei naquela ilha maldita de onde o William me salvou... Olha, foi como se eu tivesse deixado metade da minha vida pra trás ali.";
			link.l1 = "Interessante! Em qual ilha foi isso?";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "Willy é um velho amigo meu, nos conhecemos quando eu ainda respirava o bom ar da Escócia... Bons tempos. Fui tolo o bastante para arranjar briga com aqueles malditos papistas e com o próprio inquisidor, então ele mandou me matar. Naquela época eu era comerciante, tinha minha própria flauta. Pois é, naquele dia maldito meu navio foi atacado pelos espanhóis, disfarçados de piratas. Lutamos com coragem, mas conseguiram nos encurralar feito ratos! Mesmo assim, o velho Colhaun não perdeu a cabeça e pulou no mar com um barril de água e algumas tábuas. Aproveitei a escuridão e nadei para longe do meu navio, sem ser visto pelos soldados. Minhas chances de sobreviver não eram boas, mas ficar no navio significava não ter chance nenhuma. Dois dias depois, fui parar numa praia de uma ilha deserta. Eu já vivia há algum tempo no Caribe, mas nunca tinha ouvido falar daquele lugar! É pequena e completamente desabitada... e passei dois anos lá, que pareceram uma eternidade. Até hoje não sei como consegui manter a sanidade.";
			link.l1 = "Você viveu por dois anos em uma ilha desabitada?";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "Com certeza, maldito lugar! Ainda bem que tinha água doce. Sobrevivi comendo caranguejos, cracas, peixes e aves. Por isso chamei de Ilha dos Caranguejos. Eu não tinha armas, então aprendi a usar arpão, lança e flecha como um selvagem! Ohoo! Beba, beba, Capitão! Também não me importo de molhar a garganta...";
			link.l1 = "É... Não queria estar no seu lugar.";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "Aí está! Foi exatamente isso que eu disse quando pisei pela primeira vez naquela imensidão de areia: 'Velho Archy, sua situação não é invejável, mas também não é desesperadora!' E sabe o que me manteve vivo, Capitão?";
			link.l1 = "Um navio passando pela ilha?";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "Não! Foi o trabalho duro que me salvou! Esforço, fé e vontade de viver! Explorei toda a ilha, cada cantinho, e fui recompensado com um baú cheio de ferramentas de carpinteiro, material de escrita e outras coisinhas. Sabe o que eu disse pra mim mesmo naquele momento? Sirva mais, Capitão, só sirva!\nEu disse: Archie, você precisa trabalhar pra manter a cabeça no lugar, e Deus te deu tudo pra começar. Agora está vendo! Comecei a construir uma casa perto de uma baía, e sabe o que aconteceu? Isso me salvou dos pensamentos ruins e me deu um motivo pra viver!";
			link.l1 = "Você é uma verdadeira inspiração, Sr. Calhoun. Poucos homens conseguiriam fazer algo, ou qualquer coisa, numa situação dessas...";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "Sim, o velho Calhaun nasceu na Escócia por um motivo! Isso mesmo! Somos filhos das montanhas – fortes, corajosos e resistentes, muito melhores do que aqueles fracos dos pântanos. Sirva mais... Certo, sobre o que eu estava falando? Ah, sim! Trabalhei duro e construí uma casa decente pra mim. Também comecei um diário pra registrar as desventuras do dia a dia. Levei esse diário comigo quando o Willy me salvou. Agora guardo ele nesta mesa aqui e releio deitado numa cama quente e macia toda vez que ficamos em Port Royal. Escrevi tudo nele, tudo que me aconteceu antes e depois de chegar lá. É um dos motivos de eu ainda não ter perdido o juízo.";
			link.l1 = "Então quer dizer que o senhor Paterson te resgatou da ilha? Mas como ele conseguiu encontrar o lugar? Você disse...";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "Sim, sim, a ilha não está marcada em nenhum mapa. Mas o Willy, ele é o velho Willy! Ele faz qualquer coisa! E ele achou aquela maldita ilha e me salvou, e por isso vou ser grato até o fim da minha vida. É...";
			link.l1 = "Você gosta de trabalhar para o Sr. Paterson? Gostaria de tentar a sorte por conta própria de novo?";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "Cansei de ser independente. O Willy é jovem e bem-sucedido, e além disso sou amigo dele há anos. O que mais eu preciso? Não, vou ficar com o Willy até o fim dos meus dias, ou pelo menos até ele me expulsar de novo na próxima vez que eu encher a cara, haha! Falando em encher a cara, manda mais uma aí!";
			link.l1 = "Akh...(bebendo) Me diga, Sr. Calhoun. Ouvi dizer que o senhor, ahn, já foi caçador de tesouros. É verdade, ou é só conversa fiada?";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "Who told you that? Well, there's no sense in trying to hide it. I used to be one. It didn't turn out well though; it was treasure hunting that led me to those blasted Jesuits and the island. The holy fathers tortured a man to death because of me, and I myself... oh, let's keep the past in the past.\nI have paid enough for my sins, and I hope never to repeat them in the future. No, Willy won't let that happen, I'm sure!";
			link.l1 = "Escute, Archibald. Já ouviu falar de um homem chamado Miguel Dichoso?";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "Eu nunca ouvi esse nome antes. Quem é ele?";
			link.l1 = "Ah, ninguém interessante... só um homem que gosta de buscar aventura e tesouros. Mas já que você nunca ouviu falar dele, melhor deixarmos esse assunto pra lá.";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "Sim, melhor não! Vamos falar da velha Europa então! Lembro de vinte anos atrás na Escócia...";
			link.l1 = "...";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
