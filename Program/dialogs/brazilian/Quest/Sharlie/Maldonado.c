// Алонсо де Мальдонадо
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
		
		case "ksochitam":
			dialog.text = "Pare, Capitão "+GetFullName(pchar)+"...";
			link.l1 = "De algum jeito, nem me surpreendo mais com a presença dos soldados espanhóis por aqui... Acho que já me acostumei a ter alguém sempre no meu encalço. O que você está procurando nessa ilha esquecida por Deus, castelhano? Esperando encontrar um jeito fácil de relaxar?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Meu nome é Alonso de Maldonado. Talvez isso não signifique nada para você, mas Diego de Montoya talvez te soe familiar. Ele era meu melhor amigo. Salvou minha vida, e agora o sangue dele está nas suas mãos.";
			link.l1 = "Imagino que você me seguiu até aqui para se vingar?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Não estou aqui só por vingança. Pelo que entendi, você está com a máscara de Kukulcán?";
			link.l1 = "Mas que surpresa! Outro caçador de tesouros! Veio resolver algum assunto pendente deixado pelo Don Diego?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "Não me interesso por tesouros. Eu vi as riquezas de Tayasal. Miguel Dichoso não conseguiu levar mais do que uma migalha. O que eu quero é a máscara.";
			link.l1 = "Você já esteve em Tayasal? Difícil de acreditar. Pelo que me lembro, Dichoso foi o único sobrevivente daquela expedição.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "Eu fui a Tayasal vinte anos antes de Dichoso sequer aparecer. Foi na mesma época em que aquele feiticeiro louco, Kanek, usou aquele ritual desprezível de sacrifício humano para esconder a máscara nesta ilha.";
			link.l1 = "Não acredito no que estou ouvindo! Você fazia parte do mesmo grupo de conquistadores que foram levados lá para serem sacrificados quando o Guardião da Verdade foi criado? Todos vocês estão mortos!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "Nem todos nós. Eu sobrevivi.";
			link.l1 = "Por que os Itza decidiram poupar você? O que te torna tão diferente?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Você não entenderia. Na verdade, nem eu entendi direito. Ninguém teve piedade de mim. Lembro como se fosse ontem... Logo depois que aquele selvagem pegou uma adaga e arrancou um pedaço de pele das costas do Casco antes de matá-lo e começar a uivar feito um louco, acho que fui sugado pelo ídolo. Acordei bem longe de Tayasal, vinte anos depois, sendo que pra mim parecia ter passado só um instante!";
			link.l1 = "Um funil espaço-temporal... Maldição, tudo o que Ksatl Cha disse estava certo! Como você descobriu sobre a máscara? Pra que você precisa dela?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "Preciso deter a cria do inferno, invocada por um feiticeiro indígena enlouquecido. Essa abominação quer transformar nosso mundo numa fogueira!";
			link.l1 = "Hum... Você falou com o padre Vincento, não foi? O inquisidor está jogando dos dois lados. Que surpresa, hein. Ele te mandou me caçar para um duelo até o fim? Parabéns! Cumpriu sua missão, Dom Alonso!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "O Senhor fortalece minha mão na batalha contra o mal. Vou voltar para Tayasal e usar a máscara para selar os portões para sempre. E nenhum demônio em forma humana jamais cruzará para o nosso mundo.";
			link.l1 = "Tem só um pequeno problema com o seu plano, Don Alonso. O demônio JÁ está entre nós. Tudo o que precisamos fazer é não deixá-lo SAIR por esses portões. Ele não vai conseguir enquanto você mantiver a máscara longe dele.  ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Vai precisar de mais do que isso. Seja quem for que esteja certo entre nós, uma coisa é certa: os portões precisam ser fechados para sempre. E só há uma maneira de fazer isso: destruir a máscara no altar de Tayasal. Assim, o demônio perderá todo o seu poder.";
			link.l1 = "Hm. Concordo que é nossa melhor opção... Como você pretende chegar a Tayasal? Sabe o caminho até lá?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "O caminho fácil que usávamos naquela época não existe mais. As estradas estão soterradas por pedras e perdidas na selva. Existe outro caminho para a cidade, mas é longo e perigoso. A trilha começa na baía mais ao norte de Yucatán.\nCom a ajuda do Padre Vincento e de Dom Ramon de Mendoza, vou reunir um grupo de soldados de elite e abriremos caminho pela selva, guardada pelos selvagens Itza. Não será fácil, mas Deus nos dará força e coragem para lutarmos em nome da nossa fé.";
			link.l1 = "Dom Alonso, por acaso minhas aspirações coincidem com as suas. Não está na hora de deixarmos nossas desavenças de lado por um instante e unirmos forças? Juntos teremos mais chances de completar esta cruzada com sucesso.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Sou um soldado espanhol. Não faço alianças com hereges, nem negocio com franceses. Além disso, já declarei minha vingança contra você por Don Diego. Uma vida por uma vida!";
			link.l1 = "Você é teimoso como uma mula, Dom Alonso! Aí está você, pregando que o mundo está ameaçado por um grande mal, e mesmo assim recusa a minha ajuda para cumprir uma tarefa tão grandiosa!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "Agora quem manda sou eu, não o Padre Vincento! Faça suas orações e prepare-se para morrer, capitão francês!..";
			link.l1 = "Ah, já ouvi isso tantas vezes nos últimos meses! Em guarda, caballero cabeça-dura!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
