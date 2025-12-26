void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "O que você queria, "+GetAddress_Form(NPChar)+"? Desculpe, mas não estou aceitando novos pedidos. É que eu tenho... trabalho demais...";
			link.l1 = "É mesmo? Ouvi dizer que você perdeu algo muito valioso recentemente em um jogo de cartas, é verdade?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Bem, se você veio para se divertir às minhas custas, entre na fila – já tem gente suficiente querendo fazer isso sem você. Mas nenhum deles me ofereceu ajuda. Meu destino está por um fio, e depende inteiramente de Javier Castillo, enquanto as pessoas só querem zombar da minha desgraça.";
			link.l1 = "Não sou do tipo que ri das desgraças dos outros. Me conte o que aconteceu. Talvez eu possa te ajudar.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "Ajuda? E por que alguém deveria te dar isso? Eu certamente não vou. Você é o ferreiro da sua própria felicidade... e também da sua desgraça. Então pare de se fazer de vítima – apenas aceite as consequências dos seus atos, elas são mais do que naturais.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "Aquela noite não era para ser fatal. Eu só entrei na taverna para tomar uma caneca de rum depois que o próprio Almirante Eugenio de la Torre fez um grande pedido comigo. Mas, já meio alto, sentei numa mesa para jogar cartas. Foi aí que Javier pôs os olhos em mim\nNo começo, a sorte estava do meu lado – até ganhei uma boa quantia, mas assim que comecei a acreditar na minha sorte, tudo mudou de repente. Javier continuava enchendo minha caneca de rum, e eu só perdia: primeiro gastei todo meu dinheiro, depois o que tinha separado para materiais, e por fim todas as minhas economias\nQuando percebi o quanto já tinha perdido, era tarde demais para desistir. Fiquei obcecado com uma ideia – recuperar tudo, custe o que custar. E então apostei meu livro. Aquele canalha do Javier avaliou ele em apenas cinco mil pesos\nClaro que vale muito mais, mas eu estava tão cego pela empolgação que aceitei. E então... acho que você já sabe o resto. Eu perdi. Sabe, isso nunca tinha acontecido comigo antes. Acho que aquele desgraçado colocou alguma coisa na minha bebida.";
			link.l1 = "E como, posso perguntar, eu deveria te ajudar? Você mesmo se sentou à mesa, você mesmo apostou sua propriedade, e você mesmo perdeu tudo. Agora simplesmente não quer aceitar as consequências? E o que tem de tão valioso nesse livro pra você estar sofrendo assim?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "Este livro é a coisa mais valiosa que eu tinha. Ele guarda segredos transmitidos por séculos, de mestre para aprendiz. É o coração da minha forja, a alma do meu ofício. Já aceitei a perda, "+GetAddress_Form(NPChar)+", mas como posso aceitar perder o livro? Ofereci um resgate ao Javier – cinco mil pesos\nEu estava disposto a me endividar só para tê-lo de volta. Mas sabe o que ele disse? Disse que queria cem mil por ele! Cem mil, "+GetAddress_Form(NPChar)+"! Eu não tenho esse tipo de dinheiro. E ele se recusa a baixar o preço ou aceitar em parcelas. Eu supliquei... mas ele só riu de mim. Vejo que você é "+GetSexPhrase("um homem corajoso, um marinheiro... talvez até um capitão. E sua arma não está aí só de enfeite","não é uma mulher comum, e certamente sabe como lidar com qualquer homem")+"\nPor favor, fale com o Javier. Talvez ele te escute e aceite adiar o pagamento da dívida. Sem esse livro... minha vida perde o sentido. Em troca, sempre poderei te vender materiais de qualidade por um bom preço quando eu me recuperar, e talvez até fazer algo especial pra você, capitão.";
			link.l1 = "Bem, conversar não custa nada. Vamos ver no que isso vai dar. Mas antes, permita-me apresentar: meu nome é "+GetFullName(pchar)+", capitão do meu próprio navio.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("E eu sou Sebastian Cordoba...","Uma mulher – capitã do seu próprio navio? Já ouvi falar disso, mas nunca conheci uma pessoalmente ou conversei com uma.")+" Prazer em conhecê-lo, capitão "+pchar.lastname+". E obrigado. Hoje em dia é mais fácil encontrar quem zombe das desgraças alheias do que quem esteja disposto a ajudar. Sabe, se meu livro voltar para mim, eu juro: nunca mais vou jogar jogos de azar.";
			link.l1 = "Ainda não tem pelo que me agradecer. Primeiro vou cuidar dos meus próprios assuntos e, se sobrar tempo, converso com o Javier.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "Receio que você possa ter chegado tarde demais. Javier acabou sendo muito mais rápido do que eu imaginava\nEle já encontrou um comprador para o livro – Etienne Renoir, um mestre armeiro francês. Se o almirante descobrir que, por minha culpa, um tesouro desses foi parar nas mãos dos franceses... Eu perco a cabeça. Prisão seria um castigo leve.";
			link.l1 = "Hmm... Tudo bem. Vou cuidar do seu problema imediatamente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Capitão "+pchar.lastname+"! Você falou com o Javier? Alguma novidade?";
			link.l1 = "Ainda não, mas estou indo para a taverna agora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "Eu já falei"+GetSexPhrase("","")+". E com bastante sucesso. Javier partiu deste mundo às pressas, mas antes disso conseguiu devolver seu livro. Aqui está.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", você não faz ideia do quanto isso significa pra mim! Graças a você, vou conseguir cumprir todos os pedidos, até mesmo o trabalho para o próprio almirante! Infelizmente, não tenho dinheiro, mas preparei uma recompensa pra você\nAqui, fique com esta couraça – eu a fiz para um certo don, mas tenho certeza de que ele pode esperar um pouco. E também tenho alguns materiais que vão ser úteis caso você decida criar algo por conta própria.";
			link.l1 = "Obrigado, "+npchar.name+", você é muito generoso!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "E também, apareça se precisar de materiais. Minhas entregas chegam uma vez por mês, então sempre vai ter algo útil pra você – e por um bom preço. Eu cumpro o que prometo.";
			link.l1 = "Com certeza! Bem, "+npchar.name+", fique bem. Eu vou indo, tenho coisas a fazer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Capitão "+pchar.lastname+"! Você falou com o Javier? Alguma novidade?";
			link.l1 = "Veja... o livro estava comigo. Mas... as circunstâncias foram tais que ele acabou sendo vendido.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "O quê?! Você... você vendeu?! Meu livro?!";
			link.l1 = "O livro que você perdeu em um jogo de cartas. Ele foi vendido para aquele francês a quem Javier tinha prometido.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "Mas... agora acabou pra mim. O livro está com os franceses, a ordem do almirante não será cumprida... minha vida está arruinada... eu... eu estou perdido!";
			link.l1 = "Você se encurralou. Acho que isso vai te servir como uma boa lição. Adeus.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\English\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "Oi, "+GetSexPhrase("sailor","fofinha")+", quer tentar a sorte nas cartas? Sente-se, as apostas aqui são leves... pelo menos para iniciantes.";
			link.l1 = "Tenho a sensação de que você é exatamente quem eu estou procurando. Foi exatamente assim que você atraiu o Sebastian antes de arrancar até o último centavo dele, não foi? Estou aqui para recuperar o livro dele.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "Ótimo, então. Me dê cem mil – e pode levar. Não tenho utilidade pra esse livro, nem sei diferenciar um alicate de um martelo.";
			link.l1 = "Vou te dar cinco mil – esse foi o preço que você mesmo estabeleceu quando venceu o ferreiro.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "Ha! Você acha que eu sou idiota? Sei muito bem o verdadeiro valor desse livro. Cem mil, e nem uma moeda a menos. Ou ele vai pros franceses – eles não têm problema com dinheiro.";
			link.l1 = "Você acha que as autoridades vão ignorar você vendendo projetos espanhóis para os franceses? O almirante vai ficar furioso quando descobrir.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "Ah, qual é. As autoridades não ligam pra um livro qualquer, já têm problemas demais pra resolver. E o almirante? Sim, ele odeia os franceses de verdade, mas eu não vou ficar esperando por ele – com esse dinheiro todo, vou ser bem-vindo em qualquer colônia do Novo Mundo.";
			link.l1 = "Então vamos fazer um acordo. Você vai receber seu dinheiro, mas não imediatamente. O ferreiro vai pagar a dívida em parcelas, e o livro volta para ele hoje, sob a promessa da honra do meu capitão. Para você, nada muda – ele ainda vai pagar, e você não vai perder um único peso.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "Parece que você não está me ouvindo. Eu fui bem claro – preciso do dinheiro agora. Não daqui a uma semana, nem daqui a um mês, ou quando o ferreiro resolver juntar tudo, mas agora. Estou planejando sair dessa ilha miserável o mais rápido possível. Então, ou o valor completo está nas minhas mãos agora, ou o livro vai para os franceses, e você pode empenhar a honra do seu capitão com o carrasco do almirante.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "Que tal isso: vamos jogar. Meus cem mil contra o livro. Se você ganhar, vai sair da ilha um homem rico. Se perder – eu fico com o livro. Ou será que você só joga com quem nunca viu um baralho antes?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "Ha! Eu não preciso ficar rico – já sou rico! Por que eu arriscaria algo que vai me trazer uma fortuna?";
			link.l1 = "Ora, ora, o próprio Javier Castillo com medo de jogar? E eu que pensei"+GetSexPhrase(""," você")+", você era um jogador experiente, não só um vigarista tirando dinheiro de bêbados ingênuos.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "Eu não tenho medo, só não vejo sentido em sentar à mesa quando já tenho tudo o que preciso.";
			link.l1 = "Ah, qual é, dá pra ver que você tá tremendo só de pensar em jogar contra alguém que não tá segurando as cartas pela primeira vez. Deixa eu adivinhar, tá com tanta pressa pra sair daqui porque tá com vergonha? Todo mundo já percebeu que você não consegue ganhar de ninguém mais forte que um bêbado bobão?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "Como você ousa?! Já derrotei gente que nem se sentaria à mesma mesa que você! Já tivemos apostas grandes o bastante pra comprar um navio, e um capitão arrogante desses pra cada jogador! Vamos jogar. Cinco mil por carta, cem mil cada um, quem ficar sem dinheiro perde. Vamos ver quem vence quem.";
			link.l1 = "Menos conversa, mais ação. Fechado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "Diabo! Isso não pode ser...";
			link.l1 = "Ora, não é tão divertido quando é o outro que está ganhando, né?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "Você é um trapaceiro! Acha que não vi nada? De jeito nenhum vou deixar você me enganar! Prefiro te cortar em pedaços.";
			link.l1 = "Trapaceiro? Ha-ha! Parece que você é que não sabe perder, amigo. Mas se está com tanta pressa de encontrar seu fim – vou te ajudar com isso. Às armas!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "Ha! Bem, "+GetSexPhrase("amigo","fofinha")+", como é ser passado para trás"+GetSexPhrase("","")+"? Dizem que a arrogância é a segunda felicidade, mas não no seu caso.";
			link.l1 = "Não se ache tanto. Você só teve sorte.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "Perdedores sempre dizem isso. Bem, você jogou"+GetSexPhrase("","")+" – você perdeu"+GetSexPhrase("","")+", não leve para o lado pessoal. Se algum dia encontrar mais cem mil, pode tentar a sorte de novo... Mas duvido que o resultado vá mudar...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Olá, "+GetAddress_Form(NPChar)+". A que devo a honra da sua visita?";
			link.l1 = "Saudações. Eu sou o Capitão "+GetFullName(pchar)+", e eu quero conversar com você sobre Javier Castillo.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hmm... Se esse canalha também te deve dinheiro, sinto dizer que vai ter que entrar numa longa fila. O Javier nunca teve pressa pra pagar o que deve. Mas se ele conseguir algum dinheiro, vai me pagar primeiro – já tratei de garantir que ele não tenha outra opção.";
			link.l1 = "Felizmente, não sou credor dele. Quanto ele te deve? E que medidas você já tomou exatamente?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "O valor total da dívida dele é cento e cinquenta mil pesos. Ele só pagou dez mil, aparentemente achando que isso bastava. Mas eu logo deixei claro que ele estava enganado. Meus homens conseguiram arrancar mais vinte mil dele. O resto ele tem que devolver em uma semana, e o prazo está quase acabando. Felizmente, ouvi dizer que em breve ele vai receber uma boa quantia vendendo um livro.";
			link.l1 = "Você acha mesmo que ele vai te pagar? Eu no seu lugar não contaria com isso. O Javier nem esconde que, assim que conseguir o dinheiro, vai fugir daqui.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "Eu sei disso, Capitão. Fique tranquilo, já garanti que ele não vai escapar sem me pagar.";
			link.l1 = "Vejo que você já tem a situação sob controle. No entanto, como a experiência mostra, um pouco mais de cautela nunca faz mal. Veja, eu sou algo como um especialista"+GetSexPhrase("","ess")+" na cobrança de dívidas. Se me permitir agir em seu nome, posso recuperar seu dinheiro.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Infelizmente, Capitão, cobrar essa dívida já está me custando caro demais, e não posso me dar ao luxo de pagar pelos seus serviços também...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", você não precisa se preocupar com isso. Tenho meus próprios interesses nesse assunto, então vou te ajudar sem cobrar nada.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "Posso perguntar, qual exatamente é o seu interesse?";
			link.l1 = "Digamos apenas que alguns dos truques dele na mesa de cartas são coisas que eu não posso deixar passar impunes.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Bem, se não vai me custar nada, não vejo motivo para recusar. Só peço uma coisa, Capitão – não exagere. Se aquele canalha for para o outro mundo antes de pagar a dívida, não vai me adiantar de nada.";
			link.l1 = "Não se preocupe, Felipe, vou agir com cautela.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! Será que você resolveu isso tão rápido?";
			link.l1 = "Infelizmente, ainda não. Mas estou trabalhando nisso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "Ah, "+GetSexPhrase("capitão","fofinho")+" intrometido! Você de novo? O quê, quer perder mais uns milhares?";
			}
			else
			{
				dialog.text = "Você de novo? Eu já falei claramente: dinheiro na mesa – ou caia fora.";
			}
			link.l1 = "Mude o tom, Javier. E trate de pegar sua bolsa – não estou aqui à toa. Não esqueceu da sua dívida com Felipe Alarcon, esqueceu? Agora eu represento os interesses dele. Então escolha: ou paga a dívida agora, ou vou ter que procurar esse dinheiro nos seus bolsos depois que você for encontrar seu criador.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "Maldição! Não tá vendo que eu tô fazendo um negócio aqui? Volte daqui a umas horas – aí a gente conversa.";
			link.l1 = "Parece que você não me ouviu. Fui bem claro: preciso do dinheiro agora. Não daqui a uma semana, nem daqui a um mês, ou quando você conseguir juntar, mas agora. Cento e vinte mil pesos, nem uma moeda a menos. Estou disposto a aceitar o livro como cinco mil.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("Seu desgraçado imundo","Seu desgraçado")+"! Se acha que pode lidar comigo tão facilmente – esse é o maior erro da sua vida miserável.";
			link.l1 = "Vamos ver.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "Que visão... Preciso admitir, "+GetAddress_Form(NPChar)+", você me deu um grande prazer. Você maneja a lâmina com maestria. Permita-me apresentar – "+GetFullName(npchar)+". E este pobre coitado, se não me engano, é o Javier Castillo?";
				link.l1 = "Exatamente, é ele. E eu sou o Capitão "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "Que visão... Preciso admitir, "+GetAddress_Form(NPChar)+", você me deu um grande prazer. Você maneja a espada de forma magnífica. Engraçado como as circunstâncias às vezes mudam – o livro pelo qual viajei tanto agora tem outro dono, de um jeito que eu jamais imaginaria. Mas espero sinceramente não sair daqui de mãos vazias.";
				link.l1 = "Hmm... E quanto você acha que vale esse livro?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "Veja bem, Capitão, viajei uma longa distância por um livro em especial... E parece que agora ele está em suas mãos. Espero sinceramente que possamos chegar a um acordo – eu detestaria sair daqui de mãos vazias.";
			link.l1 = "Hmm... E quanto você acha que vale esse livro?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", eu conheço o valor de coisas realmente raras. Oitenta mil pesos. Uma quantia mais do que generosa, e acredite, é improvável que você receba uma oferta dessas novamente.";
			link.l1 = "Bem, o livro realmente tem valor, e eu admito que pedi"+GetSexPhrase("","")+" pura curiosidade. Não pretendo negociar com o destino de um homem. Receio, monsieur, que não haverá acordo – este livro deve voltar ao seu verdadeiro dono.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "Uma quantia ridícula. Este livro guarda os segredos dos maiores mestres da forja. Cento e cinquenta mil pesos – ou você aceita, ou ele volta para o dono. Sem negociação.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Por favor, não recuse tão depressa. Viajei muito para chegar até aqui. Estou disposto a lhe oferecer cem mil, apenas como um sinal de respeito pela habilidade com que lidou com aquele homem.";
			link.l1 = "Já disse tudo o que precisava. Agora, com licença, preciso ir.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", Eu agradeço pela sua confiança, mas cento e cinquenta mil – isso não é um preço, é um absurdo. Não vamos transformar esse negócio numa piada. Cem mil pesos é um valor justo, aceite – ninguém vai pagar mais por esse livro.";
			link.l1 = "Parece que não conseguimos chegar a um acordo. Bem, não vejo motivo para continuar essa conversa. Adeus, monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "Espere! Tudo bem, você venceu. Cento e cinquenta mil. Temos um acordo?";
			link.l1 = "Que bom que fez a escolha certa. O livro é seu. Acho que com ele você vai se tornar o maior mestre do Caribe.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", mesmo sem este livro eu já era imbatível. Mas devo admitir, é um prazer conquistar um troféu tão raro. Agora, por favor, me dê licença – mal posso esperar para descobrir se ele realmente faz jus aos elogios que ouvi.";
			link.l1 = "Então, não vou te segurar. Até logo.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Ora, ora, o que temos aqui? Achou que ia limpar nosso baú e fugir? Grande erro, camarada. Agora é a gente que vai te enfiar nesse baú e pregar a tampa!";
			}
			else
			{
				dialog.text = "Ora, ora... E quem temos aqui? Perdeu o caminho, querida? Achou que ia esvaziar o baú e sair de fininho? Grande erro, minha doce. Agora vamos revistar você direitinho – e ver o que tem nos seus bolsos... e em outros lugares.";
			}
			link.l1 = "Palavras demais para vermes patéticos como vocês. Saquem suas lâminas, vamos ver do que realmente são capazes.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "Capitão! Já fui informado que o Javier foi encontrar seu criador por sua causa. E eu pedi pra você não matá-lo tão cedo! Espero que tenha vindo devolver meu dinheiro?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Exato. Consegui encontrar o esconderijo dele, onde havia cem mil pesos. Era todo o dinheiro que ele tinha.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Sim, eu tive que matá-lo. Mas ele me atacou primeiro, e eu precisei me defender. Os bolsos dele estavam vazios – nem uma moeda sequer. Infelizmente, não consegui recuperar a dívida.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "Cem mil... Claro, não é o valor total, mas conhecendo o Javier, duvido que alguém conseguiria arrancar mais dele. Pois bem, obrigado, Capitão. Parece que contratei as pessoas erradas. Você realmente é um mestre no que faz.";
			link.l1 = "Não foi difícil. Dito isso, receio que preciso me retirar"+GetSexPhrase("","")+". O negócio espera.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Adeus, Capitão.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "Você "+GetSexPhrase("canalha","desgraçado")+"! Mentindo na minha cara enquanto olha nos meus olhos?! Você não vai escapar dessa!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			dialog.text = "Olá, "+pchar.name+"! Gostaria de comprar materiais ou mercadorias?";
			link.l1 = ""+TimeGreeting()+". Vamos ver o que você tem.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "E olá pra você, "+npchar.name+"! Obrigado pela oferta, mas eu só queria"+GetSexPhrase("","")+" para dizer oi.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", decidiu comprar alguma coisa afinal?";
			link.l1 = "Exatamente. Mostre-me o que você tem hoje.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Desculpe, já estou de saída.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}