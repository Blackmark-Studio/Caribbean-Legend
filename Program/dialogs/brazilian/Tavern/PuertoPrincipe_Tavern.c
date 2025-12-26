// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco, "+GetAddress_Form(NPChar)+"...","Durante todo este dia, essa já é a terceira vez que você faz essa pergunta...","Mais perguntas, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ufa, onde foi parar minha memória...","Sim, é mesmo a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Dizem por aí que alguém te aliviou do seu precioso gim. Ou será que os boatos mentem?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "Boas notícias, "+npchar.name+"! Recuperei seu barril!";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Pelas chagas de Deus, é verdade. O que mais você ouviu? Sabe de algo? Eu imploro, diga que sabe onde encontrar isso. Se eu não recuperar... vou ter que fugir desta cidade. Ou com as próprias pernas, ou dentro de um caixão de pinho.";
			link.l1 = "De fato, sua situação parece complicada, amigo. Não, só ouvi rumores sobre seu azar. Como uma carga tão valiosa escapou das suas mãos?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "Maldição... O que posso dizer? Roubaram bem debaixo do meu nariz! O barril estava aqui de manhã, com certeza. Chegou há dois dias, e para garantir, levei pra casa durante a noite. De manhã, trouxe de volta e escondi debaixo do balcão. Quando anoiteceu, tinha sumido sem deixar rastro! Ninguém viu ou ouviu nada.";
			link.l1 = "Ora, não é que eu fiquei surpreso...";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "Se eu tivesse a menor pista, já estaria atrás disso. Mas, infelizmente, nada – como se aquele barril fosse bom demais para este mundo e os céus tivessem levado ele embora. Pago cento e cinquenta dobrões para quem trouxer de volta. E mais: coloco uma placa com o nome do herói na minha taverna, para todos saberem do feito!";
			link.l1 = "Vou ver o que posso fazer. Depois voltamos a falar dessa placa. Agora me diga, quem sabia desse barril? E quem além de você poderia estar atrás do balcão?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "Cento e cinquenta doblões por um barril? Engraçado. Mas seus problemas não são meus. Resolva isso você mesmo.";
			link.l2.go = "OS_Tavern1_end";
		break;

		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");

			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;

		case "OS_Tavern1_4":
			dialog.text = "Praticamente ninguém! Talvez só minha ajudante, mas isso é impossível. A taverna estava em clima de festa naquele dia – a tripulação do 'Monstro do Mar' tinha voltado da caçada com um belo prêmio. Ela não teve um minuto de descanso, quanto mais tempo para se esgueirar atrás do meu balcão.";
			link.l1 = "Tem certeza disso?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "Sem dúvida! Trabalhar sem descanso não combinava com o temperamento dela, e ao anoitecer ela estava tensa como uma corda esticada. Quando um dos marinheiros tentou se aproximar, ela fez um escândalo tão grande que quase ensurdeceu todo o estabelecimento. Tive que largar meu posto para acalmar a situação. Estranho, porém – normalmente ela lida com esse tipo de coisa com muito mais calma.";
			link.l1 = "É só isso? Nada mais de estranho naquele dia?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "While I was quelling that first disturbance, another flared up - two sailors came to blows in the far corner. The scuffle didn't last long, though; they appeared to be shipmates, and were quickly separated. After that, everything truly quieted down with nothing further worthy of mention.";
			link.l1 = "Muito bem, vou começar a procurar. Espere. Acho que logo o barril estará de volta sob seu, hã... olhar atento.";
			link.l1.go = "OS_Tavern1_7";
		break;
		//<-- Старые счёты
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "Você encontrou?! Será possível? Capitão, você salvou minha vida! Quem estava por trás disso? Preciso saber o nome do canalha!";
			link.l1 = "Foi um plano meticulosamente elaborado por um tal Jack Veils, em conluio com o capitão do 'Sea Beast'. Eles recrutaram seus marinheiros e armaram uma distração elaborada para te afastar. Quando você deixou seu posto, o barril ficou desprotegido, e eles o levaram sem dificuldade.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "Céus! Jack Veils! Então ele voltou... E pelo visto achou que podia recuperar a taverna por meios tão traiçoeiros. Aquele safado nunca admite derrota!";
			link.l1 = "Então ele já foi o dono deste estabelecimento? Fique tranquilo, ele não vai mais tramar nada. Mandei ele se encontrar com o criador dele.";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "Capitão! Isso é extraordinário! Você... você me libertou do medo constante que vinha assombrando meus dias! Eu sempre soube que ele voltaria mais cedo ou mais tarde... Alguns anos atrás, éramos rivais pela posse desta taverna, e ele conseguiu me superar\nMas a alegria da vitória foi sua ruína – em meio à comemoração, ele acabou apostando o lugar comigo no carteado, sem nem perceber. Claro, quando amanheceu, ele apareceu correndo, implorando para recuperar a taverna, prometendo tudo e mais um pouco\nMas eu não sou tolo a esse ponto para aceitar tais condições. Então ele sumiu... Eu sabia que ele não deixaria isso quieto. Sentia que um dia ele voltaria. E agora, esse dia chegou.";
			link.l1 = "Mérito seja dado – ele executou o plano dele com astúcia.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "Espere um momento! Como ele ficou sabendo do barril? Parece... parece que estou começando a entender! A garçonete! Por isso ela fugiu feito uma assustada, sem nem se despedir. Ela deve ter ouvido falar que você lidou com o Jack. Agora tudo faz sentido. Capitão, estou lhe devendo uma que não tem preço, você...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
