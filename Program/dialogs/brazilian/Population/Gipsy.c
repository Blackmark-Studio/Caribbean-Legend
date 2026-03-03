//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ah, olá, querido. O que você deseja?";
			link.l1 = "Nada, eu acho.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Tenho uma pergunta para você.","Preciso de informações.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Querido, você seria tão gentil a ponto de compartilhar um pouco de ouro? Eu vou te contar o seu futuro.","Ei, marinheiro, não vá embora assim tão rápido! Gostaria de saber o seu futuro?","Me dê um pouco de tabaco e algumas moedas de prata, jovem corajoso. E eu vou dar uma olhada no seu futuro. (pisca) Quer ouvir um pouco da magia secreta dos ciganos?");
				link.l1 = "Desculpe, mas eu preciso ir.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Escute, dona cigana, sei que o seu povo entende tudo de poções e venenos. Disseram que você talvez se interesse por essa planta. Dê uma olhada. O que acha?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Ei, olhos escuros, tenho algo pra você... Isso é mangarosa. Quer comprar um pouco?";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Você pode ler minha sorte?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("Tenho uma pergunta para você.","Preciso de informações.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Estou procurando uma cigana que cuida dos doentes. Seria você?";
				link.l6.go = "dwh_ne_ta";
			}
			// <-- Тёмные воды исцеления

			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Ei, olhos escuros, você tem algum veneno pra rato? Eles estão sendo um inferno no meu navio.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Claro, bonitão. Me dê umas moedas e mostre sua mão direita. Vou contar seu futuro e te ajudar a evitar desastres. Eu nunca engano! Garantia de devolução do dinheiro!";
			link.l1 = "Sinto que essa é a hora em que seu compatriota tenta me roubar... Mudei de ideia. Não estou com vontade.";
			link.l1.go = "exit";
			link.l2 = "Quanto dinheiro você quer?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ah, querido, tanto quanto sua bolsa permitir e seu coração desejar. Quanto mais moedas de oito, mais longe no futuro eu consigo enxergar!";
			link.l1 = "100 pesos";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 pesos";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 pesos";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 pesos";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ah, obrigado pela sua generosidade, meu belo jovem falcão! Agora escute:  "+sTemp+"";
				link.l1 = LinkRandPhrase("Hein! Isso é bem interessante. Vou pensar nisso...","Sério? Vou pensar nisso...","Ah, é mesmo? Está falando sério? Vou me lembrar disso...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "A pior e mais inevitável desgraça está à sua espera. Maldito seja o zombador! Que nuvens negras se formem sobre você e que a punição te alcance!";
				link.l1 = "Ha-ha! Você realmente achou que eu ia te dar dinheiro, sua bruxa cigana? Saia da minha frente! Tomara que a Inquisição te pegue!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ah, obrigado, meu belo jovem falcão! Agora escute:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Isso é bem interessante. Vou me lembrar disso...","Sério? Vou pensar nisso...","Ah, é mesmo? Está falando sério? Pois bem, vou me lembrar disso...","Ei, já estou me sentindo melhor!");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "A pior e mais inevitável desgraça está à sua espera. Maldito seja o zombador! Que nuvens negras se formem sobre você e que a punição te encontre!";
				link.l1 = "Ha-ha! Você realmente achou que eu ia te dar dinheiro, sua bruxa cigana? Saia da minha frente! Tomara que a Inquisição te pegue!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ah, obrigada pela prata, meu belo jovem falcão! Agora escute:"+sTemp+"";
				link.l1 = LinkRandPhrase("Hein! Isso é bem interessante. Vou pensar nisso...","Sério? Vou pensar nisso...","Ah, é mesmo? Está falando sério? Pois bem, vou me lembrar disso...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "A pior e mais inevitável desgraça está à sua espera. Maldito seja o zombador! Que nuvens escuras se formem sobre você e que o castigo te encontre!";
				link.l1 = "Ha-ha! Você realmente achou que eu ia te dar dinheiro, sua bruxa cigana? Sai da minha frente! Tomara que a Inquisição te pegue!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh la la! Obrigada pela sua generosidade, meu jovem falcão bonito! Agora escute:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Isso é bem interessante. Vou pensar nisso...","Sério? Vou pensar nisso...","Ah, é mesmo? Está falando sério? Pois bem, vou me lembrar disso...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "A pior e inevitável desgraça está à sua espera. Maldito seja o zombador! Que nuvens negras se formem sobre você e que a punição te encontre!";
				link.l1 = "Ha-ha! Você achou mesmo que eu ia te dar dinheiro, sua bruxa cigana? Saia da minha frente! Tomara que a Inquisição te pegue!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Ah, não sei dizer, bonitão! Não faz muito tempo, apareceu um sujeito pedindo ajuda pra matar ratos, e logo depois alguém envenenou os soldados do forte. A coisa ficou feia pro meu povo na ilha enquanto os guardas nos interrogaram por duas semanas até acharem o assassino. Era um espião inimigo.","E como posso ter certeza das suas intenções? Talvez você só queira envenenar um nobre que é covarde demais para enfrentar em um duelo honrado?","Ouvi dizer que alguém envenenou um comerciante na taverna e roubou todos os pertences dele. O homem sofreu por muito tempo antes de morrer. Saiu espuma da boca dele e ele ficou roxo como uma berinjela... Foi você quem fez isso, meu amor?");
				link.l1 = "Vocês, ciganas, realmente gostam de dar opinião! Fique tranquila, moça, não vou envenenar ninguém. Isso é coisa de mulher, não faz meu tipo. Para os homens, tenho minha espada, mas esses malditos ratos eu não aguento.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(true, "Trustworthy");
			}
			else
			{
				dialog.text = "Está tentando me incriminar! Não, senhor, eu não tenho nenhum veneno. Tenho plantas e poções, mas venenos, não.";
				link.l1 = "Tanto faz então. Não joga mau-olhado pra cima de mim.";
				link.l1.go = "exit";
				Notification_Perk(false, "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Oh, que homem bonito e galante! (sussurrando) Me pague "+sti(npchar.quest.poison_price)+" dobrões.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Caro... Isso aqui tem que funcionar mesmo.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "De jeito nenhum! Comprei o mesmo em casa por cinco pistolas! Por esse preço, eu mesmo pegaria todos os ratos!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Então vá atrás deles você mesmo e não me incomode. Da próxima vez, vou chamar a guarda.";
			link.l1 = "Não precisa chamar os guardas, bruxa, eu já estou indo embora.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Mostre-me a planta, querido(a)... Hm... Acho que posso comprá-la de você. Trezentas peças de oito, combinado?","Mostre-me onde fica, bonitão... Heh... Bem, posso pagar duzentos e cinquenta por isso.","Vamos ver... Ah! Um exemplo interessante! Duzentos pesos! Fechado?")"";
			link.l1 = LinkRandPhrase("Oh Senhor... olhos escuros, eu não sou nenhum caipira. Eu conheço essa planta. É mangarosa...","Ah, é mesmo?! Este é um exemplar perfeito de mangarosa. Não tente me enganar, cigana.","Aha, e você acha que eu vou te dar essa mangarosa por uma quantia tão insignificante.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Certo, certo, bonitão. Vejo que você entende dessa planta. Cinquenta dobrões. Me dê ela.";
			link.l1 = "Espere aí! Quero saber como isso pode ser usado e para quê. Pode me explicar? Todo o seu povo está disposto a pagar muito ouro por esse arbustinho!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Hm... Suponho que não faz mal te contar um pouco sobre isso. Você não vai conseguir fazer nada com essa planta sem habilidades especiais.";
				link.l1 = "Estou ouvindo.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("Meu povo pode até pagar muito ouro, mas jamais revelaria seus segredos.","Ouro é ouro e segredos são segredos, rapaz... ","Sim, estamos dispostos a pagar, mas não a contar.")+"Então, vai me vender sua mangarosa? Cinquenta doblões é o preço que pagamos por ela, ninguém vai te oferecer mais.";
				link.l1 = "Ah, tudo bem... Tanto faz pra mim. Cinquenta doblões. Pode pegar";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Entenda, eu não quero vender isso. Quero saber por que você precisa disso. Compartilhe seu conhecimento comigo e eu te dou de graça.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Pegue suas moedas, jovem falcão. E mais uma coisa, traga mais dessas plantas para nós. Mas só podemos comprar uma de cada vez, pois não andamos com muito dinheiro. Os guardas não confiam no nosso povo e adoram nos importunar...";
			link.l1 = "Certo. Se eu encontrar mais, trago para você.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("De jeito nenhum! Se não quer vender, então não venda. Não vou te contar nada.","Não vou revelar nossos segredos pra um forasteiro comedor! (cospe) Não quer vender? Vai pro inferno então.","Amigo, isso não é da sua conta. Não quer vender por cinquenta doblones? Então vai lá e vende pra moça do comércio por duzentos pesos.");
			link.l1 = LinkRandPhrase("Que pena pra você então! Alguém da sua tripulação vai acabar me contando de qualquer jeito. E ela vai ganhar essa planta de presente. Até mais!","Por que tanta teimosia? Se você não me contar, a outra vai contar. E ela vai ganhar essa mangarosa de presente. Adeus.","Seu hálito fede a alho. Eu vou conseguir o que quero, mais cedo ou mais tarde. Outro do seu tipo vai ser mais falante e vai pegar a planta de graça. Até mais.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "E por que pergunta, falcão?! Claro! Me dê isso.";
			link.l1 = "Me dê cinquenta doblões.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Opa! Parece que perdi ou deixei no meu navio. Que pena. Tchau...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Não se preocupe, não vou te enganar. Pegue suas moedas.";
			link.l1 = "Pegue sua mangarosa. Se eu encontrar mais, trago para você.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "Moemos os brotos de um jeito especial, depois secamos, tiramos as sementes e os talos, misturamos com tabaco, enchemos nossos cachimbos e fumamos a mistura. E aí sentimos um... efeito inesquecível. É como ficar bêbado de álcool, mas sem a dor de cabeça depois. Uma planta só rende umas duas dúzias de cachimbos.";
			link.l1 = "Entendi agora! Pode me ensinar essa técnica secreta? Posso pagar bem...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Falcão jovem, acredite em mim, você não precisa disso. Não se envolva, essa erva vai acabar com você. Ela embota a mente e te deixa preguiçoso. Nem me peça. Mas... vejo diante de mim um homem corajoso, com uma espada, um homem do mar... talvez até um capitão?";
			link.l1 = "Você está certo.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Então ouça bem. A mangarosa pode ser usada para fins muito mais nobres, e talvez você ache útil. Uma de nossas curandeiras conhece todos os seus segredos. É ela quem você procura.\nMe dê a planta e eu te direi o nome dela e onde encontrá-la. Mas convencer ela a compartilhar os segredos com você já é problema seu.";
			link.l1 = "Certo. Pegue a planta e me diga como encontrar seu mágico cigano.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "O nome dela é Amelia. Ela mora sozinha numa casinha entre as dunas, não muito longe do mar, em algum lugar na costa sudoeste do continente espanhol, como dizem os mais sábios.";
			link.l1 = "Ah, pelo amor de Deus, pode ser mais específico?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Você é um marinheiro, um falcão destemido, e eu não sou. Procure por ela onde eu te falei. A casa dela fica bem perto da costa. É perto de uma baía, logo a sudoeste do Spanish Main – marinheiros devem saber onde é.";
			link.l1 = "Certo, vou tentar encontrar...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Leve uma Mangarosa para ela ou ela nem vai te dar atenção. E não se esqueça de levar alguns dobrões também, nem pense que ela vai te ensinar de graça!";
			link.l1 = "Quanta ganância. Vou pensar nisso. Obrigado pela sua história!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Não, "+GetSexPhrase("querido","beleza")+", não sou eu quem você procura, é "+sld.name+"Ela está aqui na cidade agora mesmo. Eu a vi recentemente.";
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Escute-me, falcão valente, posso ser cigana, mas até nós condenamos a violência aberta. Por favor, guarde sua espada.","Me escute, falcão valente, como cidadão desta cidade eu lhe peço que embainhe sua espada.");
			link.l1 = LinkRandPhrase("Certo.","Como quiser.","Como você quiser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}
